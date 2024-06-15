#include "header/util_getData.h"
#include "header/util_pasienUtil.h"
#include "header/util_riwayatUtil.h"

#include "header/guiDataType.h"
#include "header/gui_pasienDataPage.h"
#include "header/gui_basePage.h"

// ------------------ GLOBAL VARIABLE ------------------
struct dataPasien *pasien = NULL;
struct riwayat *riwayatPasien = NULL;
int jumlahPasien = 0;
int jumlahRiwayatPasien = 0;

// Base Page Variable
GtkWidget *stackContainer;
GtkWidget *landingPage;
GtkWidget *dataPasienPage;
GtkWidget *riwayatPasienPage;
GtkWidget *informasiPasienPage;
GtkWidget *laporanPendapatanPage;
GtkWidget *informasiPenyakitPage;
GtkWidget *informasiKontrolPage;

// ------DATA PASIEN PAGE VARIABLE------
GtkWidget *dataPasienPage_Stack;

// CARI DATA PASIEN PAGE VARIABLE
GtkWidget *dataPasienPage_cariData_pasienInfo;

// TAMBAH DATA PASIEN PAGE VARIABLE
GtkWidget *dataPasienPage_tambahData_pasienInfo;

// UBAH DATA PASIEN PAGE VARIABLE
GtkWidget *dataPasienPage_ubahData_pasienInfo;

// HAPUS DATA PASIEN PAGE VARIABLE
GtkWidget *dataPasienPage_hapusData_pasienInfo;
// ------END OF DATA PASIEN PAGE VARIABLE------

// --------------END OF GLOBAL VARIABLE------------------

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

    app = gtk_application_new("com.PatientManagement.Application3", G_APPLICATION_DEFAULT_FLAGS);
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