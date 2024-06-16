#include "../header/gui_penyakitperWaktuPage.h"

GtkWidget *DisplayPenyakitPage (int tahun)
{     
    //setup page
    GtkWidget *page = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    GtkWidget *mainGrid = gtk_grid_new();
    gtk_box_append(GTK_BOX(page), mainGrid);

    GtkWidget *mainContentDisplayPage = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_grid_attach(GTK_GRID(mainGrid), mainContentDisplayPage, 1, 1, 1, 1);
    gtk_widget_set_size_request(mainContentDisplayPage, WINDOW_WIDTH, WINDOW_HEIGHT - HEADER_HEIGHT - FOOTER_HEIGHT);
    gtk_widget_set_valign(mainContentDisplayPage, GTK_ALIGN_CENTER);

    char *month_labels[12] = {"Januari", "Februari", "Maret", "April", "Mei", "Juni", "Juli", "Agustus", "September", "Oktober", "November", "Desember"};

    //finding data
    int confirm;
    int penyakit;
    int help = 0;
    struct sortPenyakit *hasil;

    DataPenyakitperWaktu(riwayatPasien, jumlahRiwayatPasien,&hasil,&confirm,&penyakit, tahun);

    GtkWidget *monthLabel;
    GtkWidget *tempMonth;
    GtkWidget *namaPenyakit;

    if (confirm == 0){
        GtkWidget *invalidLabel = gtk_label_new("Tidak ada data");
        GtkWidget *invalidbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
        gtk_box_append(GTK_BOX(invalidbox), invalidLabel);
        gtk_widget_set_halign(invalidLabel, GTK_ALIGN_CENTER);
        gtk_box_append(GTK_BOX(mainContentDisplayPage), invalidbox);
    }
    else {
        GtkWidget *grid = gtk_grid_new();
        gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
        gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
        gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
        gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
        gtk_box_append(GTK_BOX(mainContentDisplayPage), grid);

        char info[256]; // Ensure that the buffer is large enough
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

                for (int k = 0; k < penyakit; k++)
                {   
                    snprintf(info, sizeof(info), "%s = %d", hasil[help].namaPenyakit, hasil[help].jumlah);
                    GtkWidget *id_label = gtk_label_new(info);
                    gtk_box_append(GTK_BOX(monthLabel), id_label);
                    gtk_widget_set_halign(tempMonth, GTK_ALIGN_CENTER);
                    help++;
                }

                gtk_grid_attach(GTK_GRID(grid), monthLabel, j*2, i, 1, 1);
            }
        }

        //Total
        GtkWidget *yearbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
        GtkWidget *yearlabel = gtk_label_new("Jumlah per Tahun");
        gtk_box_append(GTK_BOX(yearbox), yearlabel);
        gtk_widget_set_halign(yearlabel, GTK_ALIGN_CENTER);

        for (int i = 0; i < penyakit; i++){
            snprintf(info, sizeof(info), "%s = %d", hasil[help].namaPenyakit, hasil[help].jumlah);
            GtkWidget *id_label = gtk_label_new(info);
            gtk_box_append(GTK_BOX(yearbox), id_label);
            gtk_widget_set_halign(tempMonth, GTK_ALIGN_CENTER);
            help++;
        }
        gtk_grid_attach(GTK_GRID(grid), yearbox, 5,2,1,1);
    }

    // Center the mainContentDisplayPage
    gtk_grid_set_column_spacing(GTK_GRID(mainGrid), 0);
    gtk_grid_set_row_spacing(GTK_GRID(mainGrid), 10);
    gtk_grid_set_column_homogeneous(GTK_GRID(mainGrid), TRUE);
    gtk_grid_set_row_homogeneous(GTK_GRID(mainGrid), TRUE);

    return page;
}

