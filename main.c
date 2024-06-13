#include <stdio.h>
#include <stdlib.h>
#include <xlsxio_read.h>

#define MAX_ROWS 1000 // Maksimum baris yang akan dibaca dari lembar Excel

struct IncomeData {
    int month;
    int year;
    double income;
};

double calculateAverageIncome(double totalIncome, int totalMonths) {
    return totalIncome / totalMonths;
}

int main() {
    struct IncomeData incomeData[MAX_ROWS];
    int rowCount = 0;
    double totalIncome = 0.0;
    double totalIncomePerYear = 0.0;
    int totalMonthsPerYear = 0;
    int currentYear = -1; // Tahun saat ini, dimulai dengan -1

    // Buka file Excel
    xlsxioreader xls = xlsxioread_open("DataPMC20232024.xls");
    if (xls == NULL) {
        printf("Gagal membuka file Excel.\n");
        return 1;
    }

    // Buka lembar pertama
    xlsxioreadersheet sheet = xlsxioread_sheet_open(xls, NULL, XLSXIOREAD_SKIP_EMPTY_ROWS);
    if (sheet == NULL) {
        printf("Gagal membuka lembar Excel.\n");
        xlsxioread_close(xls);
        return 1;
    }

    // Baca data pendapatan dari Excel
    while (xlsxioread_sheet_next_row(sheet)) {
        if (rowCount >= MAX_ROWS) {
            printf("Melebihi jumlah maksimum baris.\n");
            break;
        }

        const char *cellValue = NULL;
        int columnIndex = 0;
        struct IncomeData data;

        // Baca bulan (diasumsikan di kolom pertama)
        cellValue = xlsxioread_sheet_next_cell(sheet);
        if (cellValue != NULL) {
            sscanf(cellValue, "%d", &data.month);
        } else {
            continue; // Lewati baris kosong atau data yang hilang
        }

        // Baca tahun (diasumsikan di kolom kedua)
        cellValue = xlsxioread_sheet_next_cell(sheet);
        if (cellValue != NULL) {
            sscanf(cellValue, "%d", &data.year);
        } else {
            continue; // Lewati baris kosong atau data yang hilang
        }

        // Baca pendapatan (diasumsikan di kolom ketiga)
        cellValue = xlsxioread_sheet_next_cell(sheet);
        if (cellValue != NULL) {
            sscanf(cellValue, "%lf", &data.income);
        } else {
            continue; // Lewati baris kosong atau data yang hilang
        }

        // Akumulasi pendapatan bulanan
        totalIncome += data.income;

        // Periksa perubahan tahun
        if (data.year != currentYear) {
            // Hitung rata-rata pendapatan per tahun sebelum beralih ke tahun baru
            if (currentYear != -1) { // Jangan hitung untuk tahun pertama (currentYear == -1)
                double averageIncomePerYear = calculateAverageIncome(totalIncomePerYear, totalMonthsPerYear);
                printf("Total pendapatan tahun %d: %.2f\n", currentYear, totalIncomePerYear);
                printf("Rata-rata pendapatan tahun %d: %.2f\n\n", currentYear, averageIncomePerYear);
            }

            // Reset variabel untuk tahun baru
            currentYear = data.year;
            totalIncomePerYear = 0.0;
            totalMonthsPerYear = 0;
        }

        // Akumulasi pendapatan per tahun
        totalIncomePerYear += data.income;
        totalMonthsPerYear++;

        // Simpan data bulan ini
        incomeData[rowCount++] = data;
    }

    // Output total dan rata-rata pendapatan untuk tahun terakhir
    if (currentYear != -1) {
        double averageIncomePerYear = calculateAverageIncome(totalIncomePerYear, totalMonthsPerYear);
        printf("Total pendapatan tahun %d: %.2f\n", currentYear, totalIncomePerYear);
        printf("Rata-rata pendapatan tahun %d: %.2f\n", currentYear, averageIncomePerYear);
    }

    // Tutup lembar dan file Excel
    xlsxioread_sheet_close(sheet);
    xlsxioread_close(xls);

    return 0;
}
