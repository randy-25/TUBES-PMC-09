#include <stdio.h>
#include <stdlib.h>
#include "header/getDataCSV.h"

int main(){
    struct dataPasien *pasien = NULL;
    struct riwayat *riwayatPasien = NULL;
    struct biaya *biayaPerawatan = NULL;
    int *jumlahPasien = malloc(sizeof(int));
    int *jumlahRiwayatPasien = malloc(sizeof(int));

    get_DataPasien_CSV(&pasien, jumlahPasien);
    get_RiwayatPasien_CSV(&riwayatPasien, jumlahRiwayatPasien);
    get_BiayaTindakan_CSV(&biayaPerawatan);

    //print data pasien
    printf("%d\n", jumlahPasien);
    for (int i = 0; i < *jumlahPasien; i++){
        printDataPasien_CSV(pasien[i]);
    }

    //print riwayat pasien
    for (int i = 0; i < *jumlahRiwayatPasien; i++){
        printRiwayatPasien_CSV(riwayatPasien[i]);
    }

    // Free allocated memory
    for (int i = 0; i < *jumlahPasien; i++) {
        free(pasien[i].nama);
        free(pasien[i].alamat);
        free(pasien[i].kota);
        free(pasien[i].tempatLahir);
        free(pasien[i].nomorBPJS);
        free(pasien[i].IdPasien);
    }
    free(pasien);

    for (int i = 0; i < *jumlahRiwayatPasien; i++) {
        free(riwayatPasien[i].IdPasien);
        free(riwayatPasien[i].diagnosis);
        free(riwayatPasien[i].tindakan);
    }
    free(riwayatPasien);

    return 0;

}