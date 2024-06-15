#ifndef LAPORANPENDAPATANUTIL_H
#define LAPORANPENDAPATANUTIL_H

#include "util_getData.h"

int cekdataPendapatanTahun (int *daftarTahun, int Tahun);
void tambahPendapatan (struct pendapatanTahun **data, int bulan, int index, int pendapatan);
void LaporanPendapatan (struct riwayat *RiwayatPasien, int jumlahRiwayatPasien, struct pendapatanTahun **Hasil, int tahun, int *confirm);

#endif