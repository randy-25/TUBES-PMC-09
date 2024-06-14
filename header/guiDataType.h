#ifndef GUI_DATA__TYPE_H
#define GUI_DATA__TYPE_H

#include <gtk/gtk.h>
#include "dataType.h"

// data structure to pass data to callback function
typedef struct DataCallBack
{
    GtkWidget *stackContainer;
    const char *page_name;
} DataCallBack;


typedef struct DataPasienEntry
{
    GtkWidget *entry_nama;
    GtkWidget *entry_alamat;
    GtkWidget *entry_kota;
    GtkWidget *entry_tempat_lahir;
    GtkWidget *entry_tanggal_lahir;
    GtkWidget *entry_no_bpjs;
    char *id_pasien;
} DataPasienEntry;

#endif