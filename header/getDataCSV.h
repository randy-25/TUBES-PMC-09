#ifndef GETDATACSV_H
#define GETDATACSV_H

#include "dataType.h"

int getMonthNumber_CSV(const char *monthName);
int is_format_CSV(char *Date);
void printDataPasien_CSV (struct dataPasien DataPasien);
void printRiwayatPasien_CSV (struct riwayat RiwayatPasien);
void parseDate_CSV (char *Date, int *day, int *month, int *year);
void get_DataPasien_CSV (struct dataPasien **Data, int *JumlahDataPasien);
void get_RiwayatPasien_CSV (struct riwayat **RiwayatPasien, int *JumlahRiwayatPasien);
void get_BiayaTindakan_CSV (struct biaya **BiayaPerawatan);

#endif