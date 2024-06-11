#include <stdio.h>
#include <stdlib.h>
#include "header/getData.h"
#include "header/penyakitperWaktuUtil.h"

int main() {
    // Declare pointers to hold patient and medical history data
    struct dataPasien *pasien = NULL; // data sheets 1
    struct riwayat *riwayatPasien = NULL; // data sheets 2
    struct biaya *biayaPerawatan = NULL; // data sheets 3 (biaya, static)
    int jumlahPasien = 0;
    int jumlahRiwayatPasien = 0;

    // Call getData function to read data from the Excel file
    getData(&pasien, &riwayatPasien, &jumlahPasien, &jumlahRiwayatPasien);
    getBiaya(&biayaPerawatan);
    

    // // Print out the patient data
    // printf("Jumlah Pasien: %d\n", jumlahPasien);
    // for (int i = 0; i < jumlahPasien; i++) {
    //     printf("\nData Pasien %d\n", i + 1);
    //     printDataPasien(pasien[i]);
    // }

    // // Print out the medical history data
    // printf("\nJumlah Riwayat Pasien: %d\n", jumlahRiwayatPasien);
    // for (int i = 0; i < jumlahRiwayatPasien; i++) {
    //     printf("\nRiwayat Pasien %d\n", i + 1);
    //     printRiwayatPasien(riwayatPasien[i]);
    // }

    //debug DataPenyakitperWaktu
    DataPenyakitperWaktu (riwayatPasien, jumlahRiwayatPasien);

    // Free allocated memory
    for (int i = 0; i < jumlahPasien; i++) {
        free(pasien[i].nama);
        free(pasien[i].alamat);
        free(pasien[i].kota);
        free(pasien[i].tempatLahir);
        free(pasien[i].nomorBPJS);
        free(pasien[i].IdPasien);
    }
    free(pasien);

    for (int i = 0; i < jumlahRiwayatPasien; i++) {
        free(riwayatPasien[i].IdPasien);
        free(riwayatPasien[i].diagnosis);
        free(riwayatPasien[i].tindakan);
    }
    free(riwayatPasien);

    return 0;
}
