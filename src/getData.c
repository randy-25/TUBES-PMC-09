#include <xlsxio_read.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../header/getData.h"

void getData(struct dataPasien **pasien, struct riwayat **riwayatPasien, int *jumlahPasien, int *jumlahRiwayatPasien)
{
    const char *filename = "../data/DataPMC20232024.xlsx";
    // open .xlsx file for reading
    xlsxioreader xlsxioread;
    if ((xlsxioread = xlsxioread_open(filename)) == NULL)
    {
        fprintf(stderr, "Error opening .xlsx file\n");
        return;
    }

    *jumlahPasien = 0;
    *jumlahRiwayatPasien = 0;

    // read values from first sheet
    char *value;
    xlsxioreadersheet sheet;
    xlsxioreadersheetlist sheetlist;
    const char *sheetname = NULL;
    int sheetsIndex, rowIndex, colIndex;
    
    if ((sheetlist = xlsxioread_sheetlist_open(xlsxioread)) != NULL)
    {
        sheetsIndex = 0;
        while ((sheetname = xlsxioread_sheetlist_next(sheetlist)) != NULL)
        {
            sheet = xlsxioread_sheet_open(xlsxioread, sheetname, XLSXIOREAD_SKIP_NONE);
            if (sheet == NULL)
            {
                fprintf(stderr, "Error opening sheet %s\n", sheetname);
                continue;
            }
            // printf("\n");
            // printf("Sheet: %s\n", sheetname);
            rowIndex = -2; // -2 to skip the header row
            while (xlsxioread_sheet_next_row(sheet))
            {
                if (sheetsIndex == 0)
                {
                    if (rowIndex >= 0)
                    {
                        if ((*pasien) == NULL)
                        {
                            (*pasien) = (struct dataPasien*)malloc(sizeof(struct dataPasien));
                        }
                        else
                        {
                            (*pasien) = (struct dataPasien*)realloc((*pasien), (rowIndex + 1) * sizeof(struct dataPasien));
                        }
                        memset(&((*pasien)[rowIndex]), 0, sizeof(struct dataPasien));
                    }
                }
                else if (sheetsIndex == 1)
                {
                    if (rowIndex >= 0)
                    {
                        if ((*riwayatPasien) == NULL)
                        {
                            (*riwayatPasien) = (riwayat *)malloc(sizeof(struct riwayat));
                        }
                        else
                        {
                            (*riwayatPasien) = (riwayat *)realloc((*riwayatPasien), (rowIndex + 1) * sizeof(struct riwayat));
                        }
                        memset(&((*riwayatPasien)[rowIndex]), 0, sizeof(struct riwayat));
                    }
                }
                colIndex = 0;
                while ((value = xlsxioread_sheet_next_cell(sheet)) != NULL)
                {
                    if (sheetsIndex == 0 && rowIndex >= 0)
                    {
                        getDataPasien(&((*pasien)[rowIndex]), value, colIndex);
                    }else if (sheetsIndex == 1 && rowIndex >= 0)
                    {
                        getRiwayatPasien(&((*riwayatPasien)[rowIndex]), value, colIndex);
                    }
                    free(value);
                    colIndex++;
                }
                rowIndex++;
            }
            if(sheetsIndex == 0){
                *jumlahPasien = rowIndex;
            }else if(sheetsIndex == 1){
                *jumlahRiwayatPasien = rowIndex;
            }
            xlsxioread_sheet_close(sheet);
            sheetsIndex++;
        }
        xlsxioread_sheetlist_close(sheetlist);
    }

    // clean up
    xlsxioread_close(xlsxioread);
}

void getDataPasien(struct dataPasien *pasien, char *value, int colIndex)
{
    switch (colIndex)
    {
    case 0:
        pasien->no = atoi(value);
        break;
    case 1:
        pasien->nama = strdup(value);
        break;
    case 2:
        pasien->alamat = strdup(value);
        break;
    case 3:
        pasien->kota = strdup(value);
        break;
    case 4:
        pasien->tempatLahir = strdup(value);
        break;
    case 5:
        parseDateString(value, &pasien->tanggalLahir.tanggal, &pasien->tanggalLahir.bulan, &pasien->tanggalLahir.tahun);
        break;
    case 6:
        pasien->umur = atoi(value);
        break;
    case 7:
        pasien->nomorBPJS = strdup(value);
        break;
    case 8:
        pasien->IdPasien = strdup(value);
        break;
    default:
        break;
    }
}

void printDataPasien(struct dataPasien pasien)
{
    printf("No: %d\n", pasien.no);
    printf("Nama: %s\n", pasien.nama);
    printf("Alamat: %s\n", pasien.alamat);
    printf("Kota: %s\n", pasien.kota);
    printf("Tempat Lahir: %s\n", pasien.tempatLahir);
    printf("Tanggal Lahir: %d-%d-%d \n", pasien.tanggalLahir.tanggal, pasien.tanggalLahir.bulan, pasien.tanggalLahir.tahun);
    printf("Umur: %d\n", pasien.umur);
    printf("Nomor BPJS: %s\n", pasien.nomorBPJS);
    printf("Id Pasien: %s\n", pasien.IdPasien);
}

