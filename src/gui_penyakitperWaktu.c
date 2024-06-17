#include "../header/gui_penyakitperWaktuPage.h"

GtkWidget *DisplayPenyakitPage(int tahun)
{
    // setup page
    GtkWidget *page = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_size_request(page, WINDOW_WIDTH, 400);

    // GtkWidget *mainGrid = gtk_grid_new();
    // gtk_box_append(GTK_BOX(page), mainGrid);

    // GtkWidget *mainContentDisplayPage = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    // gtk_grid_attach(GTK_GRID(mainGrid), mainContentDisplayPage, 1, 1, 1, 1);
    // gtk_widget_set_size_request(mainContentDisplayPage, WINDOW_WIDTH, 300);
    // gtk_widget_set_valign(mainContentDisplayPage, GTK_ALIGN_CENTER);

    char *month_labels[12] = {"Januari", "Februari", "Maret", "April", "Mei", "Juni", "Juli", "Agustus", "September", "Oktober", "November", "Desember"};

    // finding data
    int confirm;
    int penyakit;
    int help = 0;
    struct sortPenyakit *hasil;

    DataPenyakitperWaktu(riwayatPasien, jumlahRiwayatPasien, &hasil, &confirm, &penyakit, tahun);

    GtkWidget *monthLabel;
    GtkWidget *tempMonth;
    GtkWidget *namaPenyakit;

    if (confirm == 0)
    {
        GtkWidget *invalidLabel = gtk_label_new("Tidak ada data");
        GtkWidget *invalidbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
        gtk_box_append(GTK_BOX(invalidbox), invalidLabel);
        gtk_widget_set_halign(invalidLabel, GTK_ALIGN_CENTER);
        gtk_box_append(GTK_BOX(page), invalidbox);
    }
    else
    {
        GtkWidget *baseGrid = gtk_grid_new();
        gtk_widget_set_size_request(baseGrid, WINDOW_WIDTH, 200);
        gtk_widget_set_vexpand(baseGrid, TRUE);
        gtk_grid_set_column_homogeneous(GTK_GRID(baseGrid), TRUE);
        gtk_grid_set_row_homogeneous(GTK_GRID(baseGrid), TRUE);
        gtk_box_append(GTK_BOX(page), baseGrid);

        // Create new labels to display the data
        char info[256]; // Ensure that the buffer is large enough

        // right half of the page
        GtkWidget *rightHalf = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

        GtkWidget *bulanLabel = gtk_label_new("Informasi Bulanan");
        gtk_box_append(GTK_BOX(rightHalf), bulanLabel);

        for (int j = 0; j < 12; j++)
        {
            monthLabel = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
            tempMonth = gtk_label_new(month_labels[j]);

            gtk_box_append(GTK_BOX(monthLabel), tempMonth);
            gtk_widget_set_halign(tempMonth, GTK_ALIGN_CENTER);

            for (int k = 0; k < penyakit; k++)
            {
                if (hasil[help].jumlah != 0)
                {
                    snprintf(info, sizeof(info), "%s = %d", hasil[help].namaPenyakit, hasil[help].jumlah);
                    GtkWidget *id_label = gtk_label_new(info);
                    gtk_box_append(GTK_BOX(monthLabel), id_label);
                }
                help++;
            }
            gtk_box_append(GTK_BOX(rightHalf), monthLabel);
            GtkWidget *label = gtk_label_new("-------------------------------------------------");
            gtk_box_append(GTK_BOX(rightHalf), label);
        }

        GtkWidget *rightHalf_scrolled_window = gtk_scrolled_window_new();
        gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(rightHalf_scrolled_window), rightHalf);

        gtk_widget_set_size_request(rightHalf_scrolled_window, WINDOW_WIDTH / 2, 150);
        gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(rightHalf_scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
        gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(rightHalf_scrolled_window), rightHalf);
        gtk_grid_attach(GTK_GRID(baseGrid), rightHalf_scrolled_window, 1, 0, 1, 1);

        // set the left
        GtkWidget *leftHalf = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

        GtkWidget *yearlabel = gtk_label_new("Informasi per Tahun");
        gtk_box_append(GTK_BOX(leftHalf), yearlabel);
        gtk_grid_attach(GTK_GRID(baseGrid), leftHalf, 0, 0, 1, 1);

        for (int k = 0; k < penyakit; k++)
        {
            if (hasil[help].jumlah != 0)
            {
                snprintf(info, sizeof(info), "%s = %d", hasil[help].namaPenyakit, hasil[help].jumlah);
                GtkWidget *id_label = gtk_label_new(info);
                gtk_box_append(GTK_BOX(leftHalf), id_label);
            }
            help++;
        }
    }

    return page;
}

