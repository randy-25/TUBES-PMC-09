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
// -------- END OF TAMBAH DATA PASIEN PAGE --------


// -------- UBAH DATA RIWAYAT PASIEN PAGE --------
void reset_ubahRiwayat_pasien_page();

void on_back_ubahRiwayatPasien_gui(GtkButton *button, gpointer user_data);

void on_submit_ubahRiwayat_pasien_page(GtkButton *button, gpointer user_data);

GtkWidget *ubahRiwayat_form_page(int nomorRiwayat);

void on_ubah_riwayatPasien_gui(GtkButton *button, gpointer user_data);

void on_cari_riwayatPasien_ubahData_gui(GtkButton *button, gpointer user_data);

GtkWidget *RiwayatPasienPage_UbahData();
// -------- END OF UBAH DATA PASIEN PAGE --------

// -------- HAPUS DATA RIWAYAT PASIEN PAGE --------
void reset_hapusRiwayat_pasien_page();

void on_back_hapusRiwayatPasien_gui(GtkButton *button, gpointer user_data);

void on_hapus_riwayatPasien_gui(GtkButton *button, gpointer user_data);

void on_cari_riwayatPasien_hapusData_gui(GtkButton *button, gpointer user_data);

GtkWidget *RiwayatPasienPage_HapusData();
// -------- END OF HAPUS DATA PASIEN PAGE --------

// Base Page
GtkWidget *RiwayatPasienPage();

#endif