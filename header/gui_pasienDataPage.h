#ifndef GUI_PASIENDATAPAGE_H
#define GUI_PASIENDATAPAGE_H

#include "util_getData.h"
#include "util_pasienUtil.h"
#include "gui_basePage.h"

// DATA PASIEN PAGE

// -------- CARI DATA PASIEN PAGE --------
// reset the data pasien page
void reset_cariData_pasien_page();
// Back to previous page button click
void on_back_cariDataPasien_gui(GtkButton *button, gpointer user_data);
// Callback function to search patient data
void on_cari_pasien_data_gui(GtkButton *button, gpointer user_data);
GtkWidget *DataPasienPage_CariData();
// -------- END OF CARI DATA PASIEN PAGE --------

// -------- TAMBAH DATA PASIEN PAGE --------
void reset_tambahData_pasien_page();
void on_back_tambahDataPasien_gui(GtkButton *button, gpointer user_data);
GtkWidget *ShowNewPatientDataPage(struct dataPasien *new_patient, void callBackFunction(GtkButton *button, gpointer user_data));
void on_submit_data_pasien(GtkButton *button, gpointer user_data);
GtkWidget *DataPasienPage_TambahData();
// -------- END OF TAMBAH DATA PASIEN PAGE --------

// -------- UBAH DATA PASIEN PAGE --------
void reset_ubahData_pasien_page();
void on_back_ubahDataPasien_gui(GtkButton *button, gpointer user_data);
void on_submit_ubahData_pasien_page(GtkButton *button, gpointer user_data);
GtkWidget *ubahData_form_page(char *IdPasien_data);
void on_confirm_ubahData_pasien_page(GtkButton *button, gpointer user_data);
void on_cari_pasienData_ubahData_gui(GtkButton *button, gpointer user_data);
GtkWidget *DataPasienPage_UbahData();
// -------- END OF UBAH DATA PASIEN PAGE --------

// -------- HAPUS DATA PASIEN PAGE --------
void reset_hapusData_pasien_page();
void on_back_hapusDataPasien_gui(GtkButton *button, gpointer user_data);
void on_confirm_hapusData_pasien_page(GtkButton *button, gpointer user_data);
void on_cari_pasienData_hapusData_gui(GtkButton *button, gpointer user_data);
GtkWidget *DataPasienPage_HapusData();
// -------- END OF HAPUS DATA PASIEN PAGE --------

// -------- DATA PASIEN BASE PAGE --------
GtkWidget *DataPasienPage();
#endif