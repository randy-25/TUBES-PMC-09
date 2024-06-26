#include "../header/gui_riwayatPasienPage.h"

// RIWAYAT PASIEN PAGE

// ------- CARI DATA RIWAYAT PASIEN PAGE -------
// Reset Cari Riwayat Pasien Page
void reset_cari_riwayatPasien_page()
{
    // Count the children
    GtkWidget *child = gtk_widget_get_first_child(GTK_WIDGET(riwayatPasienPage_cariRiwayat_pasienInfo));
    int child_count = 0;
    while (child != NULL)
    {
        child = gtk_widget_get_next_sibling(child);
        child_count++;
    }

    // Remove all but the last child
    child = gtk_widget_get_first_child(GTK_WIDGET(riwayatPasienPage_cariRiwayat_pasienInfo));
    for (int i = 0; i < child_count - 1; i++)
    {
        GtkWidget *next = gtk_widget_get_next_sibling(child);
        gtk_box_remove(GTK_BOX(riwayatPasienPage_cariRiwayat_pasienInfo), child);
        child = next;
    }
}

// Back to previous page button click
void on_back_cariRiwayatPasien_gui(GtkButton *button, gpointer user_data)
{
    reset_cari_riwayatPasien_page();
    DataCallBack *data = (DataCallBack *)user_data;
    gtk_stack_set_visible_child_name(GTK_STACK(data->stackContainer), data->page_name);
}

// Callback function to search patient data
void on_cari_riwayatPasien_data_gui(GtkButton *button, gpointer user_data)
{
    GtkWidget *data = user_data;
    const char *input_text = gtk_editable_get_text(GTK_EDITABLE(data)); // get the input text from the entry

    char *idPasien = strdup(input_text); // get the data from the entry
    // printf("Data: %s\n", idPasien);
    struct riwayat *dataHolder = NULL;
    int jumlahDataHolder = 0;
    int confirm;
    char *nameHolder;
    cariRiwayat(riwayatPasien, jumlahRiwayatPasien, idPasien, &dataHolder, &jumlahDataHolder, &confirm, &nameHolder, pasien, jumlahPasien); // search the data from the patient data

    // Clear the input box entry
    const gchar *default_text = "KX ";
    gtk_editable_set_text(GTK_EDITABLE(data), default_text);
    gtk_editable_set_position(GTK_EDITABLE(data), strlen(default_text));

    // Clear the existing content of the box
    GtkWidget *child = gtk_widget_get_first_child(GTK_WIDGET(riwayatPasienPage_cariRiwayat_pasienInfo));
    while (child != NULL)
    {
        GtkWidget *next = gtk_widget_get_next_sibling(child);
        gtk_box_remove(GTK_BOX(riwayatPasienPage_cariRiwayat_pasienInfo), child);
        child = next;
    }

    // Create a new GtkBox to hold the patient information
    GtkWidget *info_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    if (confirm == 1)
    {
        GtkWidget *name_label = gtk_label_new(nameHolder);
        gtk_box_append(GTK_BOX(info_box), name_label);
        for (int i = 0; i < jumlahDataHolder; i++)
        {
            struct riwayat *current = &dataHolder[i];

            char buffer[256];
            snprintf(buffer, sizeof(buffer), "No: %d\nTanggal Periksa: %d-%d-%d\nId Pasien: %s\nDiagnosis: %s\nTindakan: %s\nTanggal Kontrol: %d-%d-%d\nBiaya: %d",
                     current->no,
                     current->tanggalPeriksa.tanggal, current->tanggalPeriksa.bulan, current->tanggalPeriksa.tahun,
                     current->IdPasien,
                     current->diagnosis,
                     current->tindakan,
                     current->tanggalKontrol.tanggal, current->tanggalKontrol.bulan, current->tanggalKontrol.tahun,
                     current->biaya);

            GtkWidget *riwayat_label = gtk_label_new(buffer);
            gtk_box_append(GTK_BOX(info_box), riwayat_label);
            GtkWidget *label = gtk_label_new("-------------------------------------------------");
            gtk_box_append(GTK_BOX(info_box), label);
        }
    }
    else
    {
        GtkWidget *not_found_label = gtk_label_new("Data Pasien tidak ditemukan");
        gtk_box_append(GTK_BOX(info_box), not_found_label);
    }

    // Create a scrolled window and add the info_box to it
    GtkWidget *scrolled_window = gtk_scrolled_window_new();
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window), info_box);
    gtk_widget_set_size_request(scrolled_window, WINDOW_WIDTH, 300);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

    // Add the scrolled window to the main container
    gtk_box_append(GTK_BOX(riwayatPasienPage_cariRiwayat_pasienInfo), scrolled_window);

    GtkWidget *back_button = gtk_button_new_with_label("Back");
    gtk_widget_set_halign(back_button, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(riwayatPasienPage_cariRiwayat_pasienInfo), back_button);
    DataCallBack *callBack = g_malloc(sizeof(DataCallBack));
    callBack->stackContainer = riwayatPasienPage_Stack;
    callBack->page_name = "MainGridRiwayatPasien";
    g_signal_connect(back_button, "clicked", G_CALLBACK(on_back_cariRiwayatPasien_gui), callBack);

    g_free(idPasien);
}

GtkWidget *RiwayatPasienPage_CariData()
{
    GtkWidget *page;
    GtkWidget *entry;
    GtkWidget *button;

    page = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    entry = gtk_entry_new();
    GtkWidget *formLabel = gtk_label_new("Masukkan ID Pasien: ");
    gtk_box_append(GTK_BOX(page), formLabel);

    const gchar *default_text = "KX ";
    gtk_editable_set_text(GTK_EDITABLE(entry), default_text);
    gtk_editable_set_position(GTK_EDITABLE(entry), strlen(default_text));

    gtk_widget_set_size_request(entry, 200, 30);
    gtk_box_append(GTK_BOX(page), entry);

    button = gtk_button_new_with_label("Cari");
    gtk_widget_set_halign(button, GTK_ALIGN_CENTER);
    // gtk_widget_set_size_request(button, 100, 30);
    gtk_box_append(GTK_BOX(page), button);

    riwayatPasienPage_cariRiwayat_pasienInfo = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_append(GTK_BOX(page), riwayatPasienPage_cariRiwayat_pasienInfo);

    g_signal_connect(button, "clicked", G_CALLBACK(on_cari_riwayatPasien_data_gui), entry);

    GtkWidget *back_button = gtk_button_new_with_label("Back");
    gtk_widget_set_halign(back_button, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(riwayatPasienPage_cariRiwayat_pasienInfo), back_button);
    DataCallBack *callBack = g_malloc(sizeof(DataCallBack));
    callBack->stackContainer = riwayatPasienPage_Stack;
    callBack->page_name = "MainGridRiwayatPasien";
    g_signal_connect(back_button, "clicked", G_CALLBACK(on_back_cariRiwayatPasien_gui), callBack);

    return page;
}
// -------- END OF CARI DATA PASIEN PAGE --------

