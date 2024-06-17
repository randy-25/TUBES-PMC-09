#ifndef PENYAKITPERWAKTUUTIL_H
#define PENYAKITPERWAKTUUTIL_H

#include "util_getData.h"

int cekdataTahun (int *daftarTahun, int Tahun);
int cekdataPenyakit (char (*daftarPenyakit)[50], char penyakit[50]);
void tambahData (struct perTahun **data, int bulan, int index);
void DataPenyakitperWaktu (struct riwayat *RiwayatPasien, int jumlahRiwayatPasien, struct sortPenyakit **Result, int *confirm, int *jumlahPenyakit, int tahunprint);

#endif