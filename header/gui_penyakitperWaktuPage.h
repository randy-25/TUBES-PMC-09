#ifndef GUI_PENYAKITPERWAKTUPAGE_H
#define GUI_PENYAKITPERWAKTUPAGE_H

#include "util_getData.h"
#include "util_penyakitperWaktuUtil.h"
#include "gui_basePage.h"

void reset_displayPenyakitPage();
void *DisplayPenyakitPage (int tahun);
void integer_validation_penyakitperWaktuPage(GtkButton *button, gpointer user_data) ;
void reset_penyakitperWaktuPage_Stack(GtkButton *button, gpointer user_data);
GtkWidget *addFooter_with_InformasiPasienPageStack_reset(GtkWidget *page);

GtkWidget *InformasiPenyakitPage();

#endif