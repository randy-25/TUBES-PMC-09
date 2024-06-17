#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../header/getDataCSV.h"

// Function to get the month number from the month name
int getMonthNumber_CSV(const char *monthName)
{
    if (strcmp(monthName, "Jan") == 0 || strcmp(monthName, "Januari") == 0) return 1;
    if (strcmp(monthName, "Feb") == 0 || strcmp(monthName, "Februari") == 0) return 2;
    if (strcmp(monthName, "Mar") == 0 || strcmp(monthName, "Maret") == 0) return 3;
    if (strcmp(monthName, "Apr") == 0 || strcmp(monthName, "April") == 0) return 4;
    if (strcmp(monthName, "Mei") == 0) return 5;
    if (strcmp(monthName, "Jun") == 0 || strcmp(monthName, "Juni") == 0) return 6;
    if (strcmp(monthName, "Jul") == 0 || strcmp(monthName, "Juli") == 0) return 7;
    if (strcmp(monthName, "Agu") == 0 || strcmp(monthName, "Agustus") == 0) return 8;
    if (strcmp(monthName, "Sep") == 0 || strcmp(monthName, "September") == 0) return 9;
    if (strcmp(monthName, "Okt") == 0 || strcmp(monthName, "Oktober") == 0) return 10;
    if (strcmp(monthName, "Nov") == 0 || strcmp(monthName, "November") == 0) return 11;
    if (strcmp(monthName, "Des") == 0 || strcmp(monthName, "Desember") == 0) return 12;
    return -1;
}

int is_format_CSV(char *Date){
    char *tempDate = strdup(Date);
    char *temp1 = strtok(tempDate, " ");
    char *temp2 = strtok(NULL, " ");

    if (temp2 != NULL){
        return 1;
    }
    else {
        return 0;
    }
}

void printDataPasien_CSV (struct dataPasien DataPasien){
        printf("No: %d\n", DataPasien.no);
        printf("Nama: %s\n", DataPasien.nama);
        printf("Alamat: %s\n", DataPasien.alamat);
        printf("Kota: %s\n", DataPasien.kota);
        printf("Tempat Lahir: %s\n", DataPasien.tempatLahir);
        printf("Tanggal Lahir: %d-%d-%d \n", DataPasien.tanggalLahir.tanggal, DataPasien.tanggalLahir.bulan,DataPasien.tanggalLahir.tahun);
        printf("Umur: %d\n",DataPasien.umur);
        printf("Nomor BPJS: %s\n", DataPasien.nomorBPJS);
        printf("Id Pasien: %s\n", DataPasien.IdPasien);
        printf("\n");
}

void printRiwayatPasien_CSV (struct riwayat RiwayatPasien){
    printf("No: %d\n", RiwayatPasien.no);
    printf("Tanggal Periksa: %d-%d-%d \n",RiwayatPasien.tanggalPeriksa.tanggal, RiwayatPasien.tanggalPeriksa.bulan, RiwayatPasien.tanggalPeriksa.tahun);
    printf("ID Pasien: %s\n", RiwayatPasien.IdPasien);
    printf("diagnosis: %s\n", RiwayatPasien.diagnosis);
    printf("tingakan: %s\n", RiwayatPasien.tindakan);
    printf("Tanggal Kontrol: %d-%d-%d \n",RiwayatPasien.tanggalKontrol.tanggal, RiwayatPasien.tanggalKontrol.bulan, RiwayatPasien.tanggalKontrol.tahun);
    printf("Biaya: %d\n", RiwayatPasien.biaya);
    printf("\n");
}