// ------- TAMBAH RIWAYAT PASIEN PAGE -------
void reset_tambahRiwayat_pasien_page()
{
    // Count the children
    GtkWidget *child = gtk_widget_get_first_child(GTK_WIDGET(riwayatPasienPage_tambahData_pasienInfo));
    int child_count = 0;
    while (child != NULL)
    {
        child = gtk_widget_get_next_sibling(child);
        child_count++;
    }

    // Remove all but the last child
    child = gtk_widget_get_first_child(GTK_WIDGET(riwayatPasienPage_tambahData_pasienInfo));
    for (int i = 0; i < child_count - 1; i++)
    {
        GtkWidget *next = gtk_widget_get_next_sibling(child);
        gtk_box_remove(GTK_BOX(riwayatPasienPage_tambahData_pasienInfo), child);
        child = next;
    }
}

void on_back_tambahRiwayatPasien_gui(GtkButton *button, gpointer user_data)
{
    reset_tambahRiwayat_pasien_page();
    DataCallBack *data = (DataCallBack *)user_data;
    gtk_stack_set_visible_child_name(GTK_STACK(data->stackContainer), data->page_name);
}

GtkWidget *ShowNewRiwayatDataPage(struct riwayat *new_riwayat, char *namaHolder, void callBackFunction(GtkButton *button, gpointer user_data))
{
    GtkWidget *page = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    // Title
    GtkWidget *title = gtk_label_new("Riwayat Pasien");
    gtk_widget_set_halign(title, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(page), title);

    // Display the new patient data
    char info[256];

    snprintf(info, sizeof(info), "ID Pasien: %s", new_riwayat->IdPasien);
    GtkWidget *IdPasien_label = gtk_label_new(info);
    gtk_box_append(GTK_BOX(page), IdPasien_label);

    snprintf(info, sizeof(info), "Nama: %s", namaHolder);
    GtkWidget *nama_label = gtk_label_new(info);
    gtk_box_append(GTK_BOX(page), nama_label);

    snprintf(info, sizeof(info), "Tanggal Periksa: %d-%d-%d", new_riwayat->tanggalPeriksa.tanggal, new_riwayat->tanggalPeriksa.bulan, new_riwayat->tanggalPeriksa.tahun);
    GtkWidget *tanggal_periksa_label = gtk_label_new(info);
    gtk_box_append(GTK_BOX(page), tanggal_periksa_label);

    snprintf(info, sizeof(info), "Diagnosis: %s", new_riwayat->diagnosis);
    GtkWidget *diagnosis_label = gtk_label_new(info);
    gtk_box_append(GTK_BOX(page), diagnosis_label);

    snprintf(info, sizeof(info), "Tindakan: %s", new_riwayat->tindakan);
    GtkWidget *tindakan_label = gtk_label_new(info);
    gtk_box_append(GTK_BOX(page), tindakan_label);

    snprintf(info, sizeof(info), "Tanggal Kontrol: %d-%d-%d", new_riwayat->tanggalKontrol.tanggal, new_riwayat->tanggalKontrol.bulan, new_riwayat->tanggalKontrol.tahun);
    GtkWidget *tanggal_kontrol_label = gtk_label_new(info);
    gtk_box_append(GTK_BOX(page), tanggal_kontrol_label);

    snprintf(info, sizeof(info), "Biaya: %d", new_riwayat->biaya);
    GtkWidget *biaya_label = gtk_label_new(info);
    gtk_box_append(GTK_BOX(page), biaya_label);

    // Add a button to go back to the landing page
    GtkWidget *back_button = gtk_button_new_with_label("Back");
    gtk_widget_set_halign(back_button, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(page), back_button);

    DataCallBack *callBack = g_malloc(sizeof(DataCallBack));
    callBack->stackContainer = riwayatPasienPage_Stack;
    callBack->page_name = "MainGridRiwayatPasien";
    g_signal_connect(back_button, "clicked", G_CALLBACK(callBackFunction), callBack);

    return page;
}

