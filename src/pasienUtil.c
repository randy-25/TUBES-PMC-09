#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../header/getData.h"
#include "../header/pasienUtil.h"

void cariPasien(struct dataPasien *pasien, int jumlahPasien, char *IdPasien, struct dataPasien *dataHolder)
{
    // printf("ID Pasien: %s\n", IdPasien);
    for (int i = 0; i < jumlahPasien; i++)
    {
        if (strcmp(pasien[i].IdPasien, IdPasien) == 0)
        {
            *dataHolder = pasien[i];
        }
    }
}

int hitungUmur(int tanggal, int bulan, int tahun)
{   
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int currentYear = tm.tm_year + 1900;
    int currentMonth = tm.tm_mon + 1;
    int currentDay = tm.tm_mday;
    
    int umur = currentYear - tahun;
    if(currentMonth < bulan){
        umur -= 1;
    }else if(currentMonth == bulan){
        if(currentDay < tanggal){
            umur -= 1;
        }
    }
    return umur;
}

void tambahPasien(struct dataPasien **pasien, int *jumlahPasien)
{
    struct dataPasien tempPasien;

    (*pasien) = (struct dataPasien *)realloc(*pasien, (*jumlahPasien + 1) * sizeof(struct dataPasien));

    char temp[100];
    printf("Masukkan Nomor BPJS pasien: ");
    fgets(temp, 20, stdin);
    temp[strcspn(temp, "\n")] = '\0';
    int cek = 0;
    for(int i = 0; i < *jumlahPasien; i++){
        if(strcmp((*pasien)[i].nomorBPJS, temp) == 0){
            cek += 1;
        }
    }
    if(cek == 0){
        tempPasien.nomorBPJS = strdup(temp);

        printf("Masukkan Nama Pasien: ");
        fgets(temp, 100, stdin);
        temp[strcspn(temp, "\n")] = '\0';
        tempPasien.nama = strdup(temp);

        printf("Masukkan Alamat Pasien: ");
        fgets(temp, 100, stdin);
        temp[strcspn(temp, "\n")] = '\0';
        tempPasien.alamat = strdup(temp);

        printf("Masukkan Kota Pasien: ");
        fgets(temp, 100, stdin);
        temp[strcspn(temp, "\n")] = '\0';
        tempPasien.kota = strdup(temp);

        printf("Masukkan Tempat Lahir Pasien: ");
        fgets(temp, 100, stdin);
        temp[strcspn(temp, "\n")] = '\0';
        tempPasien.tempatLahir = strdup(temp);

        printf("Masukkan Tanggal Lahir Pasien (dd-mm-yyyy): ");
        scanf("%d-%d-%d", &tempPasien.tanggalLahir.tanggal, &tempPasien.tanggalLahir.bulan, &tempPasien.tanggalLahir.tahun);

        tempPasien.umur = hitungUmur(tempPasien.tanggalLahir.tanggal, tempPasien.tanggalLahir.bulan, tempPasien.tanggalLahir.tahun);

        int prevId;
        char tempId[15];
        char *token;
        if(*jumlahPasien == 0){
            prevId = 1230123;
        }else{
            strcpy(tempId, (*pasien)[*jumlahPasien - 1].IdPasien);
            token = strtok(tempId, " ");
            token = strtok(NULL, " ");
            prevId = atoi(token);
        }

        prevId += 1;
        strcpy(tempId, "KX ");
        sprintf(temp, "%d", prevId);  
        strcat(tempId, temp);
        tempPasien.IdPasien = strdup(tempId);
        
        tempPasien.no = (*jumlahPasien) + 1;

        (*pasien)[*jumlahPasien] = tempPasien;
        (*jumlahPasien)++;
    }else{
        printf("Pasien telah terdaftar\n");
    }
}

int cekNoBPJS(char *nomorBPJS, struct dataPasien *pasien, int jumlahPasien, char *IdPasien)
{
    for(int i = 0; i < jumlahPasien; i++){
        if(strcmp(pasien[i].nomorBPJS, nomorBPJS) == 0 && strcmp(pasien[i].IdPasien, IdPasien) != 0){
            return 1;
        }
    }
    return 0;
}

