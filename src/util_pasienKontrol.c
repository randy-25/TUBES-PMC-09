#include "../header/util_pasienKontrolUtil.h"

int dataPasienIndex (struct dataPasien *dataPasien, char *IDPasien, int jumlahDataPasien, int *indexpasien)
{
    for (int i = 0; i < jumlahDataPasien; i++)
    {
        if (strcmp(dataPasien[i].IdPasien, IDPasien) == 0)
        {   
            return i;
        }
    }
}

void pasienKontrol (struct dataPasien *dataPasien, struct riwayat *riwayatPasien, int jumlahDataPasien, int jumlahRiwayatPasien, int tempDate, int tempMonth, int tempYears, int **indexDataPasien, int **indexRiwayatPasien, int *countpasien)
{
    int tempDate;
    int tempMonth;
    int tempYears;

    int tempindex;

    int ada = 0;
    *countpasien = 0;

    printf("Pasien yang perlu Kontrol : \n");
    for (int i = 0; i < jumlahRiwayatPasien; i++)
    {   
        if (tempDate == riwayatPasien[i].tanggalKontrol.tanggal && tempMonth == riwayatPasien[i].tanggalKontrol.bulan && tempYears == riwayatPasien[i].tanggalKontrol.tahun)
        {   
            printPatientName(dataPasien, riwayatPasien[i].IdPasien, jumlahDataPasien);
            printf("ID Pasien  : %s\n", riwayatPasien[i].IdPasien);
            printf("Diagnosis  : %s\n", riwayatPasien[i].diagnosis);

            //store data
            *indexDataPasien[*countpasien] = dataPasienIndex(dataPasien, riwayatPasien[i].IdPasien, jumlahDataPasien);
            *indexRiwayatPasien[*countpasien] = i;
            *countpasien++;
        }
    }
}