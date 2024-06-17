#ifndef SAVEDATA_H
#define SAVEDATA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dataType.h"

const char* getMonthName_CSV(int month);
void write_DataPasien_CSV(const struct dataPasien *Data, int JumlahDataPasien, const char *filename);
void write_RiwayatPasien_CSV(const struct riwayat *RiwayatPasien, int JumlahRiwayatPasien, const char *filename);

#endif