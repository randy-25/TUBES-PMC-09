#ifndef GUI_RIWAYATPASIENPAGE_H
#define GUI_RIWAYATPASIENPAGE_H


#include "util_getData.h"
#include "util_riwayatUtil.h"
#include "gui_basePage.h"

// RIWAYAT PASIEN PAGE

// ------- CARI DATA RIWAYAT PASIEN PAGE -------
// Reset Cari Riwayat Pasien Page
void reset_cari_riwayatPasien_page();

// Back to previous page button click
void on_back_cariRiwayatPasien_gui(GtkButton *button, gpointer user_data);

// Callback function to search patient data
void on_cari_riwayatPasien_data_gui(GtkButton *button, gpointer user_data);

GtkWidget *RiwayatPasienPage_CariData();
// -------- END OF CARI DATA PASIEN PAGE --------

// ------- TAMBAH DATA RIWAYAT PASIEN PAGE -------
void reset_tambahRiwayat_pasien_page();

void on_back_tambahRiwayatPasien_gui(GtkButton *button, gpointer user_data);

GtkWidget *ShowNewRiwayatDataPage(struct riwayat *new_riwayat, char *namaHolder, void callBackFunction(GtkButton *button, gpointer user_data));

void on_submit_riwayat_pasien(GtkButton *button, gpointer user_data);

GtkWidget *RiwayatPasienPage_TambahData();

// Base Page
GtkWidget *RiwayatPasienPage();

#endif