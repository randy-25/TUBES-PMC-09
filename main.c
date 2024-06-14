#include <gtk/gtk.h>
#include "header/getData.h"
#include "header/pasienUtil.h"
#include "header/riwayatUtil.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define HEADER_HEIGHT 50
#define FOOTER_HEIGHT 50

// Global variables to store patient data
struct dataPasien *pasien = NULL;
struct riwayat *riwayatPasien = NULL;
int jumlahPasien = 0;
int jumlahRiwayatPasien = 0;

// Base Page
GtkWidget *stackContainer;
GtkWidget *landingPage;
GtkWidget *dataPasienPage;
GtkWidget *riwayatPasienPage;
GtkWidget *informasiPasienPage;
GtkWidget *laporanPendapatanPage;
GtkWidget *informasiPenyakitPage;
GtkWidget *informasiKontrolPage;

// data structure to pass data to callback function
typedef struct DataCallBack
{
    GtkWidget *stackContainer;
    const char *page_name;
} DataCallBack;

// Callback function to switch between base pages
// only accept page name to switch to, so cant set the stack pages
void on_button_clicked(GtkButton *button, gpointer user_data)
{
    const char *page_name = user_data;
    gtk_stack_set_visible_child_name(GTK_STACK(stackContainer), page_name);
}

// Callback function to switch between pages (not base)
// accept the stack pages and page name to switch to
void on_button_clicked_with_page(GtkButton *button, gpointer user_data)
{
    DataCallBack *data = (DataCallBack *)user_data;
    gtk_stack_set_visible_child_name(GTK_STACK(data->stackContainer), data->page_name);
}

// Add header to the page
GtkWidget *addHeader(GtkWidget *page)
{
    GtkWidget *fixed = gtk_fixed_new();
    gtk_box_append(GTK_BOX(page), fixed);
    gtk_widget_set_size_request(fixed, WINDOW_WIDTH, HEADER_HEIGHT);

    GtkWidget *header = gtk_label_new("Aplikasi Manajemen Pasien - Klinik X");
    gtk_fixed_put(GTK_FIXED(fixed), header, 0, 0);
    return fixed;
}

// Add footer to the page
GtkWidget *addFooter(GtkWidget *page)
{
    GtkWidget *fixed = gtk_fixed_new();
    gtk_box_append(GTK_BOX(page), fixed);

    GtkWidget *footer = gtk_button_new_with_label("Back to Landing Page");
    gtk_fixed_put(GTK_FIXED(fixed), footer, 0, FOOTER_HEIGHT);
    g_signal_connect(footer, "clicked", G_CALLBACK(on_button_clicked), (gpointer) "LandingPage");
    return fixed;
}

GtkWidget *create_page_with_back_button(const char *title)
{
    GtkWidget *page = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    // add header before the start of the main page
    GtkWidget *header = addHeader(page);
    GtkWidget *label = gtk_label_new(title);

    gtk_box_append(GTK_BOX(page), label);
    gtk_widget_set_halign(label, GTK_ALIGN_CENTER);

    // add footer after the page ends
    GtkWidget *footer = addFooter(page);
    return page;
}

// Landing page, set 6 button and some information of the app
GtkWidget *LandingPage()
{
    GtkWidget *page = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    GtkWidget *funcButton;
    GtkWidget *grid;
    GtkWidget *label = gtk_label_new("Aplikasi Manajemen Pasien - Klinik X");

    gtk_box_append(GTK_BOX(page), label);
    gtk_widget_set_halign(label, GTK_ALIGN_CENTER);

    char *button_labels[6] = {"Data Pasien", "Riwayat pasien", "Informasi Pasien", "Laporan Pendapatan", "Informasi Penyakit dan Jumlah", "Informasi Kontrol Pasien"};

    char *page_names[6] = {"DataPasien", "RiwayatPasien", "InformasiPasien", "LaporanPendapatan", "InformasiPenyakit", "InformasiKontrol"};

    grid = gtk_grid_new();
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(page), grid);

    int k = 0;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            funcButton = gtk_button_new_with_label(button_labels[k]);
            gtk_grid_attach(GTK_GRID(grid), funcButton, j, i, 1, 1);

            g_signal_connect(funcButton, "clicked", G_CALLBACK(on_button_clicked), page_names[k]); // call the function to switch between base page

            k++;
        }
    }
    return page;
}

