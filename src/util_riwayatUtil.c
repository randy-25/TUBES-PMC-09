#include "../header/util_riwayatUtil.h"

void cariRiwayat(struct riwayat *riwayatPasien, int jumlahRiwayatPasien, char *IdPasien, struct riwayat **dataHolder, int *jumlahDataHolder, int *confirm, char **nameHolder, struct dataPasien *pasien, int jumlahPasien)
{
    for(int i = 0; i < jumlahPasien; i++){
        if(strcmp(pasien[i].IdPasien, IdPasien) == 0){
            *nameHolder = strdup(pasien[i].nama);
        }
    }
    // printf("jumlah riwayat: %d\n", jumlahRiwayatPasien);
    *confirm = 0;
    for (int i = 0; i < jumlahRiwayatPasien; i++)
    {
        if (strcmp(riwayatPasien[i].IdPasien, IdPasien) == 0)
        {
            *jumlahDataHolder += 1;
            if ((*dataHolder) == NULL)
            {
                (*dataHolder) = (struct riwayat *)malloc((*jumlahDataHolder) * sizeof(struct riwayat));
            }
            else
            {
                (*dataHolder) = (struct riwayat *)realloc((*dataHolder), (*jumlahDataHolder) * sizeof(struct riwayat));
            }
            (*dataHolder)[*jumlahDataHolder - 1] = riwayatPasien[i];
            *confirm = 1;
        }
    }
}

int biayaTindakan(char tindakan[100])
{
    if (strcmp(tindakan, "Pendaftaran") == 0)
    {
        return 15000;
    }
    else if (strcmp(tindakan, "Pemeriksaan") == 0)
    {
        return 140000;
    }
    else if (strcmp(tindakan, "Vaksinasi") == 0)
    {
        return 240000;
    }
    else if (strcmp(tindakan, "Cek Gula Darah") == 0)
    {
        return 165000;
    }
    else if (strcmp(tindakan, "Pemasangan Infus") == 0)
    {
        return 265000;
    }
    else if (strcmp(tindakan, "Pengobatan") == 0)
    {
        return 290000;
    }
    else
    {
        return 0;
    }
}

void tambahRiwayat(struct riwayat **riwayatPasien, int *jumlahRiwayatPasien, char *IdPasien, char *tanggal_periksa, char *diagnosis, char *tindakan, char *tanggal_kontrol, struct riwayat *newRiwayatHolder, char **namaHolder, struct dataPasien *pasien, int jumlahPasien, int *confirm)
{
    *confirm = 0;
    for (int i = 0; i < jumlahPasien; i++)
    {
        if (strcmp(pasien[i].IdPasien, IdPasien) == 0)
        {
            *namaHolder = strdup(pasien[i].nama);
            // strcpy(namaHolder, pasien[i].nama);
            *confirm = 1;
        }
    }
    if (*confirm == 1)
    {
        struct riwayat tempRiwayat;

        // *riwayatPasien = (struct riwayat *)realloc(*riwayatPasien, (*jumlahRiwayatPasien + 1) * sizeof(struct riwayat));

        char temp[100];
        tempRiwayat.IdPasien = strdup(IdPasien);

        parseTanggal(tanggal_periksa, &tempRiwayat.tanggalPeriksa.tanggal, &tempRiwayat.tanggalPeriksa.bulan, &tempRiwayat.tanggalPeriksa.tahun);

        tempRiwayat.diagnosis = strdup(diagnosis);

        tempRiwayat.tindakan = strdup(tindakan);

        parseTanggal(tanggal_kontrol, &tempRiwayat.tanggalKontrol.tanggal, &tempRiwayat.tanggalKontrol.bulan, &tempRiwayat.tanggalKontrol.tahun);

        tempRiwayat.biaya = biayaTindakan(tempRiwayat.tindakan);
        tempRiwayat.no = (*jumlahRiwayatPasien) + 1;
        if(*riwayatPasien == NULL){
            *riwayatPasien = (struct riwayat *)malloc(sizeof(struct riwayat));
        }else{
            *riwayatPasien = (struct riwayat *)realloc(*riwayatPasien, (*jumlahRiwayatPasien + 1) * sizeof(struct riwayat));
        }
        (*riwayatPasien)[*jumlahRiwayatPasien] = tempRiwayat;
        (*newRiwayatHolder) = tempRiwayat;
        (*jumlahRiwayatPasien)++;
    }
}

