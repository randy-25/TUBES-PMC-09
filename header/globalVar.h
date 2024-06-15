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

// ------- RIWAYAT PASIEN PAGE -------
extern GtkWidget *riwayatPasienPage_Stack;

// CARI DATA PASIEN PAGE VARIABLE
extern GtkWidget *riwayatPasienPage_cariRiwayat_pasienInfo;

// TAMBAH DATA PASIEN PAGE VARIABLE
extern GtkWidget *riwayatPasienPage_tambahData_pasienInfo;


#endif