#ifndef GUI_INFORMASIPASIENPAGE_H
#define GUI_INFORMASIPASIENPAGE_H

#include "util_getData.h"
#include "util_pasienUtil.h"
#include "util_riwayatUtil.h"
#include "gui_basePage.h"

void reset_informasiPasienPage_info();

void on_clicked_footer_informasiPasienPage(GtkButton *button, gpointer user_data);

GtkWidget *InformasiPasien_footer_with_reset(GtkWidget *page);

void on_cari_informasiPasien_data_gui(GtkButton *button, gpointer user_data);

GtkWidget *InformasiPasienPage();


#endif