// DATA PASIEN PAGE
GtkWidget *dataPasienPage_Stack;

// CARI DATA PASIEN PAGE
GtkWidget *dataPasienPage_cariData_pasienInfo;
// reset the data pasien page
void reset_cariData_pasien_page()
{
    // Count the children
    GtkWidget *child = gtk_widget_get_first_child(GTK_WIDGET(dataPasienPage_cariData_pasienInfo));
    int child_count = 0;
    while (child != NULL)
    {
        child = gtk_widget_get_next_sibling(child);
        child_count++;
    }

    // Remove all but the last child
    child = gtk_widget_get_first_child(GTK_WIDGET(dataPasienPage_cariData_pasienInfo));
    for (int i = 0; i < child_count - 1; i++)
    {
        GtkWidget *next = gtk_widget_get_next_sibling(child);
        gtk_box_remove(GTK_BOX(dataPasienPage_cariData_pasienInfo), child);
        child = next;
    }
}

// Back to previous page button click
void on_back_cariDataPasien_gui(GtkButton *button, gpointer user_data)
{
    reset_cariData_pasien_page();
    DataCallBack *data = (DataCallBack *)user_data;
    gtk_stack_set_visible_child_name(GTK_STACK(data->stackContainer), data->page_name);
}

// Callback function to search patient data
void on_cari_pasien_data_gui(GtkButton *button, gpointer user_data)
{
    GtkWidget *data = user_data;
    const char *input_text = gtk_editable_get_text(GTK_EDITABLE(data)); // get the input text from the entry

    char *idPasien = strdup(input_text); // get the data from the entry
    // printf("Data: %s\n", idPasien);
    struct dataPasien dataHolder;
    int confirm;
    cariPasien(pasien, jumlahPasien, idPasien, &dataHolder, &confirm); // search the data from the patient data
    // printDataPasien(dataHolder); // print the data to the console

    // Clear the input box entry
    const gchar *default_text = "KX ";
    gtk_editable_set_text(GTK_EDITABLE(data), default_text);
    gtk_editable_set_position(GTK_EDITABLE(data), strlen(default_text));

    // Clear the existing content of the box
    GtkWidget *child = gtk_widget_get_first_child(GTK_WIDGET(dataPasienPage_cariData_pasienInfo));
    while (child != NULL)
    {
        GtkWidget *next = gtk_widget_get_next_sibling(child);
        gtk_box_remove(GTK_BOX(dataPasienPage_cariData_pasienInfo), child);
        child = next;
    }

    if (confirm == 1)
    {
        // Create new labels to display the data
        char info[256]; // Ensure that the buffer is large enough

        snprintf(info, sizeof(info), "ID Pasien: %s", dataHolder.IdPasien);
        GtkWidget *id_label = gtk_label_new(info);
        gtk_box_append(GTK_BOX(dataPasienPage_cariData_pasienInfo), id_label);

        snprintf(info, sizeof(info), "Nama: %s", dataHolder.nama);
        GtkWidget *nama_label = gtk_label_new(info);
        gtk_box_append(GTK_BOX(dataPasienPage_cariData_pasienInfo), nama_label);

        snprintf(info, sizeof(info), "Alamat: %s", dataHolder.alamat);
        GtkWidget *alamat_label = gtk_label_new(info);
        gtk_box_append(GTK_BOX(dataPasienPage_cariData_pasienInfo), alamat_label);

        snprintf(info, sizeof(info), "Kota: %s", dataHolder.kota);
        GtkWidget *kota_label = gtk_label_new(info);
        gtk_box_append(GTK_BOX(dataPasienPage_cariData_pasienInfo), kota_label);

        snprintf(info, sizeof(info), "Tempat Lahir: %s", dataHolder.tempatLahir);
        GtkWidget *tempat_lahir_label = gtk_label_new(info);
        gtk_box_append(GTK_BOX(dataPasienPage_cariData_pasienInfo), tempat_lahir_label);

        snprintf(info, sizeof(info), "Tanggal Lahir: %02d-%02d-%04d", dataHolder.tanggalLahir.tanggal, dataHolder.tanggalLahir.bulan, dataHolder.tanggalLahir.tahun);
        GtkWidget *tanggal_lahir_label = gtk_label_new(info);
        gtk_box_append(GTK_BOX(dataPasienPage_cariData_pasienInfo), tanggal_lahir_label);

        snprintf(info, sizeof(info), "Umur: %d", dataHolder.umur);
        GtkWidget *umur_label = gtk_label_new(info);
        gtk_box_append(GTK_BOX(dataPasienPage_cariData_pasienInfo), umur_label);

        snprintf(info, sizeof(info), "Nomor BPJS: %s", dataHolder.nomorBPJS);
        GtkWidget *bpjs_label = gtk_label_new(info);
        gtk_box_append(GTK_BOX(dataPasienPage_cariData_pasienInfo), bpjs_label);
    }
    else
    {
        GtkWidget *not_found_label = gtk_label_new("Data Pasien tidak ditemukan");
        gtk_box_append(GTK_BOX(dataPasienPage_cariData_pasienInfo), not_found_label);
    }

    GtkWidget *back_button = gtk_button_new_with_label("Back");
    gtk_widget_set_halign(back_button, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(dataPasienPage_cariData_pasienInfo), back_button);
    DataCallBack *callBack = g_malloc(sizeof(DataCallBack));
    callBack->stackContainer = dataPasienPage_Stack;
    callBack->page_name = "MainGrid";
    g_signal_connect(back_button, "clicked", G_CALLBACK(on_back_cariDataPasien_gui), callBack);
}

