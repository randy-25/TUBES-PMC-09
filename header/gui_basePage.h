#ifndef GUI_BASEPAGE_H
#define GUI_BASEPAGE_H

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


#endif