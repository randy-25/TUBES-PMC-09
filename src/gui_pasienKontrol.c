// #include "../header/gui_riwayatPasienPage.h"
// //ini salah

// GtkWidget *DisplayPasienKontrolPage(GtkButton *button, gpointer user_data)
// {

// }

// void on_find_clicked_pasienKontrolPage(GtkButton *button, gpointer user_data)


// // Base Page
// GtkWidget *PasienKontrolPage()
// {
//     GtkWidget *page = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
//     GtkWidget *header = addHeader(page);

//     pasienKontrolPage_Stack = gtk_stack_new();
//     gtk_stack_set_transition_type(GTK_STACK(pasienKontrolPage_Stack), GTK_STACK_TRANSITION_TYPE_SLIDE_LEFT_RIGHT);

//     gtk_box_append(GTK_BOX(page), pasienKontrolPage_Stack);

//     GtkWidget *mainContent = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
//     gtk_box_append(GTK_BOX(pasiienKontrolPage_Stack), mainContent);
//     gtk_widget_set_size_request(mainContent, WINDOW_WIDTH, WINDOW_HEIGHT - HEADER_HEIGHT - FOOTER_HEIGHT);
//     gtk_widget_set_valign(mainContent, GTK_ALIGN_CENTER);

//     // Center the mainContent
//     // gtk_grid_set_column_spacing(GTK_GRID(mainGrid_riwayatPasien), 0);
//     // gtk_grid_set_row_spacing(GTK_GRID(mainGrid_riwayatPasien), 0);
//     // gtk_grid_set_column_homogeneous(GTK_GRID(mainGrid_riwayatPasien), TRUE);
//     // gtk_grid_set_row_homogeneous(GTK_GRID(mainGrid_riwayatPasien), TRUE);

//     GtkWidget *topLabel = gtk_label_new("Informasi Penyakit per Tahun");
//     gtk_box_append(GTK_BOX(mainContent), topLabel);
//     gtk_widget_set_halign(topLabel, GTK_ALIGN_CENTER);

//     GtkWidget *cmdLabel = gtk_label_new("Masukkan Tahun (DD-MM-YYYY)");
//     GtkWidget *entry = gtk_entry_new();
//     gtk_box_append(GTK_BOX(page), cmdLabel);

//     gtk_widget_set_size_request(entry, 200, 30);
//     gtk_box_append(GTK_BOX(page), entry);

//     GtkWidget *button = gtk_button_new_with_label("Cari");
//     gtk_widget_set_size_request(button, 100, 30);
//     gtk_box_append(GTK_BOX(page), button);

//     GtkWidget *displayPasienKontrolPage = DisplayPasienKontrolPage();
//     gtk_stack_add_named(GTK_STACK(pasienKontrolPage_Stack), displayPasienKontrolPage, "DisplayPasienKontrolPage");
//     g_signal_connect(button, "clicked", G_CALLBACK(on_find_clicked_pasienKontrolPage), entry);

//     GtkWidget *footer = addFooter(page);
//     return page;
// }