#include "../header/gui_basePage.h"

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