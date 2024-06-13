//FOR CODE DEBUG

// #include <stdio.h>
// #include <stdlib.h>
// #include "header/getData.h"
// #include "header/penyakitperWaktuUtil.h"
// #include "header/pasienKontrolUtil.h"
// #include "header/informasiPasienUtil.h"
// #include "header/laporanPendapatanUtil.h"

// int main() {
//     // Declare pointers to hold patient and medical history data
//     struct dataPasien *pasien = NULL; // data sheets 1
//     struct riwayat *riwayatPasien = NULL; // data sheets 2
//     struct biaya *biayaPerawatan = NULL; // data sheets 3 (biaya, static)
//     int jumlahPasien = 0;
//     int jumlahRiwayatPasien = 0;

//     // Call getData function to read data from the Excel file
//     getData(&pasien, &riwayatPasien, &jumlahPasien, &jumlahRiwayatPasien);
//     getBiaya(&biayaPerawatan);
    

//     // // Print out the patient data
//     // printf("Jumlah Pasien: %d\n", jumlahPasien);
//     // for (int i = 0; i < jumlahPasien; i++) {
//     //     printf("\nData Pasien %d\n", i + 1);
//     //     printDataPasien(pasien[i]);
//     // }

//     // // Print out the medical history data
//     // printf("\nJumlah Riwayat Pasien: %d\n", jumlahRiwayatPasien);
//     // for (int i = 0; i < jumlahRiwayatPasien; i++) {
//     //     printf("\nRiwayat Pasien %d\n", i + 1);
//     //     printRiwayatPasien(riwayatPasien[i]);
//     // }

//     ////debug DataPenyakitperWaktu
//     // DataPenyakitperWaktu (riwayatPasien, jumlahRiwayatPasien);

//     ////debug pasienKontrol
//     // pasienKontrol(pasien, riwayatPasien, jumlahPasien, jumlahRiwayatPasien);

//     ////debug informasiPasien
//     // informasiPasien(pasien, riwayatPasien, jumlahPasien, jumlahRiwayatPasien);

//     ////debug laporanPendapatan
//     LaporanPendapatan (riwayatPasien, jumlahRiwayatPasien);

//     // Free allocated memory
//     for (int i = 0; i < jumlahPasien; i++) {
//         free(pasien[i].nama);
//         free(pasien[i].alamat);
//         free(pasien[i].kota);
//         free(pasien[i].tempatLahir);
//         free(pasien[i].nomorBPJS);
//         free(pasien[i].IdPasien);
//     }
//     free(pasien);

//     for (int i = 0; i < jumlahRiwayatPasien; i++) {
//         free(riwayatPasien[i].IdPasien);
//         free(riwayatPasien[i].diagnosis);
//         free(riwayatPasien[i].tindakan);
//     }
//     free(riwayatPasien);

//     return 0;
// }



//FOR GUI

#include <gtk/gtk.h>
#include "header/getData.h"
// #include "header/pasienUtil.h"
// #include "header/riwayatUtil.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define HEADER_HEIGHT 50
#define FOOTER_HEIGHT 50

// Global variables to store patient data
struct dataPasien *pasien = NULL;
struct riwayat *riwayatPasien = NULL;
int jumlahPasien = 0;
int jumlahRiwayatPasien = 0;

GtkWidget *stackContainer;
GtkWidget *landingPage;
GtkWidget *dataPasienPage;
GtkWidget *riwayatPasienPage;
GtkWidget *informasiPasienPage;
GtkWidget *laporanPendapatanPage;
GtkWidget *informasiPenyakitPage;
GtkWidget *informasiKontrolPage;
GtkWidget *displayPenyakit;

void on_button_clicked(GtkButton *button, gpointer user_data)
{
    const char *page_name = user_data;
    gtk_stack_set_visible_child_name(GTK_STACK(stackContainer), page_name);
}

GtkWidget *addHeader(GtkWidget *page)
{
    GtkWidget *fixed = gtk_fixed_new();
    gtk_box_append(GTK_BOX(page), fixed);
    gtk_widget_set_size_request(fixed, WINDOW_WIDTH, HEADER_HEIGHT);

    GtkWidget *header = gtk_label_new("Aplikasi Manajemen Pasien - Klinik X");
    gtk_fixed_put(GTK_FIXED(fixed), header, 0, 0);
    return fixed;
}

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

GtkWidget *LandingPage()
{
    GtkWidget *page = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

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

            g_signal_connect(funcButton, "clicked", G_CALLBACK(on_button_clicked), page_names[k]);

            k++;
        }
    }
    return page;
}

GtkWidget *DataPasienPage()
{
    GtkWidget *page = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget *header = addHeader(page);

    GtkWidget *mainGrid = gtk_grid_new();
    gtk_box_append(GTK_BOX(page), mainGrid);

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
        // g_signal_connect(funcButton[i], "clicked", G_CALLBACK(on_button_clicked), page_names[i]);
    }

    gtk_grid_attach(GTK_GRID(baseGrid), leftHalf, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(baseGrid), rightHalf, 1, 0, 1, 1);

    // Center the mainContent
    gtk_grid_set_column_spacing(GTK_GRID(mainGrid), 0);
    gtk_grid_set_row_spacing(GTK_GRID(mainGrid), 0);
    gtk_grid_set_column_homogeneous(GTK_GRID(mainGrid), TRUE);
    gtk_grid_set_row_homogeneous(GTK_GRID(mainGrid), TRUE);

    GtkWidget *footer = addFooter(page);
    return page;
}

