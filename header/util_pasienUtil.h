#ifndef PASIENUTIL_H
#define PASIENUTIL_H

#include <time.h>

#include "util_getData.h"
#include "util_riwayatUtil.h"

void cariPasien(struct dataPasien *pasien, int jumlahPasien, char *IdPasien, struct dataPasien *dataHolder, int *confirm);
int hitungUmur(int tanggal, int bulan, int tahun);
void tambahPasien(struct dataPasien **pasien, int *jumlahPasien, char *noBPJS_input, char *nama_input, char *alamat_input, char *kota_input, char *tempatLahir_input, char *tanggalLahir_input, struct dataPasien *newPasienHolder, int *confirm);
void ubahDataPasien(struct dataPasien **pasien, int jumlahPasien, char *IdPasien, char *noBPJS_input, char *nama_input, char *alamat_input, char *kota_input, char *tempatLahir_input, char *tanggalLahir_input, struct dataPasien *newPasienHolder, int *confirm);
void hapusDataPasien(struct dataPasien **pasien, int *jumlahPasien, char *IdPasien, struct riwayat **riwayatPasien, int *jumlahRiwayatPasien, int *confirm);

#endif