GtkWidget *DataPasienPage_CariData()
{
    GtkWidget *page;
    GtkWidget *entry;
    GtkWidget *button;

    page = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    entry = gtk_entry_new();
    GtkWidget *formLabel = gtk_label_new("Masukkan ID Pasien: ");
    gtk_box_append(GTK_BOX(page), formLabel);

    const gchar *default_text = "KX ";
    gtk_editable_set_text(GTK_EDITABLE(entry), default_text);
    gtk_editable_set_position(GTK_EDITABLE(entry), strlen(default_text));

    gtk_widget_set_size_request(entry, 200, 30);
    gtk_box_append(GTK_BOX(page), entry);

    button = gtk_button_new_with_label("Cari");
    gtk_widget_set_halign(button, GTK_ALIGN_CENTER);
    // gtk_widget_set_size_request(button, 100, 30);
    gtk_box_append(GTK_BOX(page), button);

    dataPasienPage_cariData_pasienInfo = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_append(GTK_BOX(page), dataPasienPage_cariData_pasienInfo);

    g_signal_connect(button, "clicked", G_CALLBACK(on_cari_pasien_data_gui), entry);

    GtkWidget *back_button = gtk_button_new_with_label("Back");
    gtk_widget_set_halign(back_button, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(dataPasienPage_cariData_pasienInfo), back_button);
    DataCallBack *callBack = g_malloc(sizeof(DataCallBack));
    callBack->stackContainer = dataPasienPage_Stack;
    callBack->page_name = "MainGrid";
    g_signal_connect(back_button, "clicked", G_CALLBACK(on_back_cariDataPasien_gui), callBack);

    return page;
}

// TAMBAH DATA PASIEN PAGE
GtkWidget *dataPasienPage_tambahData_pasienInfo;