void on_submit_riwayat_pasien(GtkButton *button, gpointer user_data)
{
    RiwayatPasienEntry *entry = (RiwayatPasienEntry *)user_data;
    const gchar *IdPasien = gtk_editable_get_text(GTK_EDITABLE(entry->entry_id_pasien));
    const gchar *tanggal_periksa = gtk_editable_get_text(GTK_EDITABLE(entry->entry_tanggal_periksa));
    const gchar *diagnosis = gtk_editable_get_text(GTK_EDITABLE(entry->entry_diagnosis));
    const gchar *tindakan = gtk_editable_get_text(GTK_EDITABLE(entry->entry_tindakan));
    const gchar *tanggal_kontrol = gtk_editable_get_text(GTK_EDITABLE(entry->entry_tanggal_kontrol));

    char *tempIdPasien = strdup(IdPasien);
    char *temp_tanggal_periksa = strdup(tanggal_periksa);
    char *temp_diagnosis = strdup(diagnosis);
    char *temp_tindakan = strdup(tindakan);
    char *temp_tanggal_kontrol = strdup(tanggal_kontrol);

    // Clear the input box entry
    const gchar *default_text = "";
    gtk_editable_set_text(GTK_EDITABLE(entry->entry_id_pasien), default_text);
    gtk_editable_set_position(GTK_EDITABLE(entry->entry_id_pasien), strlen(default_text));

    gtk_editable_set_text(GTK_EDITABLE(entry->entry_tanggal_periksa), default_text);
    gtk_editable_set_position(GTK_EDITABLE(entry->entry_tanggal_periksa), strlen(default_text));

    gtk_editable_set_text(GTK_EDITABLE(entry->entry_diagnosis), default_text);
    gtk_editable_set_position(GTK_EDITABLE(entry->entry_diagnosis), strlen(default_text));

    gtk_editable_set_text(GTK_EDITABLE(entry->entry_tindakan), default_text);
    gtk_editable_set_position(GTK_EDITABLE(entry->entry_tindakan), strlen(default_text));

    gtk_editable_set_text(GTK_EDITABLE(entry->entry_tanggal_kontrol), default_text);
    gtk_editable_set_position(GTK_EDITABLE(entry->entry_tanggal_kontrol), strlen(default_text));

    struct riwayat newRiwayatHolder;
    char *namaHolder;
    int confirm;

    tambahRiwayat(&riwayatPasien, &jumlahRiwayatPasien, tempIdPasien, temp_tanggal_periksa, temp_diagnosis, temp_tindakan, temp_tanggal_kontrol, &newRiwayatHolder, &namaHolder, pasien, jumlahPasien, &confirm);

    if (confirm == 1)
    {

        // Create and show the new patient data page
        GtkWidget *newRiwayatPage;
        newRiwayatPage = ShowNewRiwayatDataPage(&newRiwayatHolder, namaHolder, on_back_tambahRiwayatPasien_gui);
        GtkWidget *tempWidget = gtk_stack_get_child_by_name(GTK_STACK(riwayatPasienPage_Stack), "NewRiwayatData");

        if (tempWidget != NULL)
        {
            gtk_stack_remove(GTK_STACK(riwayatPasienPage_Stack), tempWidget);
        }
        gtk_stack_add_named(GTK_STACK(riwayatPasienPage_Stack), newRiwayatPage, "NewRiwayatData");
        gtk_stack_set_visible_child(GTK_STACK(riwayatPasienPage_Stack), newRiwayatPage);
    }
    else
    {
        GtkWidget *newRiwayatPage = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
        GtkWidget *not_found_label = gtk_label_new("ID Pasien tidak ditemukan");
        gtk_box_append(GTK_BOX(newRiwayatPage), not_found_label);

        GtkWidget *tempWidget = gtk_stack_get_child_by_name(GTK_STACK(riwayatPasienPage_Stack), "NewRiwayatData");

        if (tempWidget != NULL)
        {
            gtk_stack_remove(GTK_STACK(riwayatPasienPage_Stack), tempWidget);
        }
        gtk_stack_add_named(GTK_STACK(riwayatPasienPage_Stack), newRiwayatPage, "NewRiwayatData");
        GtkWidget *back_button = gtk_button_new_with_label("Back");
        gtk_widget_set_halign(back_button, GTK_ALIGN_CENTER);
        gtk_box_append(GTK_BOX(newRiwayatPage), back_button);
        gtk_stack_set_visible_child(GTK_STACK(riwayatPasienPage_Stack), newRiwayatPage);

        DataCallBack *callBack = g_malloc(sizeof(DataCallBack));
        callBack->stackContainer = riwayatPasienPage_Stack;
        callBack->page_name = "MainGridRiwayatPasien";
        g_signal_connect(back_button, "clicked", G_CALLBACK(on_back_cariRiwayatPasien_gui), callBack);
    }
}

GtkWidget *RiwayatPasienPage_TambahData()
{
    riwayatPasienPage_tambahData_pasienInfo = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    GtkWidget *page = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    GtkWidget *entry_IdPasien;
    GtkWidget *entry_tanggalPeriksa;
    GtkWidget *entry_diagnosis;
    GtkWidget *entry_tindakan;
    GtkWidget *entry_tanggalKontrol;

    GtkWidget *title = gtk_label_new("Tambah Riwayat Pasien");
    gtk_widget_set_halign(title, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(page), title);

    GtkWidget *formGrid = gtk_grid_new();
    gtk_grid_set_column_homogeneous(GTK_GRID(formGrid), TRUE);
    gtk_grid_set_row_homogeneous(GTK_GRID(formGrid), TRUE);
    gtk_grid_set_row_spacing(GTK_GRID(formGrid), 10);
    gtk_widget_set_halign(formGrid, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(page), formGrid);

    // ID Pasien
    GtkWidget *label_IdPasien = gtk_label_new("ID Pasien: ");
    entry_IdPasien = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(formGrid), label_IdPasien, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(formGrid), entry_IdPasien, 1, 0, 1, 1);

    const gchar *default_text = "KX ";
    gtk_editable_set_text(GTK_EDITABLE(entry_IdPasien), default_text);
    gtk_editable_set_position(GTK_EDITABLE(entry_IdPasien), strlen(default_text));
    // Tanggal Periksa
    GtkWidget *label_tanggalPeriksa = gtk_label_new("Tanggal Periksa (DD-MM-YYYY): ");
    entry_tanggalPeriksa = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(formGrid), label_tanggalPeriksa, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(formGrid), entry_tanggalPeriksa, 1, 1, 1, 1);

    // Kota
    GtkWidget *label_diagnosis = gtk_label_new("Diagnosis:");
    entry_diagnosis = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(formGrid), label_diagnosis, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(formGrid), entry_diagnosis, 1, 2, 1, 1);

    // Tempat Lahir
    GtkWidget *label_tindakan = gtk_label_new("Tindakan:");
    entry_tindakan = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(formGrid), label_tindakan, 0, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(formGrid), entry_tindakan, 1, 3, 1, 1);

    // Tanggal Lahir
    GtkWidget *label_tanggalKontrol = gtk_label_new("Tanggal Kontrol (DD-MM-YYYY):");
    entry_tanggalKontrol = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(formGrid), label_tanggalKontrol, 0, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(formGrid), entry_tanggalKontrol, 1, 4, 1, 1);

    // Submit Button
    GtkWidget *submit_button = gtk_button_new_with_label("Submit");
    gtk_widget_set_halign(submit_button, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(page), submit_button);

    RiwayatPasienEntry *entry_data = g_malloc(sizeof(RiwayatPasienEntry));
    entry_data->entry_id_pasien = entry_IdPasien;
    entry_data->entry_tanggal_periksa = entry_tanggalPeriksa;
    entry_data->entry_diagnosis = entry_diagnosis;
    entry_data->entry_tindakan = entry_tindakan;
    entry_data->entry_tanggal_kontrol = entry_tanggalKontrol;

    g_signal_connect(submit_button, "clicked", G_CALLBACK(on_submit_riwayat_pasien), entry_data);

    GtkWidget *back_button = gtk_button_new_with_label("Back");
    gtk_widget_set_halign(back_button, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(page), back_button);

    DataCallBack *callBack = g_malloc(sizeof(DataCallBack));
    callBack->stackContainer = riwayatPasienPage_Stack;
    callBack->page_name = "MainGridRiwayatPasien";
    g_signal_connect(back_button, "clicked", G_CALLBACK(on_back_tambahRiwayatPasien_gui), callBack);
    return page;
}
// -------- END OF TAMBAH RIWAYAT PASIEN PAGE --------

