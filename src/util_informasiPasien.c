#include "../header/util_informasiPasienUtil.h"

void informasiPasien (struct dataPasien *dataPasien, struct riwayat *riwayatPasien, int jumlahDataPasien, int jumlahRiwayatPasien)
{
    char tempIdPasien[30];

    printf("Masukkan ID Pasien : ");
    fgets(tempIdPasien, 29, stdin);

    size_t len = strlen(tempIdPasien);
    if (len > 0 && tempIdPasien[len - 1] == '\n') {
        tempIdPasien[len - 1] = '\0';
    }

    int valid = 0;

    for (int i = 0; i < jumlahDataPasien ; i++)
    {
        if (strcmp(tempIdPasien, dataPasien[i].IdPasien) == 0)
        {
            printf("Nama         : %s \n" , dataPasien[i].nama);
            printf("ID Pasien    : %s \n" , dataPasien[i].IdPasien);
            printf("Umur         : %d \n" , dataPasien[i].umur);
            printf("Tempat, tanggal lahir    : %s %d %d %d \n" , dataPasien[i].tempatLahir, dataPasien[i].tanggalLahir.tanggal, dataPasien[i].tanggalLahir.bulan, dataPasien[i].tanggalLahir.tahun);
            printf("Kota         : %s \n" , dataPasien[i].kota);
            printf("No BPJS      : %s \n" , dataPasien[i].nomorBPJS);
            valid = 1;
            break;
        }
    }

    if (valid == 0)
    {
        printf("Tidak ada Pasien dengan ID tersebut \n");
        return;
    }

    printf("\n");
    printf("Riwayat Pasien \n");
    printf("\n");

    for (int j = 0; j < jumlahRiwayatPasien; j++)
    {
        if (strcmp(tempIdPasien, riwayatPasien[j].IdPasien) == 0)
        {
            printf("Tanggal Periksa  : %d-%d-%d\n", riwayatPasien[j].tanggalPeriksa.tanggal,  riwayatPasien[j].tanggalPeriksa.bulan,  riwayatPasien[j].tanggalPeriksa.tahun);
            printf("Diagnosis   : %s", riwayatPasien[j].diagnosis);
            printf("\n");
        }
    }
}