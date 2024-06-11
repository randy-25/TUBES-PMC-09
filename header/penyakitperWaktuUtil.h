#ifndef PENYAKITPERWAKTUUTIL_H
#define PENYAKITPERWAKTUUTIL_H

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

int cekdataTahun (int *daftarTahun, int Tahun);
int cekdataPenyakit (char (*daftarPenyakit)[50], char penyakit[50]);
void tambahData (struct perTahun **data, int bulan, int index);
void DataPenyakitperWaktu (struct riwayat *RiwayatPasien, int jumlahRiwayatPasien);

#endif