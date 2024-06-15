#ifndef GLOBAL_VAR_H
#define GLOBAL_VAR_H

#include "dataType.h"
#include "guiDataType.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define HEADER_HEIGHT 50
#define FOOTER_HEIGHT 50

// Global variables to store patient data
extern struct dataPasien *pasien;
extern struct riwayat *riwayatPasien;
extern int jumlahPasien;
extern int jumlahRiwayatPasien;

// Base Page
extern GtkWidget *stackContainer;
extern GtkWidget *landingPage;
extern GtkWidget *dataPasienPage;
extern GtkWidget *riwayatPasienPage;
extern GtkWidget *informasiPasienPage;
extern GtkWidget *laporanPendapatanPage;
extern GtkWidget *informasiPenyakitPage;
extern GtkWidget *informasiKontrolPage;

//---------- DATA PASIEN PAGE ----------
extern GtkWidget *dataPasienPage_Stack;
// CARI DATA PASIEN PAGE
extern GtkWidget *dataPasienPage_cariData_pasienInfo;

// TAMBAH DATA PASIEN PAGE
extern GtkWidget *dataPasienPage_tambahData_pasienInfo;

// UBAH DATA PASIEN PAGE VARIABLE
extern GtkWidget *dataPasienPage_ubahData_pasienInfo;

// HAPUS DATA PASIEN PAGE VARIABLE
extern GtkWidget *dataPasienPage_hapusData_pasienInfo;
//---------- END OF DATA PASIEN PAGE ----------


//---------- PENYAKIT PER WAKTU PAGE ----------
extern GtkWidget *penyakitperWaktuPage_Stack;

// DISPLAY PENYAKIT PAGE
extern GtkWidget *displayPenyakitPage;
//------- END OF PENYAKIT PER WAKTU PAGE -------


//---------- LAPORAN PENDAPATAN PAGE -----------
extern GtkWidget *laporanPendapatanPage_Stack;

// DISPLAY PENYAKIT PAGE
extern GtkWidget *displayPendapatanPage;
//------- END OF LAPORAN PENDAPATAN PAGE -------




#endif