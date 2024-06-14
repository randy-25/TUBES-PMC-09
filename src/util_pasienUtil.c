#include "../header/util_pasienUtil.h"

void cariPasien(struct dataPasien *pasien, int jumlahPasien, char *IdPasien, struct dataPasien *dataHolder, int *confirm)
{
    // printf("ID Pasien: %s\n", IdPasien);
    *confirm = 0;
    for (int i = 0; i < jumlahPasien; i++)
    {
        if (strcmp(pasien[i].IdPasien, IdPasien) == 0)
        {
            *dataHolder = pasien[i];
            *confirm = 1;
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
    if (currentMonth < bulan)
    {
        umur -= 1;
    }
    else if (currentMonth == bulan)
    {
        if (currentDay < tanggal)
        {
            umur -= 1;
        }
    }
    return umur;
}

void parseTanggalLahir(char *tanggalLahir_input, int *tanggal, int *bulan, int *tahun)
{
    char *token;
    token = strtok(tanggalLahir_input, "-");
    *tanggal = atoi(token);
    token = strtok(NULL, "-");
    *bulan = atoi(token);
    token = strtok(NULL, "-");
    *tahun = atoi(token);
}

void tambahPasien(struct dataPasien **pasien, int *jumlahPasien, char *noBPJS_input, char *nama_input, char *alamat_input, char *kota_input, char *tempatLahir_input, char *tanggalLahir_input, struct dataPasien *newPasienHolder, int *confirm)
{
    struct dataPasien tempPasien;

    (*pasien) = (struct dataPasien *)realloc(*pasien, (*jumlahPasien + 1) * sizeof(struct dataPasien));

    // char temp[100];
    // printf("Masukkan Nomor BPJS pasien: ");
    // fgets(temp, 20, stdin);
    // temp[strcspn(temp, "\n")] = '\0';
    *confirm = 0;
    int cek = 0;
    for (int i = 0; i < *jumlahPasien; i++)
    {
        if (strcmp((*pasien)[i].nomorBPJS, noBPJS_input) == 0)
        {
            cek += 1;
            *newPasienHolder = (*pasien)[i];
        }
    }
    if (cek == 0)
    {
        tempPasien.nomorBPJS = strdup(noBPJS_input);

        // printf("Masukkan Nama Pasien: ");
        // fgets(temp, 100, stdin);
        // temp[strcspn(temp, "\n")] = '\0';
        tempPasien.nama = strdup(nama_input);

        // printf("Masukkan Alamat Pasien: ");
        // fgets(temp, 100, stdin);
        // temp[strcspn(temp, "\n")] = '\0';
        tempPasien.alamat = strdup(alamat_input);

        // printf("Masukkan Kota Pasien: ");
        // fgets(temp, 100, stdin);
        // temp[strcspn(temp, "\n")] = '\0';
        tempPasien.kota = strdup(kota_input);

        // printf("Masukkan Tempat Lahir Pasien: ");
        // fgets(temp, 100, stdin);
        // temp[strcspn(temp, "\n")] = '\0';
        tempPasien.tempatLahir = strdup(tempatLahir_input);

        // printf("Masukkan Tanggal Lahir Pasien (dd-mm-yyyy): ");
        // scanf("%d-%d-%d", &tempPasien.tanggalLahir.tanggal, &tempPasien.tanggalLahir.bulan, &tempPasien.tanggalLahir.tahun);
        parseTanggalLahir(tanggalLahir_input, &tempPasien.tanggalLahir.tanggal, &tempPasien.tanggalLahir.bulan, &tempPasien.tanggalLahir.tahun);

        tempPasien.umur = hitungUmur(tempPasien.tanggalLahir.tanggal, tempPasien.tanggalLahir.bulan, tempPasien.tanggalLahir.tahun);

        int prevId;
        char tempId[15];
        char *token;
        if (*jumlahPasien == 0)
        {
            prevId = 1230123;
        }
        else
        {
            strcpy(tempId, (*pasien)[*jumlahPasien - 1].IdPasien);
            token = strtok(tempId, " ");
            token = strtok(NULL, " ");
            prevId = atoi(token);
        }

        char temp[15];
        prevId += 1;
        strcpy(tempId, "KX ");
        sprintf(temp, "%d", prevId);
        strcat(tempId, temp);
        tempPasien.IdPasien = strdup(tempId);

        tempPasien.no = (*jumlahPasien) + 1;

        (*pasien)[*jumlahPasien] = tempPasien;
        *newPasienHolder = tempPasien;
        (*jumlahPasien)++;
        *confirm = 1;
    }
}

int cekNoBPJS(char *nomorBPJS, struct dataPasien *pasien, int jumlahPasien, char *IdPasien, struct dataPasien *newPasienHolder)
{
    for (int i = 0; i < jumlahPasien; i++)
    {
        if (strcmp(pasien[i].nomorBPJS, nomorBPJS) == 0 && strcmp(pasien[i].IdPasien, IdPasien) != 0)
        {   
            *newPasienHolder = pasien[i];
            return 1;
        }
    }
    return 0;
}

void ubahDataPasien(struct dataPasien **pasien, int jumlahPasien, char *IdPasien, char *noBPJS_input, char *nama_input, char *alamat_input, char *kota_input, char *tempatLahir_input, char *tanggalLahir_input, struct dataPasien *newPasienHolder, int *confirm)
{
    int count = 0;
    for (int i = 0; i < jumlahPasien; i++)
    {
        if (strcmp((*pasien)[i].IdPasien, IdPasien) == 0)
        {
            count = 1;

            (*pasien)[i].nama = strdup(nama_input);
            (*pasien)[i].alamat = strdup(alamat_input);
            (*pasien)[i].kota = strdup(kota_input);
            (*pasien)[i].tempatLahir = strdup(tempatLahir_input);

            parseTanggalLahir(tanggalLahir_input, &(*pasien)[i].tanggalLahir.tanggal, &(*pasien)[i].tanggalLahir.bulan, &(*pasien)[i].tanggalLahir.tahun);
            (*pasien)[i].umur = hitungUmur((*pasien)[i].tanggalLahir.tanggal, (*pasien)[i].tanggalLahir.bulan, (*pasien)[i].tanggalLahir.tahun);

            int cekBPJS = 0;
            char temp[100];
            strcpy(temp, noBPJS_input);
            cekBPJS = cekNoBPJS(temp, *pasien, jumlahPasien, IdPasien, newPasienHolder);
            if (cekBPJS == 1)
            {
                *confirm = 0;
            }
            else
            {
                *confirm = 1;
                (*pasien)[i].nomorBPJS = strdup(noBPJS_input);
                *newPasienHolder = (*pasien)[i];
            }
        }
    }
    if (count == 0)
    {
        *confirm = 0;
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