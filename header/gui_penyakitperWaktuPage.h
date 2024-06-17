#ifndef GUI_PENYAKITPERWAKTUPAGE_H
#define GUI_PENYAKITPERWAKTUPAGE_H

#include "util_getData.h"
#include "util_penyakitperWaktuUtil.h"
#include "gui_basePage.h"

void reset_displayBulanBox();
void reset_displayPenyakitPage();
void *displayBulan(GtkButton *button, gpointer user_data);
void *DisplayPenyakitPage (int tahun);
void integer_validation_penyakitperWaktuPage(GtkButton *button, gpointer user_data) ;
void reset_penyakitperWaktuPage_Stack(GtkButton *button, gpointer user_data);
GtkWidget *addFooter_with_InformasiPasienPage_reset(GtkWidget *page)

GtkWidget *InformasiPenyakitPage();

#endif