#include "../header/util_pasienKontrolUtil.h"

int dataPasienIndex (struct dataPasien *dataPasien, char *IDPasien, int jumlahDataPasien)
{
    for (int i = 0; i < jumlahDataPasien; i++)
    {
        if (strcmp(dataPasien[i].IdPasien, IDPasien) == 0)
        {   
            return i;
        }
    }
}

void pasienKontrol (struct dataPasien *dataPasien, struct riwayat *riwayatPasien, int jumlahDataPasien, int jumlahRiwayatPasien, char *temp_tanggalKontrol, int **indexDataPasien, int **indexRiwayatPasien, int *countpasien)
{
    *countpasien = 0;
    int tempDate, tempMonth, tempYears;

    parseTanggal(temp_tanggalKontrol, &tempDate, &tempMonth, &tempYears);

    printf("Pasien yang perlu Kontrol : \n");
    for (int i = 0; i < jumlahRiwayatPasien; i++)
    {   
        if (tempDate == riwayatPasien[i].tanggalKontrol.tanggal && tempMonth == riwayatPasien[i].tanggalKontrol.bulan && tempYears == riwayatPasien[i].tanggalKontrol.tahun)
        {   
            // printPatientName(dataPasien, riwayatPasien[i].IdPasien, jumlahDataPasien);
            // printf("ID Pasien  : %s\n", riwayatPasien[i].IdPasien);
            // printf("Diagnosis  : %s\n", riwayatPasien[i].diagnosis);

            //store data
            *indexDataPasien[*countpasien] = dataPasienIndex(dataPasien, riwayatPasien[i].IdPasien, jumlahDataPasien);
            *indexRiwayatPasien[*countpasien] = i;
            *countpasien++;
        }
    }
}