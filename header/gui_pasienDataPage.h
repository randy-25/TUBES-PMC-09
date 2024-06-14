#ifndef GUI_PASIENDATAPAGE_H
#define GUI_PASIENDATAPAGE_H

#include <stdio.h>
#include <stdlib.h>

#include "guiDataType.h"
#include "globalVar.h"

#include "util_getData.h"
#include "util_pasienUtil.h"

void on_button_clicked(GtkButton *button, gpointer user_data);
void on_button_clicked_with_page(GtkButton *button, gpointer user_data);
GtkWidget *addHeader(GtkWidget *page);
GtkWidget *addFooter(GtkWidget *page);
GtkWidget *create_page_with_back_button(const char *title);
GtkWidget *LandingPage();


void reset_cariData_pasien_page();
void on_back_cariDataPasien_gui(GtkButton *button, gpointer user_data);
void on_cari_pasien_data_gui(GtkButton *button, gpointer user_data);
GtkWidget *DataPasienPage_CariData();


void reset_tambahData_pasien_page();
void on_back_tambahDataPasien_gui(GtkButton *button, gpointer user_data);
GtkWidget *ShowNewPatientDataPage(struct dataPasien *new_patient, void callBackFunction(GtkButton *button, gpointer user_data));
void on_submit_data_pasien(GtkButton *button, gpointer user_data);
GtkWidget *DataPasienPage_TambahData();

void reset_ubahData_pasien_page();
void on_back_ubahDataPasien_gui(GtkButton *button, gpointer user_data);
void on_submit_ubahData_pasien_page(GtkButton *button, gpointer user_data);
GtkWidget *ubahData_form_page(char *IdPasien_data);
void on_confirm_ubahData_pasien_page(GtkButton *button, gpointer user_data);
void on_cari_pasienData_ubahData_gui(GtkButton *button, gpointer user_data);
GtkWidget *DataPasienPage_UbahData();

void reset_hapusData_pasien_page();
void on_back_hapusDataPasien_gui(GtkButton *button, gpointer user_data);
void on_confirm_hapusData_pasien_page(GtkButton *button, gpointer user_data);
void on_cari_pasienData_hapusData_gui(GtkButton *button, gpointer user_data);
GtkWidget *DataPasienPage_HapusData();

GtkWidget *DataPasienPage();
#endif