void integer_validation_penyakitperWaktuPage(GtkButton *button, gpointer user_data)
{
    GtkWidget *data = user_data;
    const char *input = gtk_editable_get_text(GTK_EDITABLE(data));
    char *endptr;
    //  strtol(input, &endptr, 10); // Convert input to integer
    int value = atoi(input);
    // printf("value: %d\n", value);
    GtkWidget *tempWidget = gtk_stack_get_child_by_name(GTK_STACK(penyakitperWaktuPage_Stack), "displayPenyakitPage");

    if (tempWidget != NULL)
    {
        gtk_stack_remove(GTK_STACK(penyakitperWaktuPage_Stack), tempWidget);
    }

    // if (*endptr == '\0')
    // {
    // Create the new page
    GtkWidget *displayPenyakitPage = DisplayPenyakitPage(value);
    gtk_stack_add_named(GTK_STACK(penyakitperWaktuPage_Stack), displayPenyakitPage, "displayPenyakitPage");

    // Get the window and replace its child with the new page
    gtk_stack_set_visible_child_name(GTK_STACK(penyakitperWaktuPage_Stack), "displayPenyakitPage");
    // }
    // else
    // {
    //     g_print("Invalid input, not an integer.\n");
    // }
}

void reset_penyakitperWaktuPage_Stack(GtkButton *button, gpointer user_data)
{
    GtkWidget *tempWidget = gtk_stack_get_child_by_name(GTK_STACK(penyakitperWaktuPage_Stack), "displayPenyakitPage");

    if (tempWidget != NULL)
    {
        gtk_stack_remove(GTK_STACK(penyakitperWaktuPage_Stack), tempWidget);
    }

    // back to landing page
    const char *page_name = user_data;
    gtk_stack_set_visible_child_name(GTK_STACK(stackContainer), page_name);
}

GtkWidget *addFooter_with_InformasiPasienPageStack_reset(GtkWidget *page)
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
    GtkWidget *page = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    GtkWidget *header = addHeader(page);

    penyakitperWaktuPage_Stack = gtk_stack_new();
    gtk_stack_set_transition_type(GTK_STACK(penyakitperWaktuPage_Stack), GTK_STACK_TRANSITION_TYPE_SLIDE_LEFT_RIGHT);

    GtkWidget *topLabel = gtk_label_new("Informasi Penyakit per Tahun");
    gtk_box_append(GTK_BOX(page), topLabel);
    gtk_widget_set_halign(topLabel, GTK_ALIGN_CENTER);
    // gtk_widget_set_size_request(topLabel, 100, 30);

    GtkWidget *cmdLabel = gtk_label_new("Masukkan Tahun ");
    gtk_box_append(GTK_BOX(page), cmdLabel);
    // gtk_widget_set_size_request(cmdLabel, 100, 30);

    GtkWidget *entry = gtk_entry_new();
    gtk_widget_set_size_request(entry, 200, 30);
    gtk_box_append(GTK_BOX(page), entry);

    GtkWidget *button = gtk_button_new_with_label("Cari");
    gtk_widget_set_size_request(button, 100, 30);
    gtk_box_append(GTK_BOX(page), button);

    gtk_box_append(GTK_BOX(page), penyakitperWaktuPage_Stack);
    gtk_widget_set_size_request(penyakitperWaktuPage_Stack, WINDOW_WIDTH, 420);

    // GtkWidget *mainGrid = gtk_grid_new();
    // gtk_stack_add_named(GTK_STACK(penyakitperWaktuPage_Stack), mainGrid, "MainGrid");

    // GtkWidget *mainContent = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    // gtk_grid_attach(GTK_GRID(mainGrid), mainContent, 0, 0, 1, 1);
    // gtk_widget_set_size_request(mainContent, WINDOW_WIDTH, 700);
    // gtk_widget_set_valign(mainContent, GTK_ALIGN_CENTER);

    g_signal_connect(button, "clicked", G_CALLBACK(integer_validation_penyakitperWaktuPage), entry);

    GtkWidget *footer = addFooter_with_InformasiPasienPageStack_reset(page);
    return page;
}