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

typedef struct PerBulan{
    int jan;
    int feb;
    int mar;
    int apr;
    int mei;
    int jun;
    int jul;
    int agu;
    int sep;
    int okt;
    int nov;
    int des;
}PerBulan;

typedef struct perTahun {
    char *penyakit;
    int tahun;
    int jumlahperTahun;
    PerBulan *bulan; 
}perTahun;

typedef struct pendapatanTahun {
    int tahun;
    int jumlahperTahun;
    PerBulan *bulan; 
}pendapatanTahun;


typedef struct DataPasienKontrol{
    char *IdPasien;
    char *nama;
    tanggal tanggalPeriksa;
    char *diagnosis;
    char *tindakan;
    int biaya;
}DataPasienKontrol;

#endif