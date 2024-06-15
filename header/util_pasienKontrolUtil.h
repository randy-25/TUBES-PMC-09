#ifndef PASIENKONTROLUTIL_H
#define PASIENKONTROLUTIL_H

#include "util_getData.h"

void pasienKontrol (struct dataPasien *dataPasien, struct riwayat *riwayatPasien, int jumlahDataPasien, int jumlahRiwayatPasien, int tempDate, int tempMonth, int tempYears, int **indexDataPasien, int **indexRiwayatPasien, int *countpasien);
int dataPasienIndex (struct dataPasien *dataPasien, char *IDPasien, int jumlahDataPasien, int *indexpasien);

#endif