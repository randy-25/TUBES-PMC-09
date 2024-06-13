#ifndef PASIENUTIL_H
#define PASIENUTIL_H

void cariPasien(struct dataPasien *pasien, int jumlahPasien, char *IdPasien, struct dataPasien *dataHolder);
int hitungUmur(int tanggal, int bulan, int tahun);
void tambahPasien(struct dataPasien **pasien, int *jumlahPasien);
void ubahDataPasien(struct dataPasien **pasien, int jumlahPasien);
void hapusDataPasien(struct dataPasien **pasien, int *jumlahPasien);
void printDataPasien(struct dataPasien pasien);

#endif