void ubahRiwayat(struct riwayat **riwayatPasien, int jumlahRiwayatPasien)
{
    char IdPasien[15];
    char temp[15];
    printf("Masukkan ID Pasien: KX ");
    fgets(temp, 15, stdin);
    strcpy(IdPasien, "KX ");
    strcat(IdPasien, temp);
    IdPasien[strcspn(IdPasien, "\n")] = '\0';

    int count = 0;
    riwayat *tempRiwayat = NULL;
    for (int i = 0; i < jumlahRiwayatPasien; i++)
    {
        if (strcmp((*riwayatPasien)[i].IdPasien, IdPasien) == 0)
        {
            if (tempRiwayat == NULL)
            {
                tempRiwayat = (struct riwayat *)malloc(sizeof(struct riwayat));
            }
            else
            {
                tempRiwayat = (struct riwayat *)realloc(tempRiwayat, (count + 1) * sizeof(struct riwayat));
            }

            tempRiwayat[count] = (*riwayatPasien)[i];
            count++;
            printRiwayatPasien((*riwayatPasien)[i]);
        }
    }
    if (count != 0)
    {
        int pilihan;
        printf("Pilih nomor riwayat pasien yang ingin diubah : ");
        scanf("%d", &pilihan);

        int cek = 0;
        for (int i = 0; i < count; i++)
        {
            if (pilihan == tempRiwayat[i].no)
            {
                cek += 1;
            }
        }
        if (cek != 1)
        {
            printf("Pilihan tidak sesuai\n");
        }
        else
        {
            printf("Masukkan data baru\n");
            char temp[100];
            printf("Masukkan Tanggal Periksa (dd-mm-yyyy): ");
            scanf("%d-%d-%d", &(*riwayatPasien)[pilihan - 1].tanggalPeriksa.tanggal, &(*riwayatPasien)[pilihan - 1].tanggalPeriksa.bulan, &(*riwayatPasien)[pilihan - 1].tanggalPeriksa.tahun);

            fgets(temp, 100, stdin);

            printf("Masukkan Diagnosis: ");
            fgets(temp, 100, stdin);
            temp[strcspn(temp, "\n")] = '\0';
            (*riwayatPasien)[pilihan - 1].diagnosis = strdup(temp);

            printf("Masukkan Tindakan: ");
            fgets(temp, 100, stdin);
            temp[strcspn(temp, "\n")] = '\0';
            (*riwayatPasien)[pilihan - 1].tindakan = strdup(temp);

            printf("Masukkan Tanggal Kontrol (dd-mm-yyyy): ");
            scanf("%d-%d-%d", &(*riwayatPasien)[pilihan - 1].tanggalKontrol.tanggal, &(*riwayatPasien)[pilihan - 1].tanggalKontrol.bulan, &(*riwayatPasien)[pilihan - 1].tanggalKontrol.tahun);

            (*riwayatPasien)[pilihan - 1].biaya = biayaTindakan((*riwayatPasien)[pilihan - 1].tindakan);
        }
    }
    else
    {
        printf("Tidak ada riwayat pasien dengan ID tersebut\n");
    }
}

void hapusRiwayat(struct riwayat **riwayatPasien, int *jumlahRiwayatPasien)
{
    char IdPasien[15];
    char temp[15];
    printf("Masukkan ID Pasien: KX ");
    fgets(temp, 15, stdin);
    strcpy(IdPasien, "KX ");
    strcat(IdPasien, temp);
    IdPasien[strcspn(IdPasien, "\n")] = '\0';

    int count = 0;
    riwayat *tempRiwayat = NULL;
    for (int i = 0; i < *jumlahRiwayatPasien; i++)
    {
        if (strcmp((*riwayatPasien)[i].IdPasien, IdPasien) == 0)
        {
            if (tempRiwayat == NULL)
            {
                tempRiwayat = (struct riwayat *)malloc(sizeof(struct riwayat));
            }
            else
            {
                tempRiwayat = (struct riwayat *)realloc(tempRiwayat, (count + 1) * sizeof(struct riwayat));
            }

            tempRiwayat[count] = (*riwayatPasien)[i];
            count++;
            printRiwayatPasien((*riwayatPasien)[i]);
        }
    }
    if (count != 0)
    {
        int pilihan;
        printf("Pilih nomor riwayat pasien yang ingin dihapus : ");
        scanf("%d", &pilihan);
        int cek = 0;
        for (int i = 0; i < count; i++)
        {
            if (pilihan == tempRiwayat[i].no)
            {
                cek += 1;
            }
        }
        if (cek != 1)
        {
            printf("Pilihan tidak sesuai\n");
        }
        else
        {
            for (int i = pilihan - 1; i < *jumlahRiwayatPasien - 1; i++)
            {
                (*riwayatPasien)[i] = (*riwayatPasien)[i + 1];
                (*riwayatPasien)[i].no = i + 1;
            }
            (*jumlahRiwayatPasien)--;
            (*riwayatPasien) = (struct riwayat *)realloc((*riwayatPasien), (*jumlahRiwayatPasien) * sizeof(struct riwayat));

            printf("Riwayat pasien berhasil dihapus\n");
        }
    }
    else
    {
        printf("Tidak ada riwayat pasien dengan ID tersebut\n");
    }
}