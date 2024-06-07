#ifndef DATA_TYPE_H
#define DATA_TYPE_H

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

#endif