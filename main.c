#include <stdio.h>
#include <stdlib.h>
#include <xlsxio_read.h> // Include library for reading Excel files

#define MAX_ROWS 1000 // Maximum number of rows to read from the Excel sheet

// Struct to hold income data
struct IncomeData {
    int month;
    int year;
    double income;
};

// Function to calculate average income per year
double calculateAverageIncome(struct IncomeData *data, int count) {
    double totalIncome = 0.0;
    for (int i = 0; i < count; i++) {
        totalIncome += data[i].income;
    }
    return totalIncome / count;
}

int main() {
    // Initialize variables
    struct IncomeData incomeData[MAX_ROWS];
    int rowCount = 0;

    // Open Excel file
    xlsxioreader xls = xlsxioread_open("DataPMC20232024.xls");
    if (xls == NULL) {
        printf("Failed to open Excel file.\n");
        return 1;
    }

    // Open first sheet
    xlsxioreadersheet sheet = xlsxioread_sheet_open(xls, NULL, XLSXIOREAD_SKIP_EMPTY_ROWS);
    if (sheet == NULL) {
        printf("Failed to open Excel sheet.\n");
        xlsxioread_close(xls);
        return 1;
    }

    // Read income data from Excel
    while (xlsxioread_sheet_next_row(sheet)) {
        if (rowCount >= MAX_ROWS) {
            printf("Exceeded maximum rows.\n");
            break;
        }

        const char *cellValue = NULL;
        int columnIndex = 0;
        struct IncomeData data;

        // Read month (assuming it's in first column)
        cellValue = xlsxioread_sheet_next_cell(sheet);
        if (cellValue != NULL) {
            sscanf(cellValue, "%d", &data.month);
        } else {
            continue; // Skip empty rows or missing data
        }

        // Read year (assuming it's in second column)
        cellValue = xlsxioread_sheet_next_cell(sheet);
        if (cellValue != NULL) {
            sscanf(cellValue, "%d", &data.year);
        } else {
            continue; // Skip empty rows or missing data
        }

        // Read income (assuming it's in third column)
        cellValue = xlsxioread_sheet_next_cell(sheet);
        if (cellValue != NULL) {
            sscanf(cellValue, "%lf", &data.income);
        } else {
            continue; // Skip empty rows or missing data
        }

        incomeData[rowCount++] = data;
    }

    // Close sheet and Excel file
    xlsxioread_sheet_close(sheet);
    xlsxioread_close(xls);

    // Calculate total income and average income per year
    double totalIncome = 0.0;
    int yearCount = 0;
    int currentYear = incomeData[0].year;

    for (int i = 0; i < rowCount; i++) {
        totalIncome += incomeData[i].income;
        if (incomeData[i].year != currentYear) {
            yearCount++;
            currentYear = incomeData[i].year;
        }
    }

    double averageIncome = calculateAverageIncome(incomeData, yearCount);

    // Print results
    printf("Total income:\t%.2f\n", totalIncome);
    printf("Average income per year:\t%.2f\n", averageIncome);

    return 0;
}
