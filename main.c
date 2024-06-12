#include <gtk/gtk.h>
#include "header/getData.h"
#include "header/pasienUtil.h"
#include "header/riwayatUtil.h"

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


void on_button_clicked(GtkButton *button, gpointer user_data){
    const char *page_name = user_data;
    gtk_stack_set_visible_child_name(GTK_STACK(stackContainer), page_name);
}

GtkWidget *create_page_with_back_button(const char *title) {
    GtkWidget *page = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    GtkWidget *label = gtk_label_new(title);
    GtkWidget *backButton = gtk_button_new_with_label("Back to Landing Page");

    gtk_box_append(GTK_BOX(page), label);
    gtk_widget_set_halign(label, GTK_ALIGN_CENTER);

    gtk_box_append(GTK_BOX(page), backButton);
    gtk_widget_set_halign(backButton, GTK_ALIGN_CENTER);

    // Connect the back button to switch to the landing page
    g_signal_connect(backButton, "clicked", G_CALLBACK(on_button_clicked), (gpointer)"LandingPage");

    return page;
}

GtkWidget *LandingPage()
{
    GtkWidget *page = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    GtkWidget *funcButton;
    GtkWidget *grid;
    GtkWidget *label = gtk_label_new("Aplikasi Manajemen Pasien - Klinik X");

    gtk_box_append(GTK_BOX(page), label);
    gtk_widget_set_halign(label, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(label, GTK_ALIGN_CENTER);

    char *button_labels[6] = {"Data Pasien", "Riwayat pasien", "Informasi Pasien", "Laporan Pendapatan", "Informasi Penyakit dan Jumlah", "Informasi Kontrol Pasien"};

    char *page_names[6] = {"DataPasien", "RiwayatPasien", "InformasiPasien", "LaporanPendapatan", "InformasiPenyakit", "InformasiKontrol"};

    grid = gtk_grid_new();
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(page), grid);

    int k = 0;
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 3; j++){
            funcButton = gtk_button_new_with_label(button_labels[k]);
            gtk_grid_attach(GTK_GRID(grid), funcButton, j, i, 1, 1);

            g_signal_connect(funcButton, "clicked", G_CALLBACK(on_button_clicked), page_names[k]);

            k++;
        }
    }
    return page;
}

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

    dataPasienPage = create_page_with_back_button("Data Pasien");
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