void ubahDataPasien(struct dataPasien **pasien, int jumlahPasien)
{
    char IdPasien[15];
    char temp[15];
    printf("Masukkan ID Pasien: KX ");
    fgets(temp, 15, stdin);
    strcpy(IdPasien, "KX ");
    strcat(IdPasien, temp);
    IdPasien[strcspn(IdPasien, "\n")] = '\0';

    int count = 0;
    for (int i = 0; i < jumlahPasien; i++)
    {
        if (strcmp((*pasien)[i].IdPasien, IdPasien) == 0)
        {
            count = 1;
            printf("\nData Pasien %d\n", i + 1);
            printDataPasien((*pasien)[i]);

            printf("Masukkan Data Baru\n");
            char temp[100];
            printf("Masukkan nama pasien: ");
            fgets(temp, 100, stdin);
            temp[strcspn(temp, "\n")] = '\0';
            (*pasien)[i].nama = strdup(temp);

            printf("Masukkan alamat pasien: ");
            fgets(temp, 100, stdin);
            temp[strcspn(temp, "\n")] = '\0';
            (*pasien)[i].alamat = strdup(temp);

            printf("Masukkan kota pasien: ");
            fgets(temp, 100, stdin);
            temp[strcspn(temp, "\n")] = '\0';
            (*pasien)[i].kota = strdup(temp);

            printf("Masukkan tempat lahir pasien: ");
            fgets(temp, 100, stdin);
            temp[strcspn(temp, "\n")] = '\0';
            (*pasien)[i].tempatLahir = strdup(temp);

            printf("Masukkan tanggal lahir pasien (dd-mm-yyyy): ");
            scanf("%d-%d-%d", &(*pasien)[i].tanggalLahir.tanggal, &(*pasien)[i].tanggalLahir.bulan, &(*pasien)[i].tanggalLahir.tahun);

            (*pasien)[i].umur = hitungUmur((*pasien)[i].tanggalLahir.tanggal, (*pasien)[i].tanggalLahir.bulan, (*pasien)[i].tanggalLahir.tahun);
            
            fgets(temp, 100, stdin);


            int cekBPJS = 0;
            do{
                printf("Masukkan nomor BPJS pasien: ");
                fgets(temp, 20, stdin);
                temp[strcspn(temp, "\n")] = '\0';

                cekBPJS = cekNoBPJS(temp, *pasien, jumlahPasien, IdPasien);
                if(cekBPJS == 1){
                    printf("Nomor BPJS telah terdaftar\n");
                    printf("Pasien dengan nomor BPJS tersebut adalah: \n");
                    for(int j = 0; j < jumlahPasien; j++){
                        if(strcmp((*pasien)[j].nomorBPJS, temp) == 0){
                            printDataPasien((*pasien)[j]);
                        }
                    }

                    printf("\n");
                    printf("Lanjut mengubah data pasien? (y/n): ");
                    char confirm;
                    scanf("%s", &confirm);
                    fgets(temp, 100, stdin);
                    if(confirm == 'n'){
                        cekBPJS = 0;
                        break;
                    }else{
                        printf("Masukkan nomor BPJS yang benar\n");
                    }
                }else{
                    (*pasien)[i].nomorBPJS = strdup(temp);
                }
            }while(cekBPJS == 1);
            

            printf("Data pasien berhasil diubah\n");
        }
    }
    if (count == 0)
    {
        printf("Data pasien tidak ditemukan\n");
    }
}

void hapusDataPasien(struct dataPasien **pasien, int *jumlahPasien)
{
    char IdPasien[15];
    char temp[15];
    printf("Masukkan ID Pasien: KX ");
    fgets(temp, 15, stdin);
    strcpy(IdPasien, "KX ");
    strcat(IdPasien, temp);
    IdPasien[strcspn(IdPasien, "\n")] = '\0';

    int count = 0;
    for (int i = 0; i < *jumlahPasien; i++)
    {
        if (strcmp((*pasien)[i].IdPasien, IdPasien) == 0)
        {
            count = 1;
            printf("\nData pasien yang akan dihapus %d\n", i + 1);
            printDataPasien((*pasien)[i]);

            for (int j = i; j < *jumlahPasien - 1; j++)
            {
                (*pasien)[j] = (*pasien)[j + 1];
                (*pasien)[j].no -= 1;
            }

            *pasien = (struct dataPasien *)realloc(*pasien, (*jumlahPasien - 1) * sizeof(struct dataPasien));
            *jumlahPasien -= 1;
            printf("Data pasien berhasil dihapus\n");
        }
    }
    
}