GtkWidget *InformasiPenyakitPage()
{
    GtkWidget *page = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    GtkWidget *header = addHeader(page);

    GtkWidget *mainGrid = gtk_grid_new();
    gtk_box_append(GTK_BOX(page), mainGrid);

    GtkWidget *mainContent = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_grid_attach(GTK_GRID(mainGrid), mainContent, 1, 1, 1, 1);
    gtk_widget_set_size_request(mainContent, WINDOW_WIDTH, WINDOW_HEIGHT - HEADER_HEIGHT - FOOTER_HEIGHT);
    gtk_widget_set_valign(mainContent, GTK_ALIGN_CENTER);

    GtkWidget *topLabel = gtk_label_new("Informasi Penyakit per Tahun");
    gtk_box_append(GTK_BOX(mainContent), topLabel);
    gtk_widget_set_halign(topLabel, GTK_ALIGN_CENTER);

    GtkWidget *cmdLabel = gtk_label_new("Masukkan Tahun ");
    gtk_box_append(GTK_BOX(mainContent), cmdLabel);
    gtk_widget_set_halign(cmdLabel, GTK_ALIGN_CENTER);

    GtkWidget *inputBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_box_append(GTK_BOX(mainContent), inputBox);
    gtk_widget_set_halign(inputBox, GTK_ALIGN_CENTER);

    GtkWidget *entry = gtk_entry_new();
    gtk_box_append(GTK_BOX(inputBox), entry);

    GtkWidget *submit = gtk_button_new_with_label("Submit");
    gtk_box_append(GTK_BOX(mainContent), submit);
    gtk_widget_set_halign(submit, GTK_ALIGN_CENTER);

    g_signal_connect(submit, "clicked", G_CALLBACK(on_button_clicked), (gpointer) "DisplayPenyakit");

    // Center the mainContent
    gtk_grid_set_column_spacing(GTK_GRID(mainGrid), 0);
    gtk_grid_set_row_spacing(GTK_GRID(mainGrid), 0);
    gtk_grid_set_column_homogeneous(GTK_GRID(mainGrid), TRUE);
    gtk_grid_set_row_homogeneous(GTK_GRID(mainGrid), TRUE);

    GtkWidget *footer = addFooter(page);
    return page;
}

GtkWidget *DisplayPenyakit ()
{
    GtkWidget *page = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget *header = addHeader(page);

    GtkWidget *mainGrid = gtk_grid_new();
    gtk_box_append(GTK_BOX(page), mainGrid);

    GtkWidget *mainContent = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_grid_attach(GTK_GRID(mainGrid), mainContent, 1, 1, 1, 1);
    gtk_widget_set_size_request(mainContent, WINDOW_WIDTH, WINDOW_HEIGHT - HEADER_HEIGHT - FOOTER_HEIGHT);
    gtk_widget_set_valign(mainContent, GTK_ALIGN_CENTER);

    char *month_labels[12] = {"Januari", "Februari", "Maret", "April", "Mei", "Juni", "Juli", "Agustus", "September", "Oktober", "November", "Desember"};
    char *namaPenyakit[4] = {"Dehidrasi", "Pusing", "Masuk Angin", "Demam"};

    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(mainContent), grid);

    // GtkWidget *boxYear = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);

    // GtkWidget *tempYear = gtk_label_new("Tahun Sekarang");
    // gtk_box_append(GTK_BOX(mainContent), tempYear);
    // gtk_widget_set_halign(tempYear, GTK_ALIGN_CENTER);

    GtkWidget *monthLabel;
    GtkWidget *tempMonth;
    GtkWidget *tempPenyakit;

    int k = 0;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 6; j++)
        {   
            monthLabel = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

            if (i == 0)
            {
                tempMonth = gtk_label_new(month_labels[j]);
            }
            else 
            {
                tempMonth = gtk_label_new(month_labels[j+6]);
            }
  
            gtk_box_append(GTK_BOX(monthLabel), tempMonth);
            gtk_widget_set_halign(tempMonth, GTK_ALIGN_CENTER);

            for (int k = 0; k < 4; k++)
            {   
                tempPenyakit = gtk_label_new(namaPenyakit[k]);
                gtk_box_append(GTK_BOX(monthLabel), tempPenyakit);
                gtk_widget_set_halign(tempMonth, GTK_ALIGN_CENTER);
            }

            gtk_grid_attach(GTK_GRID(grid), monthLabel, j, i+1, 1, 1);
        }
    }

    // Center the mainContent
    gtk_grid_set_column_spacing(GTK_GRID(mainGrid), 10);
    gtk_grid_set_row_spacing(GTK_GRID(mainGrid), 0);
    gtk_grid_set_column_homogeneous(GTK_GRID(mainGrid), TRUE);
    gtk_grid_set_row_homogeneous(GTK_GRID(mainGrid), TRUE);

    GtkWidget *footer = addFooter(page);
    return page;
}

GtkWidget *

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

    informasiPenyakitPage = InformasiPenyakitPage();
    gtk_stack_add_named(GTK_STACK(stackContainer), informasiPenyakitPage, "InformasiPenyakit");

    displayPenyakit = DisplayPenyakit();
    gtk_stack_add_named(GTK_STACK(stackContainer), displayPenyakit, "DisplayPenyakit");

    informasiKontrolPage = create_page_with_back_button("Informasi Kontrol Pasien");
    gtk_stack_add_named(GTK_STACK(stackContainer), informasiKontrolPage, "InformasiKontrol");


    gtk_widget_set_visible(GTK_WIDGET(window), TRUE);
}

int main(int argc, char **argv)
{
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