// -------- UBAH RIWAYAT PASIEN PAGE --------
void reset_ubahRiwayat_pasien_page()
{
    // Count the children
    GtkWidget *child = gtk_widget_get_first_child(GTK_WIDGET(riwayatPasienPage_ubahData_pasienInfo));
    int child_count = 0;
    while (child != NULL)
    {
        child = gtk_widget_get_next_sibling(child);
        child_count++;
    }

    // Remove all but the last child
    child = gtk_widget_get_first_child(GTK_WIDGET(riwayatPasienPage_ubahData_pasienInfo));
    for (int i = 0; i < child_count - 1; i++)
    {
        GtkWidget *next = gtk_widget_get_next_sibling(child);
        gtk_box_remove(GTK_BOX(riwayatPasienPage_ubahData_pasienInfo), child);
        child = next;
    }
}

// Back to previous page button click
void on_back_ubahRiwayatPasien_gui(GtkButton *button, gpointer user_data)
{
    reset_ubahRiwayat_pasien_page();
    DataCallBack *data = (DataCallBack *)user_data;
    gtk_stack_set_visible_child_name(GTK_STACK(data->stackContainer), data->page_name);
}

void on_submit_ubahRiwayat_pasien_page(GtkButton *button, gpointer user_data)
{
    RiwayatPasienEntry *entry = (RiwayatPasienEntry *)user_data;
    const gchar *tanggal_periksa = gtk_editable_get_text(GTK_EDITABLE(entry->entry_tanggal_periksa));
    const gchar *diagnosis = gtk_editable_get_text(GTK_EDITABLE(entry->entry_diagnosis));
    const gchar *tindakan = gtk_editable_get_text(GTK_EDITABLE(entry->entry_tindakan));
    const gchar *tanggal_kontrol = gtk_editable_get_text(GTK_EDITABLE(entry->entry_tanggal_kontrol));

    char *temp_tanggal_periksa = strdup(tanggal_periksa);
    char *temp_diagnosis = strdup(diagnosis);
    char *temp_tindakan = strdup(tindakan);
    char *temp_tanggal_kontrol = strdup(tanggal_kontrol);

    // Clear the input box entry
    const gchar *default_text = "";
    gtk_editable_set_text(GTK_EDITABLE(entry->entry_tanggal_periksa), default_text);
    gtk_editable_set_position(GTK_EDITABLE(entry->entry_tanggal_periksa), strlen(default_text));

    gtk_editable_set_text(GTK_EDITABLE(entry->entry_diagnosis), default_text);
    gtk_editable_set_position(GTK_EDITABLE(entry->entry_diagnosis), strlen(default_text));

    gtk_editable_set_text(GTK_EDITABLE(entry->entry_tindakan), default_text);
    gtk_editable_set_position(GTK_EDITABLE(entry->entry_tindakan), strlen(default_text));

    gtk_editable_set_text(GTK_EDITABLE(entry->entry_tanggal_kontrol), default_text);
    gtk_editable_set_position(GTK_EDITABLE(entry->entry_tanggal_kontrol), strlen(default_text));

    struct riwayat newRiwayatHolder;
    char *namaHolder;
    int confirm;

    ubahRiwayat(&riwayatPasien, jumlahRiwayatPasien, entry->nomorRiwayat, temp_tanggal_periksa, temp_diagnosis, temp_tindakan, temp_tanggal_kontrol, &newRiwayatHolder, &namaHolder, pasien, jumlahPasien);

    GtkWidget *newRiwayatPage;
    newRiwayatPage = ShowNewRiwayatDataPage(&newRiwayatHolder, namaHolder, on_back_ubahRiwayatPasien_gui);
    GtkWidget *tempWidget = gtk_stack_get_child_by_name(GTK_STACK(riwayatPasienPage_Stack), "NewUbahRiwayatData");

    if (tempWidget != NULL)
    {
        gtk_stack_remove(GTK_STACK(riwayatPasienPage_Stack), tempWidget);
    }
    gtk_stack_add_named(GTK_STACK(riwayatPasienPage_Stack), newRiwayatPage, "NewUbahRiwayatData");
    gtk_stack_set_visible_child(GTK_STACK(riwayatPasienPage_Stack), newRiwayatPage);

    g_free(temp_tanggal_periksa);
    g_free(temp_diagnosis);
    g_free(temp_tindakan);
    g_free(temp_tanggal_kontrol);
}

GtkWidget *ubahRiwayat_form_page(int nomorRiwayat)
{
    GtkWidget *page = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    // printf("Nomor Riwayat: %d\n", nomorRiwayat);
    GtkWidget *entry_tanggal_periksa;
    GtkWidget *entry_diagnosis;
    GtkWidget *entry_tindakan;
    GtkWidget *entry_tanggal_kontrol;

    GtkWidget *title = gtk_label_new("Ubah Data Pasien");
    gtk_widget_set_halign(title, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(page), title);

    GtkWidget *formGrid = gtk_grid_new();
    gtk_grid_set_column_homogeneous(GTK_GRID(formGrid), TRUE);
    gtk_grid_set_row_homogeneous(GTK_GRID(formGrid), TRUE);
    gtk_grid_set_row_spacing(GTK_GRID(formGrid), 10);
    gtk_widget_set_halign(formGrid, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(page), formGrid);

    // Tanggal Periksa
    GtkWidget *label_tanggal_periksa = gtk_label_new("Tanggal Periksa (DD-MM-YYYY): ");
    entry_tanggal_periksa = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(formGrid), label_tanggal_periksa, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(formGrid), entry_tanggal_periksa, 1, 0, 1, 1);

    // Diagnosis
    GtkWidget *label_diagnosis = gtk_label_new("Diagnosis: ");
    entry_diagnosis = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(formGrid), label_diagnosis, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(formGrid), entry_diagnosis, 1, 1, 1, 1);

    // Tindakan
    GtkWidget *label_tindakan = gtk_label_new("Tindakan:");
    entry_tindakan = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(formGrid), label_tindakan, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(formGrid), entry_tindakan, 1, 2, 1, 1);

    // Tanggal Kontrol
    GtkWidget *label_tanggal_kontrol = gtk_label_new("Tanggal Kontrol:");
    entry_tanggal_kontrol = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(formGrid), label_tanggal_kontrol, 0, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(formGrid), entry_tanggal_kontrol, 1, 3, 1, 1);

    // Submit Button
    GtkWidget *submit_button = gtk_button_new_with_label("Submit");
    gtk_widget_set_halign(submit_button, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(page), submit_button);

    // Wrap the data into a struct
    RiwayatPasienEntry *entry_data = g_malloc(sizeof(RiwayatPasienEntry));
    entry_data->entry_tanggal_periksa = entry_tanggal_periksa;
    entry_data->entry_diagnosis = entry_diagnosis;
    entry_data->entry_tindakan = entry_tindakan;
    entry_data->entry_tanggal_kontrol = entry_tanggal_kontrol;
    entry_data->nomorRiwayat = nomorRiwayat;

    g_signal_connect(submit_button, "clicked", G_CALLBACK(on_submit_ubahRiwayat_pasien_page), entry_data);

    GtkWidget *back_button = gtk_button_new_with_label("Back");
    gtk_widget_set_halign(back_button, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(page), back_button);

    DataCallBack *callBack = g_malloc(sizeof(DataCallBack));
    callBack->stackContainer = dataPasienPage_Stack;
    callBack->page_name = "MainGridRiwayatPasien";
    g_signal_connect(back_button, "clicked", G_CALLBACK(on_back_ubahRiwayatPasien_gui), callBack);
    return page;
}

