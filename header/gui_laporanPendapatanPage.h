#ifndef GUI_LAPORANPENDAPATANPAGE_H
#define GUI_LAPORANPENDAPATANPAGE_H

#include "util_getData.h"
#include "util_laporanPendapatanUtil.h"
#include "gui_basePage.h"

void on_button_clicked(GtkButton *button, gpointer user_data);
void on_button_clicked_with_page(GtkButton *button, gpointer user_data);
GtkWidget *addHeader(GtkWidget *page);
GtkWidget *addFooter(GtkWidget *page);
GtkWidget *create_page_with_back_button(const char *title);
GtkWidget *LandingPage();

GtkWidget *DisplayPendapatanPage(int tahun);
void integer_validation_laporanPendapatanPage(GtkButton *button, gpointer user_data) ;
void reset_laporanPendapatanPage_Stack(GtkButton *button, gpointer user_data);
GtkWidget *addFooter_with_laporanPendapatanPage_reset(GtkWidget *page);

GtkWidget *LaporanPendapatanPage();

#endif