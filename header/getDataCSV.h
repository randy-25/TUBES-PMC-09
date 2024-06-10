#ifndef GETDATA_H
#define GETDATA_H

#include "dataType.h"

int getMonthNumber(const char *monthName);
int is_format(char *Date);
void printDataPasien (struct dataPasien DataPasien);
void printRiwayatPasien (struct riwayat RiwayatPasien);
void parseDate (char *Date, int *day, int *month, int *year);
void get_DataPasien(struct dataPasien **Data, int *JumlahDataPasien);
void get_RiwayatPasien(struct riwayat **RiwayatPasien, int *JumlahRiwayatPasien);
void get_BiayaTindakan (struct biaya **BiayaPerawatan);

#endif