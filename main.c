#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VISITS 1000 // Maksimum kunjungan yang dapat diproses

struct PatientVisit {
    int no;
    char tanggal_masuk[20];
    char id_pasien[20];
    char keluhan[100];
    char penanganan[100];
    char tanggal_keluar[20];
    double biaya_penanganan;
};

// Fungsi untuk membaca data kunjungan dari file CSV
int readPatientVisits(const char *filename, struct PatientVisit visits[]) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 0;
    }

    char line[256];
    int count = 0;
    while (fgets(line, sizeof(line), file)) {
        // Parsing each line assuming format: no, tanggal_masuk, id_pasien, keluhan, penanganan, tanggal_keluar, biaya_penanganan
        char *token = strtok(line, ",");
        visits[count].no = atoi(token);

        token = strtok(NULL, ",");
        strcpy(visits[count].tanggal_masuk, token);

        token = strtok(NULL, ",");
        strcpy(visits[count].id_pasien, token);

        token = strtok(NULL, ",");
        strcpy(visits[count].keluhan, token);

        token = strtok(NULL, ",");
        strcpy(visits[count].penanganan, token);

        token = strtok(NULL, ",");
        strcpy(visits[count].tanggal_keluar, token);

        token = strtok(NULL, ",");
        visits[count].biaya_penanganan = atof(token);

        count++;
    }

    fclose(file);
    return count;
}

int main() {
    struct PatientVisit visits[MAX_VISITS]; // Array untuk menyimpan kunjungan pasien
    int numVisits = readPatientVisits("data_pasien.csv", visits); // Membaca data dari file CSV
    if (numVisits == 0) {
        printf("Tidak ada data yang dapat dibaca dari data_pasien.csv\n");
        return 1;
    }

    // Array untuk menyimpan total pendapatan bulanan dan rata-rata pendapatan tahunan
    double totalIncomePerMonth[12] = {0};
    double totalIncomePerYear[100] = {0}; // Asumsi maksimal 100 tahun
    int numYears = 0;

    // Menghitung total pendapatan per bulan dan per tahun
    for (int i = 0; i < numVisits; i++) {
        int month;
        int year;
        sscanf(visits[i].tanggal_masuk, "%d-%*[^-]-%d", &month, &year); // Mengambil bulan dan tahun dari tanggal masuk

        totalIncomePerMonth[month - 1] += visits[i].biaya_penanganan; // Mengakumulasi pendapatan per bulan
        totalIncomePerYear[year] += visits[i].biaya_penanganan; // Mengakumulasi pendapatan per tahun
        if (year > numYears) numYears = year; // Menyimpan tahun terbaru yang terdeteksi
    }

    // Menampilkan total pendapatan per bulan
    for (int year = 2022; year <= numYears; year++) {
        for (int month = 1; month <= 12; month++) {
            printf("Total pemasukan bulan %d tahun %d: %.2f\n", month, year, totalIncomePerMonth[month - 1]);
        }
    }

    // Menghitung dan menampilkan rata-rata pendapatan per tahun
    for (int year = 2022; year <= numYears; year++) {
        double totalYearlyIncome = 0;
        int numMonths = 0;
        for (int month = 1; month <= 12; month++) {
            totalYearlyIncome += totalIncomePerMonth[month - 1];
            numMonths++;
        }
        double averageYearlyIncome = totalYearlyIncome / numMonths;
        printf("Rata-rata pendapatan tahun %d: %.2f\n", year, averageYearlyIncome);
    }

    return 0;
}
