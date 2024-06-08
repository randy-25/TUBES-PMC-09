#ifndef RIWAYATUTIL_H
#define RIWAYATUTIL_H 

#include "dataType.h"

void cariRiwayat(struct riwayat *riwayatPasien, int jumlahRiwayatPasien);
int biayaTindakan(char tindakan[100]);
void tambahRiwayat(struct riwayat **riwayatPasien, int *jumlahRiwayatPasien);
void ubahRiwayat(struct riwayat **riwayatPasien, int jumlahRiwayatPasien);
void hapusRiwayat(struct riwayat **riwayatPasien, int *jumlahRiwayatPasien);

#endif