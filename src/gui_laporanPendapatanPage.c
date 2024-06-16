#include "../header/gui_laporanPendapatanPage.h"

GtkWidget *DisplayPendapatanPage(int tahun)
{
    //setup page
    GtkWidget *page = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    GtkWidget *mainGrid = gtk_grid_new();
    gtk_box_append(GTK_BOX(page), mainGrid);

    GtkWidget *mainContent = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);
    gtk_grid_attach(GTK_GRID(mainGrid), mainContent, 1, 1, 1, 1);
    // gtk_widget_set_size_request(mainContent, WINDOW_WIDTH, WINDOW_HEIGHT - HEADER_HEIGHT - FOOTER_HEIGHT);
    gtk_widget_set_valign(mainContent, GTK_ALIGN_CENTER);

    char *month_labels[12] = {"Januari", "Februari", "Maret", "April", "Mei", "Juni", "Juli", "Agustus", "September", "Oktober", "November", "Desember"};

    //finding data
    int confirm;
    struct pendapatanTahun *Hasil = NULL;
    LaporanPendapatan(riwayatPasien, jumlahRiwayatPasien, &Hasil, tahun, &confirm);

    GtkWidget *monthLabel;
    GtkWidget *tempMonth;
    GtkWidget *namaPenyakit;
    int help;

    if (confirm == 0){
        GtkWidget *invalidLabel = gtk_label_new("Tidak ada data");
        GtkWidget *invalidbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
        gtk_box_append(GTK_BOX(invalidbox), invalidLabel);
        gtk_widget_set_halign(invalidLabel, GTK_ALIGN_CENTER);
        gtk_box_append(GTK_BOX(mainContent), invalidbox);
    }
    else {
        char info[256]; // Ensure that the buffer is large enough
        for (int i = 0; i < 14; i++)
        {
                if (i == 0){
                    snprintf(info, sizeof(info), "Januari %d : %d",tahun,(*Hasil).bulan.jan);
                }
                else if(i == 1){
                    snprintf(info, sizeof(info), "Februari %d : %d",tahun,(*Hasil).bulan.feb);
                }
                else if(i == 2){
                    snprintf(info, sizeof(info), "Maret %d : %d",tahun,(*Hasil).bulan.mar);
                }
                else if(i == 3){
                    snprintf(info, sizeof(info), "April %d : %d",tahun,(*Hasil).bulan.apr);
                }
                else if(i == 4){
                    snprintf(info, sizeof(info), "Mei %d : %d",tahun,(*Hasil).bulan.mei);
                }
                else if(i == 5){
                    snprintf(info, sizeof(info), "Juni %d : %d",tahun,(*Hasil).bulan.jun);
                }
                else if(i == 6){
                    snprintf(info, sizeof(info), "Juli %d : %d",tahun,(*Hasil).bulan.jul);
                }
                else if(i == 7){
                    snprintf(info, sizeof(info), "Agustus %d : %d",tahun,(*Hasil).bulan.agu);
                }
                else if(i == 8){
                    snprintf(info, sizeof(info), "September %d : %d",tahun,(*Hasil).bulan.sep);
                }
                else if(i == 9){
                    snprintf(info, sizeof(info), "Oktober %d : %d",tahun,(*Hasil).bulan.okt);
                }
                else if(i == 10){
                    snprintf(info, sizeof(info), "November %d : %d",tahun,(*Hasil).bulan.nov);
                }
                else if(i == 11){
                    snprintf(info, sizeof(info), "Desember %d : %d",tahun,(*Hasil).bulan.des);
                }
                else if(i == 12) {
                    snprintf(info, sizeof(info), "Jumlah dalam setahun %d : %d",tahun,(*Hasil).jumlahperTahun);
                }
                else {
                    snprintf(info, sizeof(info), "Rata-rata perBulan %d : %d",tahun,(*Hasil).jumlahperTahun/12);
                }
                GtkWidget *id_label = gtk_label_new(info);
                gtk_box_append(GTK_BOX(mainContent), id_label);
                gtk_widget_set_halign(id_label, GTK_ALIGN_CENTER);
            }
        }

    // Center the mainContent
    gtk_grid_set_column_spacing(GTK_GRID(mainGrid), 5);
    gtk_grid_set_row_spacing(GTK_GRID(mainGrid), 0);
    gtk_grid_set_column_homogeneous(GTK_GRID(mainGrid), TRUE);
    gtk_grid_set_row_homogeneous(GTK_GRID(mainGrid), TRUE);

    return page;
}

