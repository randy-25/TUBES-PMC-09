#ifndef GETDATA_H
#define GETDATA_H

#include <xlsxio_read.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dataType.h"

void getDataPasien(struct dataPasien *pasien, char *value, int colIndex);
void printDataPasien(struct dataPasien pasien);
void getRiwayatPasien(struct riwayat *riwayatPasien, char *value, int colIndex);
void getBiaya(struct biaya **biaya);
void printRiwayatPasien(struct riwayat riwayatPasien);
int getMonthNumber(const char *monthName);
int isNumeric(const char *str);
void convertDaysToDate(int days, int *date, int *month, int *year);
void parseDateString(const char *dateString, int *date, int *month, int *year);
void getData(struct dataPasien **pasien, struct riwayat **riwayatPasien, int *jumlahPasien, int *jumlahRiwayatPasien);

#endif