typedef struct DataPasienEntry
{
    GtkWidget *entry_nama;
    GtkWidget *entry_alamat;
    GtkWidget *entry_kota;
    GtkWidget *entry_tempat_lahir;
    GtkWidget *entry_tanggal_lahir;
    GtkWidget *entry_no_bpjs;
} DataPasienEntry;

void reset_tambahData_pasien_page()
{
    // Count the children
    GtkWidget *child = gtk_widget_get_first_child(GTK_WIDGET(dataPasienPage_tambahData_pasienInfo));
    int child_count = 0;
    while (child != NULL)
    {
        child = gtk_widget_get_next_sibling(child);
        child_count++;
    }

    // Remove all but the last child
    child = gtk_widget_get_first_child(GTK_WIDGET(dataPasienPage_tambahData_pasienInfo));
    for (int i = 0; i < child_count - 1; i++)
    {
        GtkWidget *next = gtk_widget_get_next_sibling(child);
        gtk_box_remove(GTK_BOX(dataPasienPage_tambahData_pasienInfo), child);
        child = next;
    }
}

void on_back_tambahDataPasien_gui(GtkButton *button, gpointer user_data)
{
    reset_tambahData_pasien_page();
    DataCallBack *data = (DataCallBack *)user_data;
    gtk_stack_set_visible_child_name(GTK_STACK(data->stackContainer), data->page_name);
}

GtkWidget *ShowNewPatientDataPage(struct dataPasien *new_patient)
{
    GtkWidget *page = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    // Title
    GtkWidget *title = gtk_label_new("Data Pasien Baru");
    gtk_widget_set_halign(title, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(page), title);

    // Display the new patient data
    char info[256];

    snprintf(info, sizeof(info), "Nama: %s", new_patient->nama);
    GtkWidget *nama_label = gtk_label_new(info);
    gtk_box_append(GTK_BOX(page), nama_label);

    snprintf(info, sizeof(info), "Alamat: %s", new_patient->alamat);
    GtkWidget *alamat_label = gtk_label_new(info);
    gtk_box_append(GTK_BOX(page), alamat_label);

    snprintf(info, sizeof(info), "Kota: %s", new_patient->kota);
    GtkWidget *kota_label = gtk_label_new(info);
    gtk_box_append(GTK_BOX(page), kota_label);

    snprintf(info, sizeof(info), "Tempat Lahir: %s", new_patient->tempatLahir);
    GtkWidget *tempat_lahir_label = gtk_label_new(info);
    gtk_box_append(GTK_BOX(page), tempat_lahir_label);

    snprintf(info, sizeof(info), "Tanggal Lahir: %d-%d-%d", new_patient->tanggalLahir.tanggal, new_patient->tanggalLahir.bulan, new_patient->tanggalLahir.tahun);
    GtkWidget *tanggal_lahir_label = gtk_label_new(info);
    gtk_box_append(GTK_BOX(page), tanggal_lahir_label);

    snprintf(info, sizeof(info), "No BPJS: %s", new_patient->nomorBPJS);
    GtkWidget *no_bpjs_label = gtk_label_new(info);
    gtk_box_append(GTK_BOX(page), no_bpjs_label);

    snprintf(info, sizeof(info), "ID Pasien: %s", new_patient->IdPasien);
    GtkWidget *id_label = gtk_label_new(info);
    gtk_box_append(GTK_BOX(page), id_label);
    
    // Add a button to go back to the landing page
    GtkWidget *back_button = gtk_button_new_with_label("Back");
    gtk_widget_set_halign(back_button, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(page), back_button);

    DataCallBack *callBack = g_malloc(sizeof(DataCallBack));
    callBack->stackContainer = dataPasienPage_Stack;
    callBack->page_name = "MainGrid";
    g_signal_connect(back_button, "clicked", G_CALLBACK(on_back_tambahDataPasien_gui), callBack);

    return page;
}

