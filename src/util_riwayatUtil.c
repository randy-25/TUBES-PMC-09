#include "../header/util_riwayatUtil.h"

void cariRiwayat(struct riwayat *riwayatPasien, int jumlahRiwayatPasien, char *IdPasien, struct riwayat **dataHolder, int *jumlahDataHolder, int *confirm, char **nameHolder, struct dataPasien *pasien, int jumlahPasien)
{
    for (int i = 0; i < jumlahPasien; i++)
    {
        if (strcmp(pasien[i].IdPasien, IdPasien) == 0)
        {
            *nameHolder = strdup(pasien[i].nama);
        }
    }
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
            *confirm = 1;
        }
    }
    if (*confirm == 1)
    {
        struct riwayat tempRiwayat;

        char temp[100];
        tempRiwayat.IdPasien = strdup(IdPasien);

        parseTanggal(tanggal_periksa, &tempRiwayat.tanggalPeriksa.tanggal, &tempRiwayat.tanggalPeriksa.bulan, &tempRiwayat.tanggalPeriksa.tahun);

        tempRiwayat.diagnosis = strdup(diagnosis);

        tempRiwayat.tindakan = strdup(tindakan);

        parseTanggal(tanggal_kontrol, &tempRiwayat.tanggalKontrol.tanggal, &tempRiwayat.tanggalKontrol.bulan, &tempRiwayat.tanggalKontrol.tahun);

        tempRiwayat.biaya = biayaTindakan(tempRiwayat.tindakan);
        tempRiwayat.no = (*jumlahRiwayatPasien) + 1;
        if (*riwayatPasien == NULL)
        {
            *riwayatPasien = (struct riwayat *)malloc(sizeof(struct riwayat));
        }
        else
        {
            *riwayatPasien = (struct riwayat *)realloc(*riwayatPasien, (*jumlahRiwayatPasien + 1) * sizeof(struct riwayat));
        }
        (*riwayatPasien)[*jumlahRiwayatPasien] = tempRiwayat;
        (*newRiwayatHolder) = tempRiwayat;
        (*jumlahRiwayatPasien)++;
    }
}

int cekNomorRiwayat(int nomorRiwayat, char *IdPasien, struct riwayat *riwayatPasien)
{

    if (strcmp(riwayatPasien[nomorRiwayat - 1].IdPasien, IdPasien) == 0)
    {
        return 1;
    }

    return 0;
}

void ubahRiwayat(struct riwayat **riwayatPasien, int jumlahRiwayatPasien, int nomorRiwayat, char *tanggal_periksa, char *diagnosis, char *tindakan, char *tanggal_kontrol, struct riwayat *newRiwayatHolder, char **namaHolder, struct dataPasien *pasien, int jumlahPasien)
{
    struct riwayat tempRiwayat = (*riwayatPasien)[nomorRiwayat - 1];

    char temp[100];

    parseTanggal(tanggal_periksa, &tempRiwayat.tanggalPeriksa.tanggal, &tempRiwayat.tanggalPeriksa.bulan, &tempRiwayat.tanggalPeriksa.tahun);

    tempRiwayat.diagnosis = strdup(diagnosis);

    tempRiwayat.tindakan = strdup(tindakan);

    parseTanggal(tanggal_kontrol, &tempRiwayat.tanggalKontrol.tanggal, &tempRiwayat.tanggalKontrol.bulan, &tempRiwayat.tanggalKontrol.tahun);

    tempRiwayat.biaya = biayaTindakan(tempRiwayat.tindakan);

    (*riwayatPasien)[nomorRiwayat - 1] = tempRiwayat;
    (*newRiwayatHolder) = tempRiwayat;

    for (int i = 0; i < jumlahPasien; i++)
    {
        if (strcmp(pasien[i].IdPasien, tempRiwayat.IdPasien) == 0)
        {
            *namaHolder = strdup(pasien[i].nama);
        }
    }
}

void hapusRiwayat(struct riwayat **riwayatPasien, int *jumlahRiwayatPasien, int nomorRiwayat)
{

    for (int i = nomorRiwayat - 1; i < *jumlahRiwayatPasien - 1; i++)
    {
        (*riwayatPasien)[i] = (*riwayatPasien)[i + 1];
        (*riwayatPasien)[i].no = i + 1;
    }
    (*jumlahRiwayatPasien)--;
    (*riwayatPasien) = (struct riwayat *)realloc((*riwayatPasien), (*jumlahRiwayatPasien) * sizeof(struct riwayat));
}