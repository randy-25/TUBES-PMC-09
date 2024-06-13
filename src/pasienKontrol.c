#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../header/getData.h"
#include "../header/pasienKontrolUtil.h"

void printPatientName (struct dataPasien *dataPasien, char *IDPasien, int jumlahDataPasien)
{
    for (int i = 0; i < jumlahDataPasien; i++)
    {
        if (strcmp(dataPasien[i].IdPasien, IDPasien) == 0)
        {
            printf("Nama Pasien : %s\n", dataPasien[i].nama);
            break;
        }
    }
}

void pasienKontrol (struct dataPasien *dataPasien, struct riwayat *riwayatPasien, int jumlahDataPasien, int jumlahRiwayatPasien)
{
    int tempDate;
    int tempMonth;
    int tempYears;

    int tempindex;

    int ada = 0;

    printf("Masukkan tanggal bulan tahun : (DD MM YYYY)\n");
    scanf("%d %d %d", &tempDate, &tempMonth, &tempYears);

    // Use getchar to consume the newline character left by scanf
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);

    printf("Pasien yang perlu Kontrol : \n");
    for (int i = 0; i < jumlahRiwayatPasien; i++)
    {   
        if (tempDate == riwayatPasien[i].tanggalKontrol.tanggal && tempMonth == riwayatPasien[i].tanggalKontrol.bulan && tempYears == riwayatPasien[i].tanggalKontrol.tahun)
        {   
            printPatientName(dataPasien, riwayatPasien[i].IdPasien, jumlahDataPasien);
            printf("ID Pasien  : %s\n", riwayatPasien[i].IdPasien);
            printf("Diagnosis  : %s\n", riwayatPasien[i].diagnosis);
            printf("\n");
            ada = 1;
        }
    }

    if (ada == 0)
    {
        printf("Tidak ada Pasien yang perlu kontrol\n");
    }
}