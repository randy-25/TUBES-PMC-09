#ifndef GETDATA_H
#define GETDATA_H

typedef struct tanggal
{
    int tanggal;
    int bulan;
    int tahun;
} tanggal;

typedef struct dataPasien
{
    int no;
    char *nama;
    char *alamat;
    char *kota;
    char *tempatLahir;
    tanggal tanggalLahir;
    int umur;
    char *nomorBPJS;
    char *IdPasien;
} dataPasien;

typedef struct riwayat
{
    int no;
    tanggal tanggalPeriksa;
    char *IdPasien;
    char *diagnosis;
    char *tindakan;
    tanggal tanggalKontrol;
    int biaya;
} riwayat;

typedef struct biaya
{
    int pendaftaran;
    int pemeriksaan;
    int vaksinasi;
    int cekGulaDarah;
    int pemasanganInfus;
    int pengobatan;
} biaya;

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
