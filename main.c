#include <stdio.h>
#include <stdlib.h>
#include "header/getData.h"
#include "header/riwayatUtil.h"
#include "header/pasienUtil.h"

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

    // UBAH DATA PASIEN_DEBUG
    // cariPasien(pasien, jumlahPasien);
    // tambahPasien(&pasien, &jumlahPasien);
    // ubahDataPasien(&pasien, jumlahPasien);
    // hapusDataPasien(&pasien, &jumlahPasien);
    // for(int i = 0; i < jumlahPasien; i++){
    //     printDataPasien(pasien[i]);
    // }

    // UBAH RIWAYAT_DEBUG
    // cariRiwayat(riwayatPasien, jumlahRiwayatPasien);
    // tambahRiwayat(&riwayatPasien, &jumlahRiwayatPasien);
    // printRiwayatPasien(riwayatPasien[jumlahRiwayatPasien - 1]);
    // ubahRiwayat(&riwayatPasien, jumlahRiwayatPasien);
    // hapusRiwayat(&riwayatPasien, &jumlahRiwayatPasien);
    // for(int i = 0; i < jumlahRiwayatPasien; i++){
    //     printRiwayatPasien(riwayatPasien[i]);
    // }

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

    free(biayaPerawatan);
    return 0;
}