void on_submit_data_pasien(GtkButton *button, gpointer user_data)
{
    DataPasienEntry *entry = (DataPasienEntry *)user_data;
    const gchar *nama = gtk_editable_get_text(GTK_EDITABLE(entry->entry_nama));
    const gchar *alamat = gtk_editable_get_text(GTK_EDITABLE(entry->entry_alamat));
    const gchar *kota = gtk_editable_get_text(GTK_EDITABLE(entry->entry_kota));
    const gchar *tempat_lahir = gtk_editable_get_text(GTK_EDITABLE(entry->entry_tempat_lahir));
    const gchar *tanggal_lahir = gtk_editable_get_text(GTK_EDITABLE(entry->entry_tanggal_lahir));
    const gchar *no_bpjs = gtk_editable_get_text(GTK_EDITABLE(entry->entry_no_bpjs));

    char *tempNama = strdup(nama);
    char *tempAlamat = strdup(alamat);
    char *tempKota = strdup(kota);
    char *tempTempatLahir = strdup(tempat_lahir);
    char *tempTanggalLahir = strdup(tanggal_lahir);
    char *tempNoBPJS = strdup(no_bpjs);

    // Clear the input box entry
    const gchar *default_text = "";
    gtk_editable_set_text(GTK_EDITABLE(entry->entry_nama), default_text);
    gtk_editable_set_position(GTK_EDITABLE(entry->entry_nama), strlen(default_text));

    gtk_editable_set_text(GTK_EDITABLE(entry->entry_alamat), default_text);
    gtk_editable_set_position(GTK_EDITABLE(entry->entry_alamat), strlen(default_text));

    gtk_editable_set_text(GTK_EDITABLE(entry->entry_kota), default_text);
    gtk_editable_set_position(GTK_EDITABLE(entry->entry_kota), strlen(default_text));

    gtk_editable_set_text(GTK_EDITABLE(entry->entry_tempat_lahir), default_text);
    gtk_editable_set_position(GTK_EDITABLE(entry->entry_tempat_lahir), strlen(default_text));

    gtk_editable_set_text(GTK_EDITABLE(entry->entry_tanggal_lahir), default_text);
    gtk_editable_set_position(GTK_EDITABLE(entry->entry_tanggal_lahir), strlen(default_text));

    gtk_editable_set_text(GTK_EDITABLE(entry->entry_no_bpjs), default_text);
    gtk_editable_set_position(GTK_EDITABLE(entry->entry_no_bpjs), strlen(default_text));

    struct dataPasien newPasienHolder;
    int confirm;

    tambahPasien(&pasien, &jumlahPasien, tempNoBPJS, tempNama, tempAlamat, tempKota, tempTempatLahir, tempTanggalLahir, &newPasienHolder, &confirm);

    if (confirm == 1)
    {
        // printf("Data Pasien berhasil ditambahkan\n");

        GtkWidget *tempWidget = gtk_stack_get_child_by_name(GTK_STACK(dataPasienPage_Stack), "NewPatientData");

        if(tempWidget != NULL){
            gtk_stack_remove(GTK_STACK(dataPasienPage_Stack), tempWidget);
        }

        // Create and show the new patient data page
        dataPasienPage_tambahData_pasienInfo = ShowNewPatientDataPage(&newPasienHolder);
        gtk_stack_add_named(GTK_STACK(dataPasienPage_Stack), dataPasienPage_tambahData_pasienInfo, "NewPatientData");
        gtk_stack_set_visible_child(GTK_STACK(dataPasienPage_Stack), dataPasienPage_tambahData_pasienInfo);
    }
    else
    {
        // printf("Data Pasien Telah Terdaftar\n");

        GtkWidget *tempWidget = gtk_stack_get_child_by_name(GTK_STACK(dataPasienPage_Stack), "FailedPage");

        if(tempWidget != NULL){
            gtk_stack_remove(GTK_STACK(dataPasienPage_Stack), tempWidget);
        }

        dataPasienPage_tambahData_pasienInfo = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
        GtkWidget *failedLabel = gtk_label_new("Nomor BPJS Pasien Telah Terdaftar");
        gtk_widget_set_halign(failedLabel, GTK_ALIGN_CENTER);
        gtk_box_append(GTK_BOX(dataPasienPage_tambahData_pasienInfo), failedLabel);

        GtkWidget *tempPasienInfo = ShowNewPatientDataPage(&newPasienHolder);
        gtk_box_append(GTK_BOX(dataPasienPage_tambahData_pasienInfo), tempPasienInfo);

        gtk_stack_add_named(GTK_STACK(dataPasienPage_Stack), dataPasienPage_tambahData_pasienInfo, "FailedPage");
        gtk_stack_set_visible_child(GTK_STACK(dataPasienPage_Stack), dataPasienPage_tambahData_pasienInfo);
    }
}

