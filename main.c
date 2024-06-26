#include "header/util_getData.h"
#include "header/util_pasienUtil.h"
#include "header/util_riwayatUtil.h"
#include "header/util_informasiPasienUtil.h"
#include "header/util_laporanPendapatanUtil.h"
#include "header/util_pasienKontrolUtil.h"
#include "header/util_penyakitperWaktuUtil.h"
#include "header/util_saveData.h"

#include "header/guiDataType.h"
#include "header/gui_basePage.h"
#include "header/gui_pasienDataPage.h"
#include "header/gui_riwayatPasienPage.h"
#include "header/gui_informasiPasienPage.h"
#include "header/gui_penyakitperWaktuPage.h"
#include "header/gui_laporanPendapatanPage.h"


#include "header/gui_pasienKontrol.h"

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


// ------- RIWAYAT PASIEN PAGE -------
GtkWidget *riwayatPasienPage_Stack;

// CARI RIWAYAT PASIEN PAGE VARIABLE
GtkWidget *riwayatPasienPage_cariRiwayat_pasienInfo;

// TAMBAH RIWAYAT PASIEN PAGE VARIABLE
GtkWidget *riwayatPasienPage_tambahData_pasienInfo;

// UBAH RIWAYAT PASIEN PAGE VARIABLE
GtkWidget *riwayatPasienPage_ubahData_pasienInfo;

// HAPUS RIWAYAT PASIEN PAGE VARIABLE
GtkWidget *riwayatPasienPage_hapusData_pasienInfo;
// ------- END OF RIWAYAT PASIEN PAGE -------


// ------- INFORMASI PASIEN PAGE -------
GtkWidget *informasiPasienPage_pasienInfo;
// ------- END OF INFORMASI PASIEN PAGE -------


//---------- PENYAKIT PER WAKTU PAGE ----------
GtkWidget *penyakitperWaktuPage_pasienInfo;

// DISPLAY PENYAKIT PAGE
GtkWidget *displayPenyakitPage;

// DISPLAY PENYAKIT PERBULAN PAGE
GtkWidget *displayBulanBox;
//------- END OF PENYAKIT PER WAKTU PAGE -------


//---------- LAPORAN PENDAPATAN PAGE -----------
GtkWidget *laporanPendapatanPage_Stack;

// DISPLAY PENYAKIT PAGE
GtkWidget *displayPendapatanPage;
//------- END OF LAPORAN PENDAPATAN PAGE -------


// ------- INFORMASI PASIEN KONTROL PAGE -------
GtkWidget *informasiPasienKontrolPage_pasienInfo;
// ------- END OF INFORMASI PASIEN KONTROL PAGE -------


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

    riwayatPasienPage = RiwayatPasienPage();
    gtk_stack_add_named(GTK_STACK(stackContainer), riwayatPasienPage, "RiwayatPasien");

    informasiPasienPage = InformasiPasienPage();
    gtk_stack_add_named(GTK_STACK(stackContainer), informasiPasienPage, "InformasiPasien");

    laporanPendapatanPage = LaporanPendapatanPage();
    gtk_stack_add_named(GTK_STACK(stackContainer), laporanPendapatanPage, "LaporanPendapatan");

    informasiPenyakitPage = InformasiPenyakitPage();
    gtk_stack_add_named(GTK_STACK(stackContainer), informasiPenyakitPage, "InformasiPenyakit");

    informasiKontrolPage = PasienKontrolPage();
    gtk_stack_add_named(GTK_STACK(stackContainer), informasiKontrolPage, "InformasiKontrol");

    gtk_widget_set_visible(GTK_WIDGET(window), TRUE);
}

int main(int argc, char **argv){
    struct biaya *biayaPerawatan = NULL;

    get_DataPasien_CSV(&pasien, &jumlahPasien);
    get_RiwayatPasien_CSV(&riwayatPasien, &jumlahRiwayatPasien);
    get_BiayaTindakan_CSV(&biayaPerawatan);

// <<<<<<<<< Temporary merge branch 1
// =========
    // print data pasien
    // printf("%d\n", jumlahPasien);
    // for (int i = 0; i < jumlahPasien; i++){
    //     printDataPasien_CSV(pasien[i]);
    // }

    // //print riwayat pasien
    // for (int i = 0; i < jumlahRiwayatPasien; i++){
    //     printRiwayatPasien_CSV(riwayatPasien[i]);
    // }

// >>>>>>>>> Temporary merge branch 2
    GtkApplication *app;
    int status;

    app = gtk_application_new("com.PatientManagement.Application3", 0);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    status = g_application_run(G_APPLICATION(app), argc, argv);

    if(status == 0){
        write_DataPasien_CSV(pasien, jumlahPasien);
        write_RiwayatPasien_CSV(riwayatPasien, jumlahRiwayatPasien);
    }

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