void on_ubah_riwayatPasien_gui(GtkButton *button, gpointer user_data)
{
    RiwayatPasienEntry *entry_data = (RiwayatPasienEntry *)user_data;

    const char *tempUbahNomorRiwayat = gtk_editable_get_text(GTK_EDITABLE(entry_data->entry_nomor_riwayat));

    int no_ubah = atoi(tempUbahNomorRiwayat);
    char *idPasien = strdup(entry_data->id_pasien);

    int confirm = cekNomorRiwayat(no_ubah, idPasien, riwayatPasien);
    // printf("confirm %d\n", confirm);
    if (confirm == 1)
    {
        GtkWidget *formUbahRiwayatPage = ubahRiwayat_form_page(no_ubah);

        GtkWidget *tempWidget = gtk_stack_get_child_by_name(GTK_STACK(riwayatPasienPage_Stack), "UbahRiwayatData");

        if (tempWidget != NULL)
        {
            gtk_stack_remove(GTK_STACK(riwayatPasienPage_Stack), tempWidget);
        }

        gtk_stack_add_named(GTK_STACK(riwayatPasienPage_Stack), formUbahRiwayatPage, "UbahRiwayatData");
        gtk_stack_set_visible_child(GTK_STACK(riwayatPasienPage_Stack), formUbahRiwayatPage);
    }
    else
    {
        GtkWidget *formUbahRiwayatPage = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
        GtkWidget *not_found_label = gtk_label_new("Data Pasien tidak ditemukan");
        gtk_box_append(GTK_BOX(formUbahRiwayatPage), not_found_label);

        GtkWidget *tempWidget = gtk_stack_get_child_by_name(GTK_STACK(riwayatPasienPage_Stack), "UbahRiwayatData");

        if (tempWidget != NULL)
        {
            gtk_stack_remove(GTK_STACK(riwayatPasienPage_Stack), tempWidget);
        }
        gtk_stack_add_named(GTK_STACK(riwayatPasienPage_Stack), formUbahRiwayatPage, "UbahRiwayatData");
        gtk_stack_set_visible_child(GTK_STACK(riwayatPasienPage_Stack), formUbahRiwayatPage);
        GtkWidget *back_button = gtk_button_new_with_label("Back");
        gtk_widget_set_halign(back_button, GTK_ALIGN_CENTER);
        gtk_box_append(GTK_BOX(formUbahRiwayatPage), back_button);
        DataCallBack *callBack = g_malloc(sizeof(DataCallBack));
        callBack->stackContainer = riwayatPasienPage_Stack;
        callBack->page_name = "MainGridRiwayatPasien";
        g_signal_connect(back_button, "clicked", G_CALLBACK(on_back_ubahRiwayatPasien_gui), callBack);
    }
}

void on_cari_riwayatPasien_ubahData_gui(GtkButton *button, gpointer user_data)
{
    GtkWidget *data = user_data;
    const char *input_text = gtk_editable_get_text(GTK_EDITABLE(data)); // get the input text from the entry

    char *idPasien = strdup(input_text); // get the data from the entry
    // printf("Data: %s\n", idPasien);
    struct riwayat *dataHolder = NULL;
    int jumlahDataHolder = 0;
    int confirm;
    char *nameHolder;
    cariRiwayat(riwayatPasien, jumlahRiwayatPasien, idPasien, &dataHolder, &jumlahDataHolder, &confirm, &nameHolder, pasien, jumlahPasien); // search the data from the patient data

    // Clear the input box entry
    const gchar *default_text = "KX ";
    gtk_editable_set_text(GTK_EDITABLE(data), default_text);
    gtk_editable_set_position(GTK_EDITABLE(data), strlen(default_text));

    // Clear the existing content of the box
    GtkWidget *child = gtk_widget_get_first_child(GTK_WIDGET(riwayatPasienPage_ubahData_pasienInfo));
    while (child != NULL)
    {
        GtkWidget *next = gtk_widget_get_next_sibling(child);
        gtk_box_remove(GTK_BOX(riwayatPasienPage_ubahData_pasienInfo), child);
        child = next;
    }

    // Create a new GtkBox to hold the patient information
    GtkWidget *info_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    if (confirm == 1)
    {
        GtkWidget *name_label = gtk_label_new(nameHolder);
        gtk_box_append(GTK_BOX(info_box), name_label);
        for (int i = 0; i < jumlahDataHolder; i++)
        {
            struct riwayat *current = &dataHolder[i];

            char buffer[256];
            snprintf(buffer, sizeof(buffer), "No: %d\nTanggal Periksa: %d-%d-%d\nId Pasien: %s\nDiagnosis: %s\nTindakan: %s\nTanggal Kontrol: %d-%d-%d\nBiaya: %d",
                     current->no,
                     current->tanggalPeriksa.tanggal, current->tanggalPeriksa.bulan, current->tanggalPeriksa.tahun,
                     current->IdPasien,
                     current->diagnosis,
                     current->tindakan,
                     current->tanggalKontrol.tanggal, current->tanggalKontrol.bulan, current->tanggalKontrol.tahun,
                     current->biaya);

            GtkWidget *riwayat_label = gtk_label_new(buffer);
            gtk_box_append(GTK_BOX(info_box), riwayat_label);
            GtkWidget *label = gtk_label_new("-------------------------------------------------");
            gtk_box_append(GTK_BOX(info_box), label);
        }
    }
    else
    {
        GtkWidget *not_found_label = gtk_label_new("Data Pasien tidak ditemukan");
        gtk_box_append(GTK_BOX(info_box), not_found_label);
    }

    // Create a scrolled window and add the info_box to it
    GtkWidget *scrolled_window = gtk_scrolled_window_new();
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window), info_box);
    gtk_widget_set_size_request(scrolled_window, WINDOW_WIDTH, 300);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

    // Add the scrolled window to the main container
    gtk_box_append(GTK_BOX(riwayatPasienPage_ubahData_pasienInfo), scrolled_window);

    if (confirm == 1)
    {
        GtkWidget *entry_ubah_no = gtk_entry_new();
        GtkWidget *formLabel = gtk_label_new("Masukkan No Riwayat Yang Ingin Diubah: ");
        gtk_box_append(GTK_BOX(riwayatPasienPage_ubahData_pasienInfo), formLabel);
        gtk_box_append(GTK_BOX(riwayatPasienPage_ubahData_pasienInfo), entry_ubah_no);

        RiwayatPasienEntry *entry_data = g_malloc(sizeof(RiwayatPasienEntry));
        entry_data->id_pasien = strdup(idPasien);
        entry_data->entry_nomor_riwayat = entry_ubah_no;

        GtkWidget *ubah_button = gtk_button_new_with_label("Ubah");
        gtk_widget_set_halign(ubah_button, GTK_ALIGN_CENTER);
        gtk_box_append(GTK_BOX(riwayatPasienPage_ubahData_pasienInfo), ubah_button);

        g_signal_connect(ubah_button, "clicked", G_CALLBACK(on_ubah_riwayatPasien_gui), entry_data);
    }

    GtkWidget *back_button = gtk_button_new_with_label("Back");
    gtk_widget_set_halign(back_button, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(riwayatPasienPage_ubahData_pasienInfo), back_button);
    DataCallBack *callBack = g_malloc(sizeof(DataCallBack));
    callBack->stackContainer = riwayatPasienPage_Stack;
    callBack->page_name = "MainGridRiwayatPasien";
    g_signal_connect(back_button, "clicked", G_CALLBACK(on_back_ubahRiwayatPasien_gui), callBack);

    g_free(idPasien);
}

