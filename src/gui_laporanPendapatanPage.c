#include "../header/gui_laporanPendapatanPage.h"

void reset_displayPendapatanPage()
{
    GtkWidget *child = gtk_widget_get_first_child(GTK_WIDGET(displayPendapatanPage));
    while (child != NULL)
    {
        GtkWidget *next = gtk_widget_get_next_sibling(child);
        gtk_box_remove(GTK_BOX(displayPendapatanPage), child);
        child = next;
    }
}

void *DisplayPendapatanPage(int tahun)
{
    // //setup page
    // GtkWidget *page = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);


    // GtkWidget *mainGrid = gtk_grid_new();
    // gtk_box_append(GTK_BOX(page), mainGrid);

    // GtkWidget *mainContent = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
    // gtk_grid_attach(GTK_GRID(mainGrid), mainContent, 1, 1, 1, 1);
    // // gtk_widget_set_size_request(mainContent, WINDOW_WIDTH, WINDOW_HEIGHT - HEADER_HEIGHT - FOOTER_HEIGHT);
    // gtk_widget_set_valign(mainContent, GTK_ALIGN_CENTER);

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
        gtk_box_append(GTK_BOX(displayPendapatanPage), invalidLabel);
    }
    else {
        GtkWidget *baseGrid = gtk_grid_new();
        gtk_widget_set_size_request(baseGrid, WINDOW_WIDTH, 300);
        gtk_widget_set_vexpand(baseGrid, TRUE);
        gtk_grid_set_column_homogeneous(GTK_GRID(baseGrid), TRUE);
        gtk_grid_set_row_homogeneous(GTK_GRID(baseGrid), TRUE);
        gtk_box_append(GTK_BOX(displayPendapatanPage), baseGrid);

        char info[256];//buffrer

        GtkWidget *leftHalf = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

        GtkWidget *leftLabel = gtk_label_new("Informasi per Tahun");
        gtk_box_append(GTK_BOX(leftHalf), leftLabel);

        snprintf(info, sizeof(info), "Jumlah pendapatan tahun %d : %d",tahun,(*Hasil).jumlahperTahun);
        GtkWidget *jumlah = gtk_label_new(info);
        gtk_box_append(GTK_BOX(leftHalf), jumlah);

        snprintf(info, sizeof(info), "Rata-rata perBulan : %d",(*Hasil).jumlahperTahun/12);
        GtkWidget *id_label = gtk_label_new(info);
        gtk_box_append(GTK_BOX(leftHalf), id_label);

        // gtk_center_box_set_center_widget(GTK_CENTER_BOX(leftHalf), leftLabel);
        gtk_grid_attach(GTK_GRID(baseGrid), leftHalf, 0, 0, 1, 1);

        // right half of the page
        GtkWidget *rightHalf = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

        GtkWidget *month = gtk_label_new("Informasi per Bulan");
        gtk_box_append(GTK_BOX(rightHalf), month);
        for (int i = 0; i < 12; i++)
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
                GtkWidget *id_label = gtk_label_new(info);
                gtk_box_append(GTK_BOX(rightHalf), id_label);
        }
        GtkWidget *rightHalf_scrolled_window = gtk_scrolled_window_new();
        gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(rightHalf_scrolled_window), rightHalf);

        gtk_widget_set_size_request(rightHalf_scrolled_window, WINDOW_WIDTH / 2, 150);
        gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(rightHalf_scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
        gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(rightHalf_scrolled_window), rightHalf);
        gtk_grid_attach(GTK_GRID(baseGrid), rightHalf_scrolled_window, 1, 0, 1, 1);
    }

    // Center the mainContent
}

void integer_validation_laporanPendapatanPage(GtkButton *button, gpointer user_data) 
{
    GtkWidget *data = user_data;
    const char *input = gtk_editable_get_text(GTK_EDITABLE(data));
    char *endptr;
    int value = strtol(input, &endptr, 10); // Convert input to integer
    
    // GtkWidget *tempWidget = gtk_stack_get_child_by_name(GTK_STACK(laporanPendapatanPage_Stack), "displayPendapatanPage");

    //     if (tempWidget != NULL)
    //     {   
    //         gtk_stack_remove(GTK_STACK(laporanPendapatanPage_Stack), tempWidget);
    //     }
    reset_displayPendapatanPage();

    if (*endptr == '\0') {
        // Create the new page
        DisplayPendapatanPage(value);
        // gtk_stack_add_named(GTK_STACK(laporanPendapatanPage_Stack), displayPendapatanPage, "displayPendapatanPage");

        // // Get the window and replace its child with the new page
        // gtk_stack_set_visible_child_name(GTK_STACK(laporanPendapatanPage_Stack), "displayPendapatanPage");
    } else {
        g_print("Invalid input, not an integer.\n");
    }
}

