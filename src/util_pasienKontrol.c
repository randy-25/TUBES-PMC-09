#include "../header/util_pasienKontrolUtil.h"


void findNamaPasien(char *idPasien, struct dataPasien *dataPasien, int jumlahDataPasien, char **namaPasien)
{
    for (int i = 0; i < jumlahDataPasien; i++)
    {
        if (strcmp(dataPasien[i].IdPasien, idPasien) == 0)
        {
            *namaPasien = strdup(dataPasien[i].nama);
            break;
        }
    }
}

void pasienKontrol (struct dataPasien *dataPasien, int jumlahDataPasien, struct riwayat *riwayatPasien, int jumlahRiwayatPasien, struct tanggal tanggalKontrol, struct DataPasienKontrol **newDataPasienKontrol, int *jumlahDataPasienKontrol)
{
    // printf("Tanggal Kontrol: %d-%d-%d\n", tanggalKontrol.tanggal, tanggalKontrol.bulan, tanggalKontrol.tahun);
    // printf("jumlahRiwayatPasien: %d\n", jumlahRiwayatPasien);
    for (int i = 0; i < jumlahRiwayatPasien; i++)
    {   
        // printf("%d Tanggal Riwayat Pasien: %d-%d-%d\n", (i+1),riwayatPasien[i].tanggalKontrol.tanggal, riwayatPasien[i].tanggalKontrol.bulan, riwayatPasien[i].tanggalKontrol.tahun);
        if (tanggalKontrol.tanggal == riwayatPasien[i].tanggalKontrol.tanggal && tanggalKontrol.bulan == riwayatPasien[i].tanggalKontrol.bulan && tanggalKontrol.tahun == riwayatPasien[i].tanggalKontrol.tahun)
        {   
            // printf("ID Pasien: %s\n", riwayatPasien[i].IdPasien);
            *jumlahDataPasienKontrol += 1;
            if(*newDataPasienKontrol == NULL)
            {
                *newDataPasienKontrol = (struct DataPasienKontrol *) malloc(sizeof(struct DataPasienKontrol));
            }
            else
            {
                *newDataPasienKontrol = (struct DataPasienKontrol *) realloc(*newDataPasienKontrol, *jumlahDataPasienKontrol * sizeof(struct DataPasienKontrol));
            }
            (*newDataPasienKontrol)[*jumlahDataPasienKontrol - 1].IdPasien = strdup(riwayatPasien[i].IdPasien);
            // (*newDataPasienKontrol)[*jumlahDataPasienKontrol - 1].nama = strdup(dataPasien[i].nama);

            findNamaPasien(riwayatPasien[i].IdPasien, dataPasien, jumlahDataPasien, &(*newDataPasienKontrol)[*jumlahDataPasienKontrol - 1].nama);

            (*newDataPasienKontrol)[*jumlahDataPasienKontrol - 1].tanggalPeriksa.tanggal = riwayatPasien[i].tanggalPeriksa.tanggal;

            (*newDataPasienKontrol)[*jumlahDataPasienKontrol - 1].tanggalPeriksa.bulan = riwayatPasien[i].tanggalPeriksa.bulan;

            (*newDataPasienKontrol)[*jumlahDataPasienKontrol - 1].tanggalPeriksa.tahun = riwayatPasien[i].tanggalPeriksa.tahun;

            (*newDataPasienKontrol)[*jumlahDataPasienKontrol - 1].diagnosis = strdup(riwayatPasien[i].diagnosis);

            (*newDataPasienKontrol)[*jumlahDataPasienKontrol - 1].tindakan = strdup(riwayatPasien[i].tindakan);

            (*newDataPasienKontrol)[*jumlahDataPasienKontrol - 1].biaya = riwayatPasien[i].biaya;
        }
    }
}