GtkWidget *RiwayatPasienPage_UbahData()
{
    GtkWidget *page;
    GtkWidget *entry;
    GtkWidget *button;

    page = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    entry = gtk_entry_new();
    GtkWidget *formLabel = gtk_label_new("Masukkan ID Pasien: ");
    gtk_box_append(GTK_BOX(page), formLabel);

    const gchar *default_text = "KX ";
    gtk_editable_set_text(GTK_EDITABLE(entry), default_text);
    gtk_editable_set_position(GTK_EDITABLE(entry), strlen(default_text));

    gtk_widget_set_size_request(entry, 200, 30);
    gtk_box_append(GTK_BOX(page), entry);

    button = gtk_button_new_with_label("Cari");
    gtk_widget_set_halign(button, GTK_ALIGN_CENTER);
    // gtk_widget_set_size_request(button, 100, 30);
    gtk_box_append(GTK_BOX(page), button);

    riwayatPasienPage_ubahData_pasienInfo = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_append(GTK_BOX(page), riwayatPasienPage_ubahData_pasienInfo);

    g_signal_connect(button, "clicked", G_CALLBACK(on_cari_riwayatPasien_ubahData_gui), entry);

    GtkWidget *back_button = gtk_button_new_with_label("Back");
    gtk_widget_set_halign(back_button, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(riwayatPasienPage_ubahData_pasienInfo), back_button);
    DataCallBack *callBack = g_malloc(sizeof(DataCallBack));
    callBack->stackContainer = riwayatPasienPage_Stack;
    callBack->page_name = "MainGridRiwayatPasien";
    g_signal_connect(back_button, "clicked", G_CALLBACK(on_button_clicked_with_page), callBack);

    return page;
}
// -------- END OF UBAH RIWAYAT PASIEN PAGE --------

// -------- HAPUS RIWAYAT PASIEN PAGE --------
void reset_hapusRiwayat_pasien_page()
{
    // Count the children
    GtkWidget *child = gtk_widget_get_first_child(GTK_WIDGET(riwayatPasienPage_hapusData_pasienInfo));
    int child_count = 0;
    while (child != NULL)
    {
        child = gtk_widget_get_next_sibling(child);
        child_count++;
    }

    // Remove all but the last child
    child = gtk_widget_get_first_child(GTK_WIDGET(riwayatPasienPage_hapusData_pasienInfo));
    for (int i = 0; i < child_count - 1; i++)
    {
        GtkWidget *next = gtk_widget_get_next_sibling(child);
        gtk_box_remove(GTK_BOX(riwayatPasienPage_hapusData_pasienInfo), child);
        child = next;
    }
}

// Back to previous page button click
void on_back_hapusRiwayatPasien_gui(GtkButton *button, gpointer user_data)
{
    reset_hapusRiwayat_pasien_page();
    DataCallBack *data = (DataCallBack *)user_data;
    gtk_stack_set_visible_child_name(GTK_STACK(data->stackContainer), data->page_name);
}

void on_hapus_riwayatPasien_gui(GtkButton *button, gpointer user_data)
{
    RiwayatPasienEntry *entry_data = (RiwayatPasienEntry *)user_data;

    const char *tempUbahNomorRiwayat = gtk_editable_get_text(GTK_EDITABLE(entry_data->entry_nomor_riwayat));

    int no_hapus = atoi(tempUbahNomorRiwayat);
    char *idPasien = strdup(entry_data->id_pasien);

    int confirm = cekNomorRiwayat(no_hapus, idPasien, riwayatPasien);
    GtkWidget *hapusRiwayatPage;
    if (confirm == 1)
    {
        hapusRiwayat(&riwayatPasien, &jumlahRiwayatPasien, no_hapus);

        hapusRiwayatPage = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
        GtkWidget *hapus_label = gtk_label_new("Data Pasien berhasil dihapus");
        gtk_box_append(GTK_BOX(hapusRiwayatPage), hapus_label);
    }
    else
    {
        hapusRiwayatPage = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
        GtkWidget *not_found_label = gtk_label_new("Data Pasien tidak ditemukan");
        gtk_box_append(GTK_BOX(hapusRiwayatPage), not_found_label);
    }
    GtkWidget *tempWidget = gtk_stack_get_child_by_name(GTK_STACK(riwayatPasienPage_Stack), "HapusRiwayatData");

    if (tempWidget != NULL)
    {
        gtk_stack_remove(GTK_STACK(riwayatPasienPage_Stack), tempWidget);
    }
    gtk_stack_add_named(GTK_STACK(riwayatPasienPage_Stack), hapusRiwayatPage, "HapusRiwayatData");
    gtk_stack_set_visible_child(GTK_STACK(riwayatPasienPage_Stack), hapusRiwayatPage);
    GtkWidget *back_button = gtk_button_new_with_label("Back");
    gtk_widget_set_halign(back_button, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(hapusRiwayatPage), back_button);
    DataCallBack *callBack = g_malloc(sizeof(DataCallBack));
    callBack->stackContainer = riwayatPasienPage_Stack;
    callBack->page_name = "MainGridRiwayatPasien";
    g_signal_connect(back_button, "clicked", G_CALLBACK(on_back_hapusRiwayatPasien_gui), callBack);
}

