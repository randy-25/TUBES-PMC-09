#ifndef PASIENKONTROLUTIL_H
#define PASIENKONTROLUTIL_H

#include "util_getData.h"

void findNamaPasien(char *idPasien, struct dataPasien *dataPasien, int jumlahDataPasien, char **namaPasien);

void pasienKontrol (struct dataPasien *dataPasien, int jumlahDataPasien, struct riwayat *riwayatPasien, int jumlahRiwayatPasien, struct tanggal tanggalKontrol, struct DataPasienKontrol **newDataPasienKontrol, int *jumlahDataPasienKontrol);


#endif