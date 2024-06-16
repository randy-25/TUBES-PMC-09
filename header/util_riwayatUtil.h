#ifndef RIWAYATUTIL_H
#define RIWAYATUTIL_H 

#include "util_getData.h"

void cariRiwayat(struct riwayat *riwayatPasien, int jumlahRiwayatPasien, char *IdPasien, struct riwayat **dataHolder, int *jumlahDataHolder, int *confirm, char **nameHolder, struct dataPasien *pasien, int jumlahPasien);

int biayaTindakan(char tindakan[100]);

void tambahRiwayat(struct riwayat **riwayatPasien, int *jumlahRiwayatPasien, char *IdPasien, char *tanggal_periksa, char *diagnosis, char *tindakan, char *tanggal_kontrol, struct riwayat *newRiwayatHolder,char **namaHolder, struct dataPasien *pasien, int jumlahPasien, int *confirm);

int cekNomorRiwayat(int nomorRiwayat, char *IdPasien, struct riwayat *riwayatPasien);

void ubahRiwayat(struct riwayat **riwayatPasien, int jumlahRiwayatPasien, int nomorRiwayat, char *tanggal_periksa, char *diagnosis, char *tindakan, char *tanggal_kontrol, struct riwayat *newRiwayatHolder, char **namaHolder, struct dataPasien *pasien, int jumlahPasien);

void hapusRiwayat(struct riwayat **riwayatPasien, int *jumlahRiwayatPasien, int nomorRiwayat);

#endif