void on_cari_riwayatPasien_hapusData_gui(GtkButton *button, gpointer user_data)
{
    GtkWidget *data = user_data;
    const char *input_text = gtk_editable_get_text(GTK_EDITABLE(data)); // get the input text from the entry

    char *idPasien = strdup(input_text); // get the data from the entry
    struct riwayat *dataHolder = NULL;
    int jumlahDataHolder = 0;
    int confirm;
    char *nameHolder;
    cariRiwayat(riwayatPasien, jumlahRiwayatPasien, idPasien, &dataHolder, &jumlahDataHolder, &confirm, &nameHolder, pasien, jumlahPasien); // search the data from the patient data

    // Clear the input box entry
    const gchar *default_text = "KX ";
    gtk_editable_set_text(GTK_EDITABLE(data), default_text);
    gtk_editable_set_position(GTK_EDITABLE(data), strlen(default_text));

    // Clear the existing content of the box
    GtkWidget *child = gtk_widget_get_first_child(GTK_WIDGET(riwayatPasienPage_hapusData_pasienInfo));
    while (child != NULL)
    {
        GtkWidget *next = gtk_widget_get_next_sibling(child);
        gtk_box_remove(GTK_BOX(riwayatPasienPage_hapusData_pasienInfo), child);
        child = next;
    }

    // Create a new GtkBox to hold the patient information
    GtkWidget *info_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    if (confirm == 1)
    {
        GtkWidget *name_label = gtk_label_new(nameHolder);
        gtk_box_append(GTK_BOX(info_box), name_label);
        for (int i = 0; i < jumlahDataHolder; i++)
        {
            struct riwayat *current = &dataHolder[i];

            char buffer[256];
            snprintf(buffer, sizeof(buffer), "No: %d\nTanggal Periksa: %d-%d-%d\nId Pasien: %s\nDiagnosis: %s\nTindakan: %s\nTanggal Kontrol: %d-%d-%d\nBiaya: %d",
                     current->no,
                     current->tanggalPeriksa.tanggal, current->tanggalPeriksa.bulan, current->tanggalPeriksa.tahun,
                     current->IdPasien,
                     current->diagnosis,
                     current->tindakan,
                     current->tanggalKontrol.tanggal, current->tanggalKontrol.bulan, current->tanggalKontrol.tahun,
                     current->biaya);

            GtkWidget *riwayat_label = gtk_label_new(buffer);
            gtk_box_append(GTK_BOX(info_box), riwayat_label);
            GtkWidget *label = gtk_label_new("-------------------------------------------------");
            gtk_box_append(GTK_BOX(info_box), label);
        }
    }
    else
    {
        GtkWidget *not_found_label = gtk_label_new("Data Pasien tidak ditemukan");
        gtk_box_append(GTK_BOX(info_box), not_found_label);
    }

    // Create a scrolled window and add the info_box to it
    GtkWidget *scrolled_window = gtk_scrolled_window_new();
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window), info_box);
    gtk_widget_set_size_request(scrolled_window, WINDOW_WIDTH, 300);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

    // Add the scrolled window to the main container
    gtk_box_append(GTK_BOX(riwayatPasienPage_hapusData_pasienInfo), scrolled_window);

    if (confirm == 1)
    {
        GtkWidget *entry_hapus_no = gtk_entry_new();
        GtkWidget *formLabel = gtk_label_new("Masukkan No Riwayat Yang Ingin Dihapus: ");
        gtk_box_append(GTK_BOX(riwayatPasienPage_hapusData_pasienInfo), formLabel);
        gtk_box_append(GTK_BOX(riwayatPasienPage_hapusData_pasienInfo), entry_hapus_no);

        RiwayatPasienEntry *entry_data = g_malloc(sizeof(RiwayatPasienEntry));
        entry_data->id_pasien = strdup(idPasien);
        entry_data->entry_nomor_riwayat = entry_hapus_no;

        GtkWidget *ubah_button = gtk_button_new_with_label("Hapus");
        gtk_widget_set_halign(ubah_button, GTK_ALIGN_CENTER);
        gtk_box_append(GTK_BOX(riwayatPasienPage_hapusData_pasienInfo), ubah_button);

        g_signal_connect(ubah_button, "clicked", G_CALLBACK(on_hapus_riwayatPasien_gui), entry_data);
    }

    GtkWidget *back_button = gtk_button_new_with_label("Back");
    gtk_widget_set_halign(back_button, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(riwayatPasienPage_hapusData_pasienInfo), back_button);
    DataCallBack *callBack = g_malloc(sizeof(DataCallBack));
    callBack->stackContainer = riwayatPasienPage_Stack;
    callBack->page_name = "MainGridRiwayatPasien";
    g_signal_connect(back_button, "clicked", G_CALLBACK(on_back_hapusRiwayatPasien_gui), callBack);

    g_free(idPasien);
}

GtkWidget *RiwayatPasienPage_HapusData()
{
    GtkWidget *page;
    GtkWidget *entry;
    GtkWidget *button;

    page = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    entry = gtk_entry_new();
    GtkWidget *formLabel = gtk_label_new("Masukkan ID Pasien: ");
    gtk_box_append(GTK_BOX(page), formLabel);

    const gchar *default_text = "KX ";
    gtk_editable_set_text(GTK_EDITABLE(entry), default_text);
    gtk_editable_set_position(GTK_EDITABLE(entry), strlen(default_text));

    gtk_widget_set_size_request(entry, 200, 30);
    gtk_box_append(GTK_BOX(page), entry);

    button = gtk_button_new_with_label("Cari");
    gtk_widget_set_halign(button, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(page), button);

    riwayatPasienPage_hapusData_pasienInfo = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_append(GTK_BOX(page), riwayatPasienPage_hapusData_pasienInfo);

    g_signal_connect(button, "clicked", G_CALLBACK(on_cari_riwayatPasien_hapusData_gui), entry);

    GtkWidget *back_button = gtk_button_new_with_label("Back");
    gtk_widget_set_halign(back_button, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(riwayatPasienPage_hapusData_pasienInfo), back_button);
    DataCallBack *callBack = g_malloc(sizeof(DataCallBack));
    callBack->stackContainer = riwayatPasienPage_Stack;
    callBack->page_name = "MainGridRiwayatPasien";
    g_signal_connect(back_button, "clicked", G_CALLBACK(on_button_clicked_with_page), callBack);

    return page;
}

