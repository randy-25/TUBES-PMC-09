#include "../header/gui_penyakitperWaktuPage.h"

// This function clears the current display page.

void reset_displayBulanBox()
{
    GtkWidget *child = gtk_widget_get_first_child(GTK_WIDGET(displayBulanBox));
    while (child != NULL)
    {
        GtkWidget *next = gtk_widget_get_next_sibling(child);
        gtk_widget_unparent(child);
        child = next;
    }
}

void reset_displayPenyakitPage()
{
    GtkWidget *child = gtk_widget_get_first_child(GTK_WIDGET(displayPenyakitPage));
    while (child != NULL)
    {
        GtkWidget *next = gtk_widget_get_next_sibling(child);
        gtk_widget_unparent(child);
        child = next;
    }
}

void *displayBulan(GtkButton *button, gpointer user_data)
{   
    reset_displayBulanBox();
    InformasiPenyakitEntry *entry = (InformasiPenyakitEntry*)user_data;

    const char *input = gtk_editable_get_text(GTK_EDITABLE(entry->entry_data));
    
    int tahun = entry->tahun;

    char *month_labels[12] = {
        "Januari", "Februari", "Maret", "April", "Mei", "Juni", 
        "Juli", "Agustus", "September", "Oktober", "November", "Desember"
    };

    // Finding data
    int confirm;
    int penyakit;
    int help = 0;
    struct sortPenyakit *hasil = NULL;

    // Call the function to get data for the given year.
    DataPenyakitperWaktu(riwayatPasien, jumlahRiwayatPasien, &hasil, &confirm, &penyakit, tahun);

    int valid = 0;

    for (int j = 0; j < 12; j++) {
        if (strcmp(month_labels[j], input) == 0){
            help = j * penyakit;
            GtkWidget *monthLabel = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
            GtkWidget *tempMonth = gtk_label_new(month_labels[j]);
            gtk_box_append(GTK_BOX(monthLabel), tempMonth);
            gtk_widget_set_halign(tempMonth, GTK_ALIGN_CENTER);

            for (int k = 0; k < penyakit; k++) {
                if (hasil[help].jumlah != 0) {
                    valid = 1;
                    char info[256];
                    snprintf(info, sizeof(info), "%s = %d", hasil[help].namaPenyakit, hasil[help].jumlah);
                    GtkWidget *id_label = gtk_label_new(info);
                    gtk_box_append(GTK_BOX(monthLabel), id_label);
                }
                help++;
            }
            gtk_box_append(GTK_BOX(displayBulanBox), monthLabel);
            GtkWidget *separator = gtk_label_new("-------------------------------------------------");
            gtk_box_append(GTK_BOX(displayBulanBox), separator);
            break;
        }
    }
    if (valid == 0){
        GtkWidget *invalidLabel = gtk_label_new("Tidak ada data");
        gtk_box_append(GTK_BOX(displayBulanBox), invalidLabel);
    }
}

