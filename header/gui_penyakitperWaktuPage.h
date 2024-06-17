#ifndef GUI_PENYAKITPERWAKTUPAGE_H
#define GUI_PENYAKITPERWAKTUPAGE_H

#include "util_getData.h"
#include "util_penyakitperWaktuUtil.h"
#include "gui_basePage.h"

void on_button_clicked(GtkButton *button, gpointer user_data);
void on_button_clicked_with_page(GtkButton *button, gpointer user_data);
GtkWidget *addHeader(GtkWidget *page);
GtkWidget *addFooter(GtkWidget *page);
GtkWidget *create_page_with_back_button(const char *title);
GtkWidget *LandingPage();

GtkWidget *DisplayPenyakitPage (int tahun);
void integer_validation_penyakitperWaktuPage(GtkButton *button, gpointer user_data) ;
void reset_penyakitperWaktuPage_Stack(GtkButton *button, gpointer user_data);
GtkWidget *addFooter_with_InformasiPasienPageStack_reset(GtkWidget *page);

GtkWidget *InformasiPenyakitPage();

#endif