// -------- END OF HAPUS RIWAYAT PASIEN PAGE --------

// Base Page
GtkWidget *RiwayatPasienPage()
{
    GtkWidget *page = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    GtkWidget *header = addHeader(page);

    riwayatPasienPage_Stack = gtk_stack_new();
    gtk_stack_set_transition_type(GTK_STACK(riwayatPasienPage_Stack), GTK_STACK_TRANSITION_TYPE_SLIDE_LEFT_RIGHT);

    gtk_box_append(GTK_BOX(page), riwayatPasienPage_Stack);

    GtkWidget *mainGrid_riwayatPasien = gtk_grid_new();
    gtk_stack_add_named(GTK_STACK(riwayatPasienPage_Stack), mainGrid_riwayatPasien, "MainGridRiwayatPasien");
    // g_print("Added CariRiwayatPasien to stack\n");

    GtkWidget *mainContent = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_grid_attach(GTK_GRID(mainGrid_riwayatPasien), mainContent, 1, 1, 1, 1);
    gtk_widget_set_size_request(mainContent, WINDOW_WIDTH, WINDOW_HEIGHT - HEADER_HEIGHT - FOOTER_HEIGHT);
    gtk_widget_set_valign(mainContent, GTK_ALIGN_CENTER);

    GtkWidget *baseGrid = gtk_grid_new();
    gtk_widget_set_size_request(baseGrid, WINDOW_WIDTH, -1);
    gtk_widget_set_vexpand(baseGrid, TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(baseGrid), TRUE);
    gtk_grid_set_row_homogeneous(GTK_GRID(baseGrid), TRUE);
    gtk_box_append(GTK_BOX(mainContent), baseGrid);

    GtkWidget *leftHalf = gtk_center_box_new();
    GtkWidget *leftLabel = gtk_label_new("Riwayat Pasien");
    gtk_center_box_set_center_widget(GTK_CENTER_BOX(leftHalf), leftLabel);
    gtk_widget_set_valign(leftLabel, GTK_ALIGN_CENTER);

    GtkWidget *rightHalf = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    GtkWidget *rightHalfButton = gtk_grid_new();
    gtk_grid_set_column_homogeneous(GTK_GRID(rightHalfButton), TRUE);
    gtk_grid_set_row_homogeneous(GTK_GRID(rightHalfButton), TRUE);
    gtk_grid_set_row_spacing(GTK_GRID(rightHalfButton), 10);
    gtk_box_append(GTK_BOX(rightHalf), rightHalfButton);
    gtk_widget_set_halign(rightHalf, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(rightHalf, GTK_ALIGN_CENTER);

    GtkWidget *funcButton[4];
    char *button_labels[4] = {"Cari Riwayat Pasien", "Tambah Riwayat Pasien", "Ubah Riwayat Pasien", "Hapus Riwayat Pasien"};
    char *page_names[4] = {"CariRiwayatPasien", "TambahRiwayatPasien", "UbahRiwayatPasien", "HapusRiwayatPasien"};

    for (int i = 0; i < 4; i++)
    {
        funcButton[i] = gtk_button_new_with_label(button_labels[i]);
        gtk_grid_attach(GTK_GRID(rightHalfButton), funcButton[i], 0, i, 1, 1);
        gtk_widget_set_size_request(funcButton[i], 150, 50);
    }

    gtk_grid_attach(GTK_GRID(baseGrid), leftHalf, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(baseGrid), rightHalf, 1, 0, 1, 1);

    // Center the mainContent
    gtk_grid_set_column_spacing(GTK_GRID(mainGrid_riwayatPasien), 0);
    gtk_grid_set_row_spacing(GTK_GRID(mainGrid_riwayatPasien), 0);
    gtk_grid_set_column_homogeneous(GTK_GRID(mainGrid_riwayatPasien), TRUE);
    gtk_grid_set_row_homogeneous(GTK_GRID(mainGrid_riwayatPasien), TRUE);

    // Cari Data Page
    GtkWidget *riwayatPasienPage_CariData = RiwayatPasienPage_CariData();
    gtk_stack_add_named(GTK_STACK(riwayatPasienPage_Stack), riwayatPasienPage_CariData, page_names[0]);
    DataCallBack *callBack = g_malloc(sizeof(DataCallBack));
    callBack->stackContainer = riwayatPasienPage_Stack;
    callBack->page_name = page_names[0];
    g_signal_connect(funcButton[0], "clicked", G_CALLBACK(on_button_clicked_with_page), callBack);

    // Tambah Data Page
    GtkWidget *riwayatPasienPage_TambahData = RiwayatPasienPage_TambahData();
    gtk_stack_add_named(GTK_STACK(riwayatPasienPage_Stack), riwayatPasienPage_TambahData, page_names[1]);
    callBack = g_malloc(sizeof(DataCallBack));
    callBack->stackContainer = riwayatPasienPage_Stack;
    callBack->page_name = page_names[1];
    g_signal_connect(funcButton[1], "clicked", G_CALLBACK(on_button_clicked_with_page), callBack);

    // // Ubah Data Page
    GtkWidget *riwayatPasienPage_UbahData = RiwayatPasienPage_UbahData();
    gtk_stack_add_named(GTK_STACK(riwayatPasienPage_Stack), riwayatPasienPage_UbahData, page_names[2]);
    callBack = g_malloc(sizeof(DataCallBack));
    callBack->stackContainer = riwayatPasienPage_Stack;
    callBack->page_name = page_names[2];
    g_signal_connect(funcButton[2], "clicked", G_CALLBACK(on_button_clicked_with_page), callBack);

    // // Hapus Data Page
    GtkWidget *riwayatPasienPage_hapusData = RiwayatPasienPage_HapusData();
    gtk_stack_add_named(GTK_STACK(riwayatPasienPage_Stack), riwayatPasienPage_hapusData, page_names[3]);
    callBack = g_malloc(sizeof(DataCallBack));
    callBack->stackContainer = riwayatPasienPage_Stack;
    callBack->page_name = page_names[3];
    g_signal_connect(funcButton[3], "clicked", G_CALLBACK(on_button_clicked_with_page), callBack);

    GtkWidget *footer = addFooter(page);
    return page;
}