void integer_validation_penyakitperWaktuPage(GtkButton *button, gpointer user_data) 
{
    GtkWidget *data = user_data;
    const char *input = gtk_editable_get_text(GTK_EDITABLE(data));
    char *endptr;
    int value = strtol(input, &endptr, 10); // Convert input to integer

    GtkWidget *tempWidget = gtk_stack_get_child_by_name(GTK_STACK(penyakitperWaktuPage_Stack), "displayPenyakitPage");

    if (tempWidget != NULL)
    {
        gtk_stack_remove(GTK_STACK(penyakitperWaktuPage_Stack), tempWidget);
    }

    if (*endptr == '\0') {
        // Create the new page
        GtkWidget *displayPenyakitPage = DisplayPenyakitPage(value);
        gtk_stack_add_named(GTK_STACK(penyakitperWaktuPage_Stack), displayPenyakitPage, "displayPenyakitPage");
        
        // Get the window and replace its child with the new page
        gtk_stack_set_visible_child_name(GTK_STACK(penyakitperWaktuPage_Stack), "displayPenyakitPage");
    } else {
        g_print("Invalid input, not an integer.\n");
    }
}

void reset_penyakitperWaktuPage_Stack(GtkButton *button, gpointer user_data)
{
    GtkWidget *tempWidget = gtk_stack_get_child_by_name(GTK_STACK(penyakitperWaktuPage_Stack), "displayPenyakitPage");

        if (tempWidget != NULL)
        {
            gtk_stack_remove(GTK_STACK(penyakitperWaktuPage_Stack), tempWidget);
        }

    //back to landing page
    const char *page_name = user_data;
    gtk_stack_set_visible_child_name(GTK_STACK(stackContainer), page_name);
}

GtkWidget *addFooter_with_InformasiPasienPageStack_reset(GtkWidget *page)
{
    GtkWidget *fixed = gtk_fixed_new();
    gtk_box_append(GTK_BOX(page), fixed);

    GtkWidget *footer = gtk_button_new_with_label("Back to Landing Page");
    gtk_fixed_put(GTK_FIXED(fixed), footer, 0, FOOTER_HEIGHT);
    gtk_stack_set_visible_child_name(GTK_STACK(penyakitperWaktuPage_Stack), "MainGrid");
    g_signal_connect(footer, "clicked", G_CALLBACK(reset_penyakitperWaktuPage_Stack), (gpointer) "LandingPage");
    return fixed;
}

//Main Page
GtkWidget *InformasiPenyakitPage()
{
    GtkWidget *page = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    GtkWidget *header = addHeader(page);

    penyakitperWaktuPage_Stack = gtk_stack_new();
    gtk_stack_set_transition_type(GTK_STACK(penyakitperWaktuPage_Stack), GTK_STACK_TRANSITION_TYPE_SLIDE_LEFT_RIGHT);

    GtkWidget *topLabel = gtk_label_new("Informasi Penyakit per Tahun");
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


    gtk_box_append(GTK_BOX(page), penyakitperWaktuPage_Stack);

    GtkWidget *mainGrid = gtk_grid_new();
    gtk_stack_add_named(GTK_STACK(penyakitperWaktuPage_Stack), mainGrid, "MainGrid");

    GtkWidget *mainContent = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_grid_attach(GTK_GRID(mainGrid), mainContent, 0, 0, 1, 1);
    gtk_widget_set_size_request(mainContent, WINDOW_WIDTH, WINDOW_HEIGHT - HEADER_HEIGHT - FOOTER_HEIGHT);
    gtk_widget_set_valign(mainContent, GTK_ALIGN_CENTER);

    g_signal_connect(button, "clicked", G_CALLBACK(integer_validation_penyakitperWaktuPage), entry);

    // Center the mainContent
    gtk_grid_set_column_spacing(GTK_GRID(mainGrid), 0);
    gtk_grid_set_row_spacing(GTK_GRID(mainGrid), 0);
    gtk_grid_set_column_homogeneous(GTK_GRID(mainGrid), TRUE);
    gtk_grid_set_row_homogeneous(GTK_GRID(mainGrid), TRUE);

    GtkWidget *footer = addFooter_with_InformasiPasienPageStack_reset(page);
    return page;
}