GtkWidget *DataPasienPage_TambahData()
{
    GtkWidget *page = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    GtkWidget *entry_nama;
    GtkWidget *entry_alamat;
    GtkWidget *entry_kota;
    GtkWidget *entry_tempat_lahir;
    GtkWidget *entry_tanggal_lahir;
    GtkWidget *entry_no_bpjs;

    GtkWidget *title = gtk_label_new("Tambah Data Pasien");
    gtk_widget_set_halign(title, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(page), title);

    GtkWidget *formGrid = gtk_grid_new();
    gtk_grid_set_column_homogeneous(GTK_GRID(formGrid), TRUE);
    gtk_grid_set_row_homogeneous(GTK_GRID(formGrid), TRUE);
    gtk_grid_set_row_spacing(GTK_GRID(formGrid), 10);
    gtk_widget_set_halign(formGrid, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(page), formGrid);

    // Nama
    GtkWidget *label_nama = gtk_label_new("Nama Pasien: ");
    entry_nama = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(formGrid), label_nama, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(formGrid), entry_nama, 1, 0, 1, 1);

    // Alamat
    GtkWidget *label_alamat = gtk_label_new("Alamat Pasien: ");
    entry_alamat = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(formGrid), label_alamat, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(formGrid), entry_alamat, 1, 1, 1, 1);

    // Kota
    GtkWidget *label_kota = gtk_label_new("Kota:");
    entry_kota = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(formGrid), label_kota, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(formGrid), entry_kota, 1, 2, 1, 1);

    // Tempat Lahir
    GtkWidget *label_tempat_lahir = gtk_label_new("Tempat Lahir:");
    entry_tempat_lahir = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(formGrid), label_tempat_lahir, 0, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(formGrid), entry_tempat_lahir, 1, 3, 1, 1);

    // Tanggal Lahir
    GtkWidget *label_tanggal_lahir = gtk_label_new("Tanggal Lahir (DD-MM-YYYY):");
    entry_tanggal_lahir = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(formGrid), label_tanggal_lahir, 0, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(formGrid), entry_tanggal_lahir, 1, 4, 1, 1);

    // No BPJS
    GtkWidget *label_no_bpjs = gtk_label_new("No BPJS:");
    entry_no_bpjs = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(formGrid), label_no_bpjs, 0, 5, 1, 1);
    gtk_grid_attach(GTK_GRID(formGrid), entry_no_bpjs, 1, 5, 1, 1);

    // Submit Button
    GtkWidget *submit_button = gtk_button_new_with_label("Submit");
    gtk_widget_set_halign(submit_button, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(page), submit_button);

    DataPasienEntry *entry_data = g_malloc(sizeof(DataPasienEntry));
    entry_data->entry_nama = entry_nama;
    entry_data->entry_alamat = entry_alamat;
    entry_data->entry_kota = entry_kota;
    entry_data->entry_tempat_lahir = entry_tempat_lahir;
    entry_data->entry_tanggal_lahir = entry_tanggal_lahir;
    entry_data->entry_no_bpjs = entry_no_bpjs;

    g_signal_connect(submit_button, "clicked", G_CALLBACK(on_submit_data_pasien), entry_data);

    GtkWidget *back_button = gtk_button_new_with_label("Back");
    gtk_widget_set_halign(back_button, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(page), back_button);

    DataCallBack *callBack = g_malloc(sizeof(DataCallBack));
    callBack->stackContainer = dataPasienPage_Stack;
    callBack->page_name = "MainGrid";
    g_signal_connect(back_button, "clicked", G_CALLBACK(on_button_clicked_with_page), callBack);
    return page;
}

