#ifndef PASIENKONTROLUTIL_H
#define PASIENKONTROLUTIL_H

#include "util_getData.h"

void pasienKontrol (struct dataPasien *dataPasien, struct riwayat *riwayatPasien, int jumlahDataPasien, int jumlahRiwayatPasien, char *temp_tanggalKontrol, int **indexDataPasien, int **indexRiwayatPasien, int *countpasien);
int dataPasienIndex (struct dataPasien *dataPasien, char *IDPasien, int jumlahDataPasien);

#endif