void printRiwayatPasien(struct riwayat riwayatPasien)
{
    printf("No: %d\n", riwayatPasien.no);
    printf("Tanggal Periksa: %d-%d-%d \n", riwayatPasien.tanggalPeriksa.tanggal, riwayatPasien.tanggalPeriksa.bulan, riwayatPasien.tanggalPeriksa.tahun);
    printf("Id Pasien: %s\n", riwayatPasien.IdPasien);
    printf("Diagnosis: %s\n", riwayatPasien.diagnosis);
    printf("Tindakan: %s\n", riwayatPasien.tindakan);
    printf("Tanggal Kontrol: %d-%d-%d \n", riwayatPasien.tanggalKontrol.tanggal, riwayatPasien.tanggalKontrol.bulan, riwayatPasien.tanggalKontrol.tahun);
    printf("Biaya: %d\n", riwayatPasien.biaya);
}

void getRiwayatPasien(struct riwayat *riwayatPasien, char *value, int colIndex)
{
    switch (colIndex)
    {
    case 0:
        riwayatPasien->no = atoi(value);
        break;
    case 1:
        parseDateString(value, &riwayatPasien->tanggalPeriksa.tanggal, &riwayatPasien->tanggalPeriksa.bulan, &riwayatPasien->tanggalPeriksa.tahun);
        break;
    case 2:
        riwayatPasien->IdPasien = strdup(value);
        break;
    case 3:
        riwayatPasien->diagnosis = strdup(value);
        break;
    case 4:
        riwayatPasien->tindakan = strdup(value);
        break;
    case 5:
        parseDateString(value, &riwayatPasien->tanggalKontrol.tanggal, &riwayatPasien->tanggalKontrol.bulan, &riwayatPasien->tanggalKontrol.tahun);
        break;
    case 6:
        riwayatPasien->biaya = atoi(value);
        break;
    default:
        break;
    }
}

void getBiaya(struct biaya **biaya){
    (*biaya) = (struct biaya*)malloc(sizeof(struct biaya));
    (*biaya)->pendaftaran = 15000;
    (*biaya)->pemeriksaan = 125000;
    (*biaya)->vaksinasi = 100000;
    (*biaya)->cekGulaDarah = 25000;
    (*biaya)->pemasanganInfus = 125000;
    (*biaya)->pengobatan = 150000;
}

// Function to get the month number from the month name
int getMonthNumber(const char *monthName)
{
    const char *months[] = {"Januari", "Februari", "Maret", "April", "Mei", "Juni",
                            "Juli", "Agustus", "September", "Oktober", "November", "Desember"};
    int numMonths = sizeof(months) / sizeof(months[0]);
    for (int i = 0; i < numMonths; i++)
    {
        if (strcmp(monthName, months[i]) == 0)
        {
            return i + 1;
        }
    }
    return -1; // Return -1 if the month name is not found
}

// Function to check if a string contains only digits
int isNumeric(const char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (!isdigit(str[i]))
        {
            return 0;
        }
    }
    return 1;
}

// Function to convert days since 1 January 1900 to date, month, and year
void convertDaysToDate(int days, int *date, int *month, int *year)
{
    // Base date is 1 January 1900
    int baseYear = 1900;
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int isLeap;

    *year = baseYear;
    while (days >= 365)
    {
        isLeap = ((*year % 4 == 0 && *year % 100 != 0) || (*year % 400 == 0));
        if (days < (isLeap ? 366 : 365))
            break;
        days -= isLeap ? 366 : 365;
        (*year)++;
    }

    isLeap = ((*year % 4 == 0 && *year % 100 != 0) || (*year % 400 == 0));
    for (*month = 0; *month < 12; (*month)++)
    {
        int daysInThisMonth = daysInMonth[*month] + (isLeap && *month == 1 ? 1 : 0);
        if (days < daysInThisMonth)
            break;
        days -= daysInThisMonth;
    }
    *month += 1;
    *date = days + 1;
}

// Function to parse date string
void parseDateString(const char *dateString, int *date, int *month, int *year)
{
    char monthName[20];

    // Check if the string is numeric
    if (isNumeric(dateString))
    {
        // Handle the "number of days" format
        int days = atoi(dateString);
        convertDaysToDate(days - 2, date, month, year);
    }
    else
    {
        // Handle the "day month year" format
        if (sscanf(dateString, "%d %19s %d", date, monthName, year) == 3)
        {
            *month = getMonthNumber(monthName);
            if (*month == -1)
            {
                printf("Invalid month name.\n");
            }
        }
        else
        {
            printf("Failed to parse date string.\n");
        }
    }
}
