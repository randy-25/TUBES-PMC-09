#include "../header/util_riwayatUtil.h"

void cariRiwayat(struct riwayat *riwayatPasien, int jumlahRiwayatPasien)
{
    char IdPasien[15];
    char temp[15];
    printf("Masukkan ID Pasien: KX ");
    fgets(temp, 15, stdin);
    strcpy(IdPasien, "KX ");
    strcat(IdPasien, temp);
    IdPasien[strcspn(IdPasien, "\n")] = '\0';
    printf("ID Pasien: %s\n", IdPasien);
    for (int i = 0; i < jumlahRiwayatPasien; i++)
    {
        if (strcmp(riwayatPasien[i].IdPasien, IdPasien) == 0)
        {
            printf("\nRiwayat Pasien %d\n", i + 1);
            printRiwayatPasien(riwayatPasien[i]);
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

void tambahRiwayat(struct riwayat **riwayatPasien, int *jumlahRiwayatPasien)
{
    struct riwayat tempRiwayat;

    *riwayatPasien = (struct riwayat *)realloc(*riwayatPasien, (*jumlahRiwayatPasien + 1) * sizeof(struct riwayat));

    char temp[100];
    printf("Masukkan ID Pasien: KX ");
    fgets(temp, 20, stdin);
    temp[strcspn(temp, "\n")] = '\0';
    char tempNew[20];
    strcpy(tempNew, "KX ");
    strcat(tempNew, temp);
    tempRiwayat.IdPasien = strdup(tempNew);

    printf("Masukkan Tanggal Periksa (dd-mm-yyyy): ");
    scanf("%d-%d-%d", &tempRiwayat.tanggalPeriksa.tanggal, &tempRiwayat.tanggalPeriksa.bulan, &tempRiwayat.tanggalPeriksa.tahun);

    fgets(temp, 100, stdin);

    printf("Masukkan Diagnosis: ");
    fgets(temp, 100, stdin);
    temp[strcspn(temp, "\n")] = '\0';
    tempRiwayat.diagnosis = strdup(temp);

    printf("Masukkan Tindakan: ");
    fgets(temp, 100, stdin);
    temp[strcspn(temp, "\n")] = '\0';
    tempRiwayat.tindakan = strdup(temp);

    printf("Masukkan Tanggal Kontrol (dd-mm-yyyy): ");
    scanf("%d-%d-%d", &tempRiwayat.tanggalKontrol.tanggal, &tempRiwayat.tanggalKontrol.bulan, &tempRiwayat.tanggalKontrol.tahun);

    tempRiwayat.biaya = biayaTindakan(tempRiwayat.tindakan);
    tempRiwayat.no = (*jumlahRiwayatPasien) + 1;

    (*riwayatPasien)[*jumlahRiwayatPasien] = tempRiwayat;
    (*jumlahRiwayatPasien)++;
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