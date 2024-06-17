#ifndef GUI_PASIENKONTROL_H
#define GUI_PASIENKONTROL_H

#include "util_getData.h"
#include "util_pasienUtil.h"
#include "util_riwayatUtil.h"
#include "util_pasienKontrolUtil.h"
#include "gui_basePage.h"

void reset_pasienKontrolPage_info();
void on_clicked_footer_pasienKontrolPage(GtkButton *button, gpointer user_data);
GtkWidget *PasienKontrol_footer_with_reset(GtkWidget *page);
void on_cari_pasienKontrol_data_gui(GtkButton *button, gpointer user_data);
GtkWidget *PasienKontrolPage();



#endif