// This function displays the penyakit information for a given year.
void *DisplayPenyakitPage(int tahun)
{     

    char *month_labels[12] = {
        "Januari", "Februari", "Maret", "April", "Mei", "Juni", 
        "Juli", "Agustus", "September", "Oktober", "November", "Desember"
    };

    // Finding data
    int confirm;
    int penyakit;
    struct sortPenyakit *hasil = NULL;

    // Call the function to get data for the given year.
    DataPenyakitperWaktu(riwayatPasien, jumlahRiwayatPasien, &hasil, &confirm, &penyakit, tahun);
    

    if (confirm == 0) {
        GtkWidget *invalidLabel = gtk_label_new("Tidak ada data");
        GtkWidget *invalidbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
        gtk_box_append(GTK_BOX(invalidbox), invalidLabel);
        gtk_widget_set_halign(invalidLabel, GTK_ALIGN_CENTER);
        gtk_box_append(GTK_BOX(displayPenyakitPage), invalidbox);
        gtk_widget_set_vexpand(invalidbox, TRUE);
    } else {
        GtkWidget *baseGrid = gtk_grid_new();
        gtk_widget_set_size_request(baseGrid, WINDOW_WIDTH, 200);
        gtk_widget_set_vexpand(baseGrid, TRUE);
        gtk_grid_set_column_homogeneous(GTK_GRID(baseGrid), TRUE);
        gtk_grid_set_row_homogeneous(GTK_GRID(baseGrid), TRUE);
        gtk_box_append(GTK_BOX(displayPenyakitPage), baseGrid);

        // Right half of the page
        GtkWidget *rightHalf = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
        GtkWidget *bulanLabel = gtk_label_new("Informasi Bulanan");
        gtk_box_append(GTK_BOX(rightHalf), bulanLabel);

        GtkWidget *formLabel = gtk_label_new("Masukkan Bulan : ");
        GtkWidget *entry = gtk_entry_new();
        
        gtk_box_append(GTK_BOX(rightHalf), formLabel);
        gtk_box_append(GTK_BOX(rightHalf), entry);

        GtkWidget *button = gtk_button_new_with_label("Cari");
        gtk_widget_set_halign(button, GTK_ALIGN_CENTER);
        gtk_box_append(GTK_BOX(rightHalf), button);

        displayBulanBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
        gtk_widget_set_size_request(displayPenyakitPage, WINDOW_WIDTH/2, 100);
        gtk_box_append(GTK_BOX(rightHalf), displayBulanBox);

        reset_displayBulanBox();

        InformasiPenyakitEntry *entry_data = g_malloc(sizeof(InformasiPenyakitEntry));
        entry_data->tahun = tahun;
        entry_data->entry_data = entry;

        g_signal_connect(button, "clicked", G_CALLBACK(displayBulan), entry_data);

        // for (int j = 0; j < 12; j++) {
        //     GtkWidget *monthLabel = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
        //     GtkWidget *tempMonth = gtk_label_new(month_labels[j]);
        //     gtk_box_append(GTK_BOX(monthLabel), tempMonth);
        //     gtk_widget_set_halign(tempMonth, GTK_ALIGN_CENTER);

        //     for (int k = 0; k < penyakit; k++) {
        //         if (hasil[help].jumlah != 0) {
        //             char info[256];
        //             snprintf(info, sizeof(info), "%s = %d", hasil[help].namaPenyakit, hasil[help].jumlah);
        //             GtkWidget *id_label = gtk_label_new(info);
        //             gtk_box_append(GTK_BOX(monthLabel), id_label);
        //         }
        //         help++;
        //     }
        //     gtk_box_append(GTK_BOX(rightHalf), monthLabel);
        //     GtkWidget *separator = gtk_label_new("-------------------------------------------------");
        //     gtk_box_append(GTK_BOX(rightHalf), separator);
        // }

        GtkWidget *rightHalfScrolledWindow = gtk_scrolled_window_new();
        gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(rightHalfScrolledWindow), rightHalf);
        gtk_widget_set_size_request(rightHalfScrolledWindow, WINDOW_WIDTH / 2, 150);
        gtk_grid_attach(GTK_GRID(baseGrid), rightHalfScrolledWindow, 1, 0, 1, 1);

        // Left half of the page
        GtkWidget *leftHalf = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
        GtkWidget *yearLabel = gtk_label_new("Informasi per Tahun");
        gtk_box_append(GTK_BOX(leftHalf), yearLabel);
        gtk_grid_attach(GTK_GRID(baseGrid), leftHalf, 0, 0, 1, 1);

        int help = 12*penyakit;

        for (int k = 0; k < penyakit; k++) {
            if (hasil[help].jumlah != 0) {
                char info[256];
                snprintf(info, sizeof(info), "%s = %d", hasil[help].namaPenyakit, hasil[help].jumlah);
                GtkWidget *id_label = gtk_label_new(info);
                gtk_box_append(GTK_BOX(leftHalf), id_label);
            }
            help++;
        }
    }

    // Free the allocated memory for hasil after use.
    free(hasil);
}

// This function validates the input year and displays the penyakit page if valid.
void integer_validation_penyakitperWaktuPage(GtkButton *button, gpointer user_data) 
{
    GtkWidget *data = user_data;
    const char *input = gtk_editable_get_text(GTK_EDITABLE(data));
    char *endptr;
    int value = strtol(input, &endptr, 10); // Convert input to integer

    reset_displayPenyakitPage();

    if (*endptr == '\0') {
        // Create the new page
        DisplayPenyakitPage(value);
    } else {
        g_print("Invalid input, not an integer.\n");
    }
}

// This function resets the stack and navigates back to the landing page.
void reset_penyakitperWaktuPage_Stack(GtkButton *button, gpointer user_data)
{
    reset_displayPenyakitPage();
    const char *page_name = user_data;
    gtk_stack_set_visible_child_name(GTK_STACK(stackContainer), page_name);
}

// Adds footer to the page with reset functionality.
GtkWidget *addFooter_with_InformasiPasienPage_reset(GtkWidget *page)
{
    GtkWidget *fixed = gtk_fixed_new();
    gtk_box_append(GTK_BOX(page), fixed);

    GtkWidget *footer = gtk_button_new_with_label("Back to Landing Page");
    gtk_fixed_put(GTK_FIXED(fixed), footer, 0, FOOTER_HEIGHT);
    g_signal_connect(footer, "clicked", G_CALLBACK(reset_penyakitperWaktuPage_Stack), (gpointer) "LandingPage");
    return fixed;
}

// Main Page
GtkWidget *InformasiPenyakitPage()
{
    GtkWidget *page = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    
    GtkWidget *header = addHeader(page);

    GtkWidget *title = gtk_label_new("Informasi Penyakit Tahunan");
    gtk_box_append(GTK_BOX(page), title);
    gtk_widget_set_halign(title, GTK_ALIGN_CENTER);

    GtkWidget *formLabel = gtk_label_new("Masukkan Tahun : ");
    GtkWidget *entry = gtk_entry_new();
    
    gtk_box_append(GTK_BOX(page), formLabel);
    gtk_box_append(GTK_BOX(page), entry);

    GtkWidget *button = gtk_button_new_with_label("Cari");
    gtk_widget_set_halign(button, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(page), button);

    displayPenyakitPage = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_size_request(displayPenyakitPage, WINDOW_WIDTH, 400);
    gtk_box_append(GTK_BOX(page), displayPenyakitPage);

    g_signal_connect(button, "clicked", G_CALLBACK(integer_validation_penyakitperWaktuPage), entry);

    GtkWidget *footer = addFooter_with_InformasiPasienPage_reset(page);

    return page;
}