void parseDate_CSV (char *Date, int *day, int *month, int *year){
    char *tempmonth;
    char monthName[20];

    //handle DD-MM-YY format
    if(is_format_CSV(Date) == 0) {

        int *tempyears;

        *day = atoi(strtok(Date, "-"));
        tempmonth = strtok(NULL, "-");
        *year = atoi(strtok(NULL, " "));

        //if the years above 30, assumed that it is in 19 century
        if ((*year) > 30){
            *year = *year + 1900;
        }
        else {
            *year = 2000 + *year;
        }

        //convert the month to
        *month = getMonthNumber_CSV(tempmonth);
        if (*month == -1){
            printf("failed to parsed date \n");
        }
    }
    else {

        // format1_Date(Date, day, tempmonth, year);
        if (sscanf(Date, "%d %19s %d", day, monthName, year) == 3)
        {   
            *month = getMonthNumber_CSV(monthName);
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

void get_DataPasien_CSV(struct dataPasien **Data, int *JumlahDataPasien) {
    FILE *file = fopen("../data/Data Pasien.csv", "r");

    if (file == NULL){
        printf("Tidak ada file");
    }

    char temp[500];
    int Index = 0;


    while (fgets(temp, 400, file) != NULL){
    
        if ((*Data) == NULL){
            (*Data) = (dataPasien*)malloc((Index+1)*sizeof(struct dataPasien));
        }
        else {
            (*Data) = (dataPasien*)realloc((*Data), (Index+1)*sizeof(struct dataPasien));
            if ((*Data) == NULL){
                printf("gagal\n");
            }
        }

        struct dataPasien *current = &(*Data)[Index];
       
        current->no = atoi(strtok(temp, ","));

        current->nama = strdup(strtok(NULL, ","));

        current->alamat =  strdup(strtok(NULL, ","));

        current->kota =  strdup(strtok(NULL, ","));

        current->tempatLahir =  strdup(strtok(NULL, ","));

        char *tempDate = strtok(NULL, ",");

        current->umur = atoi(strtok(NULL, ","));

        current->nomorBPJS =  strdup(strtok(NULL, ","));

        current->IdPasien =  strdup(strtok(NULL, "\n"));

        parseDate_CSV(tempDate, &current->tanggalLahir.tanggal, &current->tanggalLahir.bulan, &current->tanggalLahir.tahun);

        Index++;

    }
    *JumlahDataPasien = Index;
    fclose(file);
}

void get_RiwayatPasien_CSV(struct riwayat **RiwayatPasien, int *JumlahRiwayatPasien){
    FILE *file = fopen("../data/Riwayat Pasien.csv", "r");

    if (file == NULL){
        printf("Tidak ada file");
    }

    char temp[500];
    int Index = 0;

    while (fgets(temp, 400, file)){

        if ((*RiwayatPasien) == NULL){
            (*RiwayatPasien) = (riwayat*)malloc((Index+1)*sizeof(struct riwayat));
        }
        else {
            (*RiwayatPasien) = (riwayat*)realloc((*RiwayatPasien), (Index+1)*sizeof(struct riwayat));
        }

        struct riwayat *current = &(*RiwayatPasien)[Index];

        current->no = atoi(strtok(temp, ","));

        char *tempDatePeriksa = strtok(NULL, ",");

        current->IdPasien = strdup(strtok(NULL, ","));
        current->diagnosis = strdup(strtok(NULL, ","));
        current->tindakan = strdup(strtok(NULL, ","));

        char *tempDateKontrol = strtok(NULL, ",");
        
        current->biaya = atoi(strtok(NULL, "\n"));
        
        parseDate_CSV(tempDatePeriksa, &current->tanggalPeriksa.tanggal, &current->tanggalPeriksa.bulan, &current->tanggalPeriksa.tahun);
        parseDate_CSV(tempDateKontrol, &current->tanggalKontrol.tanggal, &current->tanggalKontrol.bulan, &current->tanggalKontrol.tahun);

       Index++;
    }
    *JumlahRiwayatPasien = Index;
    fclose(file);
}

void get_BiayaTindakan_CSV (struct biaya **BiayaPerawatan){
    FILE *file = fopen("../data/Biaya Tindakan.csv", "r");

    if (file == NULL){
        printf("Tidak ada file");
    }

    char temp[500];
    char *tempAktivitas[50];
    char *tempNo[50];

    (*BiayaPerawatan) = (biaya*)malloc(sizeof(struct biaya));

    while (fgets(temp, 400, file)!= NULL){
        
        *tempNo = strtok(temp, ",");
        *tempAktivitas = strtok(NULL, ",");

        if (strcmp(*tempAktivitas, "Pendaftaran")== 0){
            (*BiayaPerawatan)->pendaftaran = atoi(strtok(NULL, " "));
        } 
        else if (strcmp(*tempAktivitas, "Pemeriksaan") == 0){
            (*BiayaPerawatan)->pemeriksaan = atoi(strtok(NULL, " "));
        }
        else if (strcmp(*tempAktivitas, "Vaksinasi") == 0){
            (*BiayaPerawatan)->vaksinasi = atoi(strtok(NULL, " "));
        }
        else if (strcmp(*tempAktivitas, "Cek gula darah") == 0){
            (*BiayaPerawatan)->cekGulaDarah = atoi(strtok(NULL, " "));
        }
        else if (strcmp(*tempAktivitas, "Pemasangan infus") == 0){
            (*BiayaPerawatan)->pemasanganInfus= atoi(strtok(NULL, " "));
        }
        else if (strcmp(*tempAktivitas, "Pengobatan") == 0){
            (*BiayaPerawatan)->pengobatan = atoi(strtok(NULL, " "));
        }
        else {
            printf("Biaya tidak ada");
        }
    }
    fclose(file);
}