GtkWidget *DataPasienPage()
{
    GtkWidget *page = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    GtkWidget *header = addHeader(page);

    dataPasienPage_Stack = gtk_stack_new();
    gtk_stack_set_transition_type(GTK_STACK(dataPasienPage_Stack), GTK_STACK_TRANSITION_TYPE_SLIDE_LEFT_RIGHT);

    gtk_box_append(GTK_BOX(page), dataPasienPage_Stack);

    GtkWidget *mainGrid = gtk_grid_new();
    gtk_stack_add_named(GTK_STACK(dataPasienPage_Stack), mainGrid, "MainGrid");

    GtkWidget *mainContent = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_grid_attach(GTK_GRID(mainGrid), mainContent, 1, 1, 1, 1);
    gtk_widget_set_size_request(mainContent, WINDOW_WIDTH, WINDOW_HEIGHT - HEADER_HEIGHT - FOOTER_HEIGHT);
    gtk_widget_set_valign(mainContent, GTK_ALIGN_CENTER);

    GtkWidget *baseGrid = gtk_grid_new();
    gtk_widget_set_size_request(baseGrid, WINDOW_WIDTH, -1);
    gtk_widget_set_vexpand(baseGrid, TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(baseGrid), TRUE);
    gtk_grid_set_row_homogeneous(GTK_GRID(baseGrid), TRUE);
    gtk_box_append(GTK_BOX(mainContent), baseGrid);

    GtkWidget *leftHalf = gtk_center_box_new();
    GtkWidget *leftLabel = gtk_label_new("Data Pasien");
    gtk_center_box_set_center_widget(GTK_CENTER_BOX(leftHalf), leftLabel);
    gtk_widget_set_valign(leftLabel, GTK_ALIGN_CENTER);

    GtkWidget *rightHalf = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    GtkWidget *rightHalfButton = gtk_grid_new();
    gtk_grid_set_column_homogeneous(GTK_GRID(rightHalfButton), TRUE);
    gtk_grid_set_row_homogeneous(GTK_GRID(rightHalfButton), TRUE);
    gtk_grid_set_row_spacing(GTK_GRID(rightHalfButton), 10);
    gtk_box_append(GTK_BOX(rightHalf), rightHalfButton);
    gtk_widget_set_halign(rightHalf, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(rightHalf, GTK_ALIGN_CENTER);

    GtkWidget *funcButton[4];
    char *button_labels[4] = {"Cari Data Pasien", "Tambah Data Pasien", "Ubah Data Pasien", "Hapus Data Pasien"};
    char *page_names[4] = {"CariDataPasien", "TambahDataPasien", "UbahDataPasien", "HapusDataPasien"};

    for (int i = 0; i < 4; i++)
    {
        funcButton[i] = gtk_button_new_with_label(button_labels[i]);
        gtk_grid_attach(GTK_GRID(rightHalfButton), funcButton[i], 0, i, 1, 1);
        gtk_widget_set_size_request(funcButton[i], 150, 50);
    }

    gtk_grid_attach(GTK_GRID(baseGrid), leftHalf, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(baseGrid), rightHalf, 1, 0, 1, 1);

    // Center the mainContent
    gtk_grid_set_column_spacing(GTK_GRID(mainGrid), 0);
    gtk_grid_set_row_spacing(GTK_GRID(mainGrid), 0);
    gtk_grid_set_column_homogeneous(GTK_GRID(mainGrid), TRUE);
    gtk_grid_set_row_homogeneous(GTK_GRID(mainGrid), TRUE);

    // Cari Data Page
    GtkWidget *dataPasienPage_cariData = DataPasienPage_CariData();
    gtk_stack_add_named(GTK_STACK(dataPasienPage_Stack), dataPasienPage_cariData, page_names[0]);
    DataCallBack *callBack = g_malloc(sizeof(DataCallBack));
    callBack->stackContainer = dataPasienPage_Stack;
    callBack->page_name = page_names[0];
    g_signal_connect(funcButton[0], "clicked", G_CALLBACK(on_button_clicked_with_page), callBack);

    // Tambah Data Page
    GtkWidget *dataPasienPage_tambahData = DataPasienPage_TambahData();
    gtk_stack_add_named(GTK_STACK(dataPasienPage_Stack), dataPasienPage_tambahData, page_names[1]);
    callBack = g_malloc(sizeof(DataCallBack));
    callBack->stackContainer = dataPasienPage_Stack;
    callBack->page_name = page_names[1];
    g_signal_connect(funcButton[1], "clicked", G_CALLBACK(on_button_clicked_with_page), callBack);

    GtkWidget *footer = addFooter(page);
    return page;
}

// activation function to create the main window
static void
activate(GtkApplication *app, gpointer user_data)
{
    GtkWidget *window = gtk_application_window_new(app);

    stackContainer = gtk_stack_new();

    gtk_window_set_title(GTK_WINDOW(window), "Aplikasi Manajemen Pasien - Klinik X");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);

    gtk_stack_set_transition_type(GTK_STACK(stackContainer), GTK_STACK_TRANSITION_TYPE_SLIDE_LEFT_RIGHT);
    gtk_window_set_child(GTK_WINDOW(window), stackContainer);

    landingPage = LandingPage();
    gtk_stack_add_named(GTK_STACK(stackContainer), landingPage, "LandingPage");

    dataPasienPage = DataPasienPage();
    gtk_stack_add_named(GTK_STACK(stackContainer), dataPasienPage, "DataPasien");

    riwayatPasienPage = create_page_with_back_button("Riwayat Pasien");
    gtk_stack_add_named(GTK_STACK(stackContainer), riwayatPasienPage, "RiwayatPasien");

    informasiPasienPage = create_page_with_back_button("Informasi Pasien");
    gtk_stack_add_named(GTK_STACK(stackContainer), informasiPasienPage, "InformasiPasien");

    laporanPendapatanPage = create_page_with_back_button("Laporan Pendapatan");
    gtk_stack_add_named(GTK_STACK(stackContainer), laporanPendapatanPage, "LaporanPendapatan");

    informasiPenyakitPage = create_page_with_back_button("Informasi Penyakit dan Jumlah");
    gtk_stack_add_named(GTK_STACK(stackContainer), informasiPenyakitPage, "InformasiPenyakit");

    informasiKontrolPage = create_page_with_back_button("Informasi Kontrol Pasien");
    gtk_stack_add_named(GTK_STACK(stackContainer), informasiKontrolPage, "InformasiKontrol");

    gtk_widget_set_visible(GTK_WIDGET(window), TRUE);
}

int main(int argc, char **argv)
{
    // Function to get data from excel file
    getData(&pasien, &riwayatPasien, &jumlahPasien, &jumlahRiwayatPasien);

    GtkApplication *app;
    int status;

    app = gtk_application_new("com.example.PatientManagement", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    status = g_application_run(G_APPLICATION(app), argc, argv);

    for (int i = 0; i < jumlahPasien; i++)
    {
        free(pasien[i].nama);
        free(pasien[i].alamat);
        free(pasien[i].kota);
        free(pasien[i].tempatLahir);
        free(pasien[i].nomorBPJS);
        free(pasien[i].IdPasien);
    }
    free(pasien);

    for (int i = 0; i < jumlahRiwayatPasien; i++)
    {
        free(riwayatPasien[i].IdPasien);
        free(riwayatPasien[i].diagnosis);
        free(riwayatPasien[i].tindakan);
    }
    free(riwayatPasien);

    g_object_unref(app);

    return status;
}