void integer_validation_laporanPendapatanPage(GtkButton *button, gpointer user_data) 
{
    GtkWidget *data = user_data;
    const char *input = gtk_editable_get_text(GTK_EDITABLE(data));
    char *endptr;
    int value = strtol(input, &endptr, 10); // Convert input to integer
    
    GtkWidget *tempWidget = gtk_stack_get_child_by_name(GTK_STACK(laporanPendapatanPage_Stack), "displayPendapatanPage");

        if (tempWidget != NULL)
        {   
            gtk_stack_remove(GTK_STACK(laporanPendapatanPage_Stack), tempWidget);
        }

    if (*endptr == '\0') {
        // Create the new page
        displayPendapatanPage = DisplayPendapatanPage(value);
        gtk_stack_add_named(GTK_STACK(laporanPendapatanPage_Stack), displayPendapatanPage, "displayPendapatanPage");

        // Get the window and replace its child with the new page
        gtk_stack_set_visible_child_name(GTK_STACK(laporanPendapatanPage_Stack), "displayPendapatanPage");
    } else {
        g_print("Invalid input, not an integer.\n");
    }
}

void reset_laporanPendapatanPage_Stack(GtkButton *button, gpointer user_data)
{
    GtkWidget *tempWidget = gtk_stack_get_child_by_name(GTK_STACK(laporanPendapatanPage_Stack), "displayPendapatanPage");

        if (tempWidget != NULL)
        {
            gtk_stack_remove(GTK_STACK(laporanPendapatanPage_Stack), tempWidget);
        }

    //back to landing page
    const char *page_name = user_data;
    gtk_stack_set_visible_child_name(GTK_STACK(stackContainer), page_name);
}

GtkWidget *addFooter_with_laporanPendapatanPage_reset(GtkWidget *page)
{
    GtkWidget *fixed = gtk_fixed_new();
    gtk_box_append(GTK_BOX(page), fixed);

    GtkWidget *footer = gtk_button_new_with_label("Back to Landing Page");
    gtk_fixed_put(GTK_FIXED(fixed), footer, 0, FOOTER_HEIGHT);
    g_signal_connect(footer, "clicked", G_CALLBACK(reset_laporanPendapatanPage_Stack), (gpointer) "LandingPage");
    return fixed;
}

GtkWidget *LaporanPendapatanPage()
{
    GtkWidget *page = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    GtkWidget *header = addHeader(page);

    laporanPendapatanPage_Stack = gtk_stack_new();
    gtk_stack_set_transition_type(GTK_STACK(laporanPendapatanPage_Stack), GTK_STACK_TRANSITION_TYPE_SLIDE_LEFT_RIGHT);

    GtkWidget *topLabel = gtk_label_new("Laporan Pendapatan per Tahun");
    gtk_box_append(GTK_BOX(page), topLabel);
    gtk_widget_set_halign(topLabel, GTK_ALIGN_CENTER);

    GtkWidget *cmdLabel = gtk_label_new("Masukkan Tahun ");
    GtkWidget *entry = gtk_entry_new();
    gtk_box_append(GTK_BOX(page), cmdLabel);

    gtk_widget_set_size_request(entry, 200, 30);
    gtk_box_append(GTK_BOX(page), entry);

    GtkWidget *button = gtk_button_new_with_label("Cari");
    gtk_widget_set_size_request(button, 100, 30);
    gtk_box_append(GTK_BOX(page), button);

    gtk_box_append(GTK_BOX(page), laporanPendapatanPage_Stack);

    GtkWidget *mainGrid = gtk_grid_new();
    gtk_box_append(GTK_BOX(page), mainGrid);

    GtkWidget *mainContent = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_grid_attach(GTK_GRID(mainGrid), mainContent, 1, 1, 1, 1);
    gtk_widget_set_size_request(mainContent, WINDOW_WIDTH, WINDOW_HEIGHT - HEADER_HEIGHT - FOOTER_HEIGHT);
    gtk_widget_set_valign(mainContent, GTK_ALIGN_CENTER);

    g_signal_connect(button, "clicked", G_CALLBACK(integer_validation_laporanPendapatanPage), entry);

    // Center the mainContent
    gtk_grid_set_column_spacing(GTK_GRID(mainGrid), 0);
    gtk_grid_set_row_spacing(GTK_GRID(mainGrid), 0);
    gtk_grid_set_column_homogeneous(GTK_GRID(mainGrid), TRUE);
    gtk_grid_set_row_homogeneous(GTK_GRID(mainGrid), TRUE);

    GtkWidget *footer = addFooter_with_laporanPendapatanPage_reset(page);
    return page;
}