void reset_laporanPendapatanPage(GtkButton *button, gpointer user_data)
{
    // GtkWidget *tempWidget = gtk_stack_get_child_by_name(GTK_STACK(laporanPendapatanPage_Stack), "displayPendapatanPage");

    //     if (tempWidget != NULL)
    //     {
    //         gtk_stack_remove(GTK_STACK(laporanPendapatanPage_Stack), tempWidget);
    //     }
    reset_displayPendapatanPage();

    //back to landing page
    const char *page_name = user_data;
    gtk_stack_set_visible_child_name(GTK_STACK(stackContainer), page_name);
}

GtkWidget *addFooter_with_laporanPendapatanPage(GtkWidget *page)
{
    GtkWidget *fixed = gtk_fixed_new();
    gtk_box_append(GTK_BOX(page), fixed);

    GtkWidget *footer = gtk_button_new_with_label("Back to Landing Page");
    gtk_fixed_put(GTK_FIXED(fixed), footer, 0, FOOTER_HEIGHT);
    g_signal_connect(footer, "clicked", G_CALLBACK(reset_laporanPendapatanPage), (gpointer) "LandingPage");
    return fixed;
}

GtkWidget *LaporanPendapatanPage()
{
    // GtkWidget *page = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    // GtkWidget *header = addHeader(page);

    // laporanPendapatanPage_Stack = gtk_stack_new();
    // gtk_stack_set_transition_type(GTK_STACK(laporanPendapatanPage_Stack), GTK_STACK_TRANSITION_TYPE_SLIDE_LEFT_RIGHT);

    // GtkWidget *topLabel = gtk_label_new("Laporan Pendapatan Tahunan");
    // gtk_box_append(GTK_BOX(page), topLabel);
    // gtk_widget_set_halign(topLabel, GTK_ALIGN_CENTER);

    // GtkWidget *cmdLabel = gtk_label_new("Masukkan Tahun ");
    // GtkWidget *entry = gtk_entry_new();
    // gtk_box_append(GTK_BOX(page), cmdLabel);

    // gtk_widget_set_size_request(entry, 200, 30);
    // gtk_box_append(GTK_BOX(page), entry);

    // GtkWidget *button = gtk_button_new_with_label("Cari");
    // gtk_widget_set_size_request(button, 100, 30);
    // gtk_box_append(GTK_BOX(page), button);

    // gtk_box_append(GTK_BOX(page), laporanPendapatanPage_Stack);
    // gtk_widget_set_size_request(laporanPendapatanPage_Stack, WINDOW_WIDTH, 400);

    // g_signal_connect(button, "clicked", G_CALLBACK(integer_validation_laporanPendapatanPage), entry);

    // GtkWidget *footer = addFooter_with_laporanPendapatanPage_reset(page);

    GtkWidget *page;
    GtkWidget *entry;
    GtkWidget *button;

    page = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    GtkWidget *header = addHeader(page);

    GtkWidget *title = gtk_label_new("Laporan Pendapatan Tahunan");
    gtk_box_append(GTK_BOX(page), title);
    gtk_widget_set_halign(title, GTK_ALIGN_CENTER);

    entry = gtk_entry_new();
    GtkWidget *formLabel = gtk_label_new("Masukkan Tahun : ");

    gtk_box_append(GTK_BOX(page), formLabel);
    gtk_box_append(GTK_BOX(page), entry);

    button = gtk_button_new_with_label("Cari");
    gtk_widget_set_halign(button, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(page), button);

    displayPendapatanPage = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_size_request(displayPendapatanPage, WINDOW_WIDTH, 450);
    gtk_box_append(GTK_BOX(page), displayPendapatanPage);

    g_signal_connect(button, "clicked", G_CALLBACK(integer_validation_laporanPendapatanPage), entry);
    GtkWidget *footer = addFooter_with_laporanPendapatanPage(page);
    return page;
}