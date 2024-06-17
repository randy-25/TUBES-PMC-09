#include "../header/gui_pasienDataPage.h"

// DATA PASIEN PAGE

// -------- CARI DATA PASIEN PAGE --------
// reset the data pasien page
void reset_cariData_pasien_page()
{
    // Count the children
    GtkWidget *child = gtk_widget_get_first_child(GTK_WIDGET(dataPasienPage_cariData_pasienInfo));
    int child_count = 0;
    while (child != NULL)
    {
        child = gtk_widget_get_next_sibling(child);
        child_count++;
    }

    // Remove all but the last child
    child = gtk_widget_get_first_child(GTK_WIDGET(dataPasienPage_cariData_pasienInfo));
    for (int i = 0; i < child_count - 1; i++)
    {
        GtkWidget *next = gtk_widget_get_next_sibling(child);
        gtk_box_remove(GTK_BOX(dataPasienPage_cariData_pasienInfo), child);
        child = next;
    }
}

// Back to previous page button click
void on_back_cariDataPasien_gui(GtkButton *button, gpointer user_data)
{
    reset_cariData_pasien_page();
    DataCallBack *data = (DataCallBack *)user_data;
    gtk_stack_set_visible_child_name(GTK_STACK(data->stackContainer), data->page_name);
}

// Callback function to search patient data
void on_cari_pasien_data_gui(GtkButton *button, gpointer user_data)
{
    GtkWidget *data = user_data;
    const char *input_text = gtk_editable_get_text(GTK_EDITABLE(data)); // get the input text from the entry

    char *idPasien = strdup(input_text); // get the data from the entry
    struct dataPasien dataHolder;
    int confirm;
    cariPasien(pasien, jumlahPasien, idPasien, &dataHolder, &confirm); // search the data from the patient data

    // Clear the input box entry
    const gchar *default_text = "KX ";
    gtk_editable_set_text(GTK_EDITABLE(data), default_text);
    gtk_editable_set_position(GTK_EDITABLE(data), strlen(default_text));

    // Clear the existing content of the box
    GtkWidget *child = gtk_widget_get_first_child(GTK_WIDGET(dataPasienPage_cariData_pasienInfo));
    while (child != NULL)
    {
        GtkWidget *next = gtk_widget_get_next_sibling(child);
        gtk_box_remove(GTK_BOX(dataPasienPage_cariData_pasienInfo), child);
        child = next;
    }

    if (confirm == 1)
    {
        // Create new labels to display the data
        char info[256]; // Ensure that the buffer is large enough

        snprintf(info, sizeof(info), "ID Pasien: %s", dataHolder.IdPasien);
        GtkWidget *id_label = gtk_label_new(info);
        gtk_box_append(GTK_BOX(dataPasienPage_cariData_pasienInfo), id_label);

        snprintf(info, sizeof(info), "Nama: %s", dataHolder.nama);
        GtkWidget *nama_label = gtk_label_new(info);
        gtk_box_append(GTK_BOX(dataPasienPage_cariData_pasienInfo), nama_label);

        snprintf(info, sizeof(info), "Alamat: %s", dataHolder.alamat);
        GtkWidget *alamat_label = gtk_label_new(info);
        gtk_box_append(GTK_BOX(dataPasienPage_cariData_pasienInfo), alamat_label);

        snprintf(info, sizeof(info), "Kota: %s", dataHolder.kota);
        GtkWidget *kota_label = gtk_label_new(info);
        gtk_box_append(GTK_BOX(dataPasienPage_cariData_pasienInfo), kota_label);

        snprintf(info, sizeof(info), "Tempat Lahir: %s", dataHolder.tempatLahir);
        GtkWidget *tempat_lahir_label = gtk_label_new(info);
        gtk_box_append(GTK_BOX(dataPasienPage_cariData_pasienInfo), tempat_lahir_label);

        snprintf(info, sizeof(info), "Tanggal Lahir: %02d-%02d-%04d", dataHolder.tanggalLahir.tanggal, dataHolder.tanggalLahir.bulan, dataHolder.tanggalLahir.tahun);
        GtkWidget *tanggal_lahir_label = gtk_label_new(info);
        gtk_box_append(GTK_BOX(dataPasienPage_cariData_pasienInfo), tanggal_lahir_label);

        snprintf(info, sizeof(info), "Umur: %d", dataHolder.umur);
        GtkWidget *umur_label = gtk_label_new(info);
        gtk_box_append(GTK_BOX(dataPasienPage_cariData_pasienInfo), umur_label);

        snprintf(info, sizeof(info), "Nomor BPJS: %s", dataHolder.nomorBPJS);
        GtkWidget *bpjs_label = gtk_label_new(info);
        gtk_box_append(GTK_BOX(dataPasienPage_cariData_pasienInfo), bpjs_label);
    }
    else
    {
        GtkWidget *not_found_label = gtk_label_new("Data Pasien tidak ditemukan");
        gtk_box_append(GTK_BOX(dataPasienPage_cariData_pasienInfo), not_found_label);
    }

    GtkWidget *back_button = gtk_button_new_with_label("Back");
    gtk_widget_set_halign(back_button, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(dataPasienPage_cariData_pasienInfo), back_button);
    DataCallBack *callBack = g_malloc(sizeof(DataCallBack));
    callBack->stackContainer = dataPasienPage_Stack;
    callBack->page_name = "MainGrid";
    g_signal_connect(back_button, "clicked", G_CALLBACK(on_back_cariDataPasien_gui), callBack);
}

GtkWidget *DataPasienPage_CariData()
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

    dataPasienPage_cariData_pasienInfo = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_append(GTK_BOX(page), dataPasienPage_cariData_pasienInfo);

    g_signal_connect(button, "clicked", G_CALLBACK(on_cari_pasien_data_gui), entry);

    GtkWidget *back_button = gtk_button_new_with_label("Back");
    gtk_widget_set_halign(back_button, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(dataPasienPage_cariData_pasienInfo), back_button);
    DataCallBack *callBack = g_malloc(sizeof(DataCallBack));
    callBack->stackContainer = dataPasienPage_Stack;
    callBack->page_name = "MainGrid";
    g_signal_connect(back_button, "clicked", G_CALLBACK(on_back_cariDataPasien_gui), callBack);

    return page;
}
// -------- END OF CARI DATA PASIEN PAGE --------


// -------- TAMBAH DATA PASIEN PAGE --------
void reset_tambahData_pasien_page()
{
    // Count the children
    GtkWidget *child = gtk_widget_get_first_child(GTK_WIDGET(dataPasienPage_tambahData_pasienInfo));
    int child_count = 0;
    while (child != NULL)
    {
        child = gtk_widget_get_next_sibling(child);
        child_count++;
    }

    // Remove all but the last child
    child = gtk_widget_get_first_child(GTK_WIDGET(dataPasienPage_tambahData_pasienInfo));
    for (int i = 0; i < child_count - 1; i++)
    {
        GtkWidget *next = gtk_widget_get_next_sibling(child);
        gtk_box_remove(GTK_BOX(dataPasienPage_tambahData_pasienInfo), child);
        child = next;
    }
}

void on_back_tambahDataPasien_gui(GtkButton *button, gpointer user_data)
{
    reset_tambahData_pasien_page();
    DataCallBack *data = (DataCallBack *)user_data;
    gtk_stack_set_visible_child_name(GTK_STACK(data->stackContainer), data->page_name);
}

GtkWidget *ShowNewPatientDataPage(struct dataPasien *new_patient, void callBackFunction(GtkButton *button, gpointer user_data))
{
    GtkWidget *page = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    // Title
    GtkWidget *title = gtk_label_new("Data Pasien");
    gtk_widget_set_halign(title, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(page), title);

    // Display the new patient data
    char info[256];

    snprintf(info, sizeof(info), "Nama: %s", new_patient->nama);
    GtkWidget *nama_label = gtk_label_new(info);
    gtk_box_append(GTK_BOX(page), nama_label);

    snprintf(info, sizeof(info), "Alamat: %s", new_patient->alamat);
    GtkWidget *alamat_label = gtk_label_new(info);
    gtk_box_append(GTK_BOX(page), alamat_label);

    snprintf(info, sizeof(info), "Kota: %s", new_patient->kota);
    GtkWidget *kota_label = gtk_label_new(info);
    gtk_box_append(GTK_BOX(page), kota_label);

    snprintf(info, sizeof(info), "Tempat Lahir: %s", new_patient->tempatLahir);
    GtkWidget *tempat_lahir_label = gtk_label_new(info);
    gtk_box_append(GTK_BOX(page), tempat_lahir_label);

    snprintf(info, sizeof(info), "Tanggal Lahir: %d-%d-%d", new_patient->tanggalLahir.tanggal, new_patient->tanggalLahir.bulan, new_patient->tanggalLahir.tahun);
    GtkWidget *tanggal_lahir_label = gtk_label_new(info);
    gtk_box_append(GTK_BOX(page), tanggal_lahir_label);

    snprintf(info, sizeof(info), "No BPJS: %s", new_patient->nomorBPJS);
    GtkWidget *no_bpjs_label = gtk_label_new(info);
    gtk_box_append(GTK_BOX(page), no_bpjs_label);

    snprintf(info, sizeof(info), "ID Pasien: %s", new_patient->IdPasien);
    GtkWidget *id_label = gtk_label_new(info);
    gtk_box_append(GTK_BOX(page), id_label);

    // Add a button to go back to the landing page
    GtkWidget *back_button = gtk_button_new_with_label("Back");
    gtk_widget_set_halign(back_button, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(page), back_button);

    DataCallBack *callBack = g_malloc(sizeof(DataCallBack));
    callBack->stackContainer = dataPasienPage_Stack;
    callBack->page_name = "MainGrid";
    g_signal_connect(back_button, "clicked", G_CALLBACK(callBackFunction), callBack);

    return page;
}

void on_submit_data_pasien(GtkButton *button, gpointer user_data)
{
    DataPasienEntry *entry = (DataPasienEntry *)user_data;
    const gchar *nama = gtk_editable_get_text(GTK_EDITABLE(entry->entry_nama));
    const gchar *alamat = gtk_editable_get_text(GTK_EDITABLE(entry->entry_alamat));
    const gchar *kota = gtk_editable_get_text(GTK_EDITABLE(entry->entry_kota));
    const gchar *tempat_lahir = gtk_editable_get_text(GTK_EDITABLE(entry->entry_tempat_lahir));
    const gchar *tanggal_lahir = gtk_editable_get_text(GTK_EDITABLE(entry->entry_tanggal_lahir));
    const gchar *no_bpjs = gtk_editable_get_text(GTK_EDITABLE(entry->entry_no_bpjs));

    char *tempNama = strdup(nama);
    char *tempAlamat = strdup(alamat);
    char *tempKota = strdup(kota);
    char *tempTempatLahir = strdup(tempat_lahir);
    char *tempTanggalLahir = strdup(tanggal_lahir);
    char *tempNoBPJS = strdup(no_bpjs);

    // Clear the input box entry
    const gchar *default_text = "";
    gtk_editable_set_text(GTK_EDITABLE(entry->entry_nama), default_text);
    gtk_editable_set_position(GTK_EDITABLE(entry->entry_nama), strlen(default_text));

    gtk_editable_set_text(GTK_EDITABLE(entry->entry_alamat), default_text);
    gtk_editable_set_position(GTK_EDITABLE(entry->entry_alamat), strlen(default_text));

    gtk_editable_set_text(GTK_EDITABLE(entry->entry_kota), default_text);
    gtk_editable_set_position(GTK_EDITABLE(entry->entry_kota), strlen(default_text));

    gtk_editable_set_text(GTK_EDITABLE(entry->entry_tempat_lahir), default_text);
    gtk_editable_set_position(GTK_EDITABLE(entry->entry_tempat_lahir), strlen(default_text));

    gtk_editable_set_text(GTK_EDITABLE(entry->entry_tanggal_lahir), default_text);
    gtk_editable_set_position(GTK_EDITABLE(entry->entry_tanggal_lahir), strlen(default_text));

    gtk_editable_set_text(GTK_EDITABLE(entry->entry_no_bpjs), default_text);
    gtk_editable_set_position(GTK_EDITABLE(entry->entry_no_bpjs), strlen(default_text));

    struct dataPasien newPasienHolder;
    int confirm;

    tambahPasien(&pasien, &jumlahPasien, tempNoBPJS, tempNama, tempAlamat, tempKota, tempTempatLahir, tempTanggalLahir, &newPasienHolder, &confirm);

    if (confirm == 1)
    {

        GtkWidget *tempWidget = gtk_stack_get_child_by_name(GTK_STACK(dataPasienPage_Stack), "NewPatientData");

        if (tempWidget != NULL)
        {
            gtk_stack_remove(GTK_STACK(dataPasienPage_Stack), tempWidget);
        }

        // Create and show the new patient data page
        GtkWidget *newPatientPage;
        newPatientPage = ShowNewPatientDataPage(&newPasienHolder, on_back_tambahDataPasien_gui);
        gtk_stack_add_named(GTK_STACK(dataPasienPage_Stack), newPatientPage, "NewPatientData");
        gtk_stack_set_visible_child(GTK_STACK(dataPasienPage_Stack), newPatientPage);
    }
    else
    {
        // printf("Data Pasien Telah Terdaftar\n");

        GtkWidget *tempWidget = gtk_stack_get_child_by_name(GTK_STACK(dataPasienPage_Stack), "FailedPage");

        if (tempWidget != NULL)
        {
            gtk_stack_remove(GTK_STACK(dataPasienPage_Stack), tempWidget);
        }

        dataPasienPage_tambahData_pasienInfo = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
        GtkWidget *failedLabel = gtk_label_new("Nomor BPJS Pasien Telah Terdaftar");
        gtk_widget_set_halign(failedLabel, GTK_ALIGN_CENTER);
        gtk_box_append(GTK_BOX(dataPasienPage_tambahData_pasienInfo), failedLabel);

        GtkWidget *tempPasienInfo = ShowNewPatientDataPage(&newPasienHolder, on_back_tambahDataPasien_gui);
        gtk_box_append(GTK_BOX(dataPasienPage_tambahData_pasienInfo), tempPasienInfo);

        gtk_stack_add_named(GTK_STACK(dataPasienPage_Stack), dataPasienPage_tambahData_pasienInfo, "FailedPage");
        gtk_stack_set_visible_child(GTK_STACK(dataPasienPage_Stack), dataPasienPage_tambahData_pasienInfo);
    }
}

GtkWidget *DataPasienPage_TambahData()
{
    dataPasienPage_tambahData_pasienInfo = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    GtkWidget *page = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    GtkWidget *entry_nama;
    GtkWidget *entry_alamat;
    GtkWidget *entry_kota;
    GtkWidget *entry_tempat_lahir;
    GtkWidget *entry_tanggal_lahir;
    GtkWidget *entry_no_bpjs;

    GtkWidget *title = gtk_label_new("Tambah Data Pasien");
    gtk_widget_set_halign(title, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(page), title);

    GtkWidget *formGrid = gtk_grid_new();
    gtk_grid_set_column_homogeneous(GTK_GRID(formGrid), TRUE);
    gtk_grid_set_row_homogeneous(GTK_GRID(formGrid), TRUE);
    gtk_grid_set_row_spacing(GTK_GRID(formGrid), 10);
    gtk_widget_set_halign(formGrid, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(page), formGrid);

    // Nama
    GtkWidget *label_nama = gtk_label_new("Nama Pasien: ");
    entry_nama = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(formGrid), label_nama, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(formGrid), entry_nama, 1, 0, 1, 1);

    // Alamat
    GtkWidget *label_alamat = gtk_label_new("Alamat Pasien: ");
    entry_alamat = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(formGrid), label_alamat, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(formGrid), entry_alamat, 1, 1, 1, 1);

    // Kota
    GtkWidget *label_kota = gtk_label_new("Kota:");
    entry_kota = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(formGrid), label_kota, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(formGrid), entry_kota, 1, 2, 1, 1);

    // Tempat Lahir
    GtkWidget *label_tempat_lahir = gtk_label_new("Tempat Lahir:");
    entry_tempat_lahir = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(formGrid), label_tempat_lahir, 0, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(formGrid), entry_tempat_lahir, 1, 3, 1, 1);

    // Tanggal Lahir
    GtkWidget *label_tanggal_lahir = gtk_label_new("Tanggal Lahir (DD-MM-YYYY):");
    entry_tanggal_lahir = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(formGrid), label_tanggal_lahir, 0, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(formGrid), entry_tanggal_lahir, 1, 4, 1, 1);

    // No BPJS
    GtkWidget *label_no_bpjs = gtk_label_new("No BPJS:");
    entry_no_bpjs = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(formGrid), label_no_bpjs, 0, 5, 1, 1);
    gtk_grid_attach(GTK_GRID(formGrid), entry_no_bpjs, 1, 5, 1, 1);

    // Submit Button
    GtkWidget *submit_button = gtk_button_new_with_label("Submit");
    gtk_widget_set_halign(submit_button, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(page), submit_button);

    DataPasienEntry *entry_data = g_malloc(sizeof(DataPasienEntry));
    entry_data->entry_nama = entry_nama;
    entry_data->entry_alamat = entry_alamat;
    entry_data->entry_kota = entry_kota;
    entry_data->entry_tempat_lahir = entry_tempat_lahir;
    entry_data->entry_tanggal_lahir = entry_tanggal_lahir;
    entry_data->entry_no_bpjs = entry_no_bpjs;

    g_signal_connect(submit_button, "clicked", G_CALLBACK(on_submit_data_pasien), entry_data);

    GtkWidget *back_button = gtk_button_new_with_label("Back");
    gtk_widget_set_halign(back_button, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(page), back_button);

    DataCallBack *callBack = g_malloc(sizeof(DataCallBack));
    callBack->stackContainer = dataPasienPage_Stack;
    callBack->page_name = "MainGrid";
    g_signal_connect(back_button, "clicked", G_CALLBACK(on_back_tambahDataPasien_gui), callBack);
    return page;
}
// -------- END OF TAMBAH DATA PASIEN PAGE --------


// -------- UBAH DATA PASIEN PAGE --------
void reset_ubahData_pasien_page()
{
    // Count the children
    GtkWidget *child = gtk_widget_get_first_child(GTK_WIDGET(dataPasienPage_ubahData_pasienInfo));
    int child_count = 0;
    while (child != NULL)
    {
        child = gtk_widget_get_next_sibling(child);
        child_count++;
    }

    // Remove all but the last child
    child = gtk_widget_get_first_child(GTK_WIDGET(dataPasienPage_ubahData_pasienInfo));
    for (int i = 0; i < child_count - 1; i++)
    {
        GtkWidget *next = gtk_widget_get_next_sibling(child);
        gtk_box_remove(GTK_BOX(dataPasienPage_ubahData_pasienInfo), child);
        child = next;
    }
}

// Back to previous page button click
void on_back_ubahDataPasien_gui(GtkButton *button, gpointer user_data)
{
    reset_ubahData_pasien_page();
    DataCallBack *data = (DataCallBack *)user_data;
    gtk_stack_set_visible_child_name(GTK_STACK(data->stackContainer), data->page_name);
}

void on_submit_ubahData_pasien_page(GtkButton *button, gpointer user_data)
{
    DataPasienEntry *entry = (DataPasienEntry *)user_data;
    const gchar *nama = gtk_editable_get_text(GTK_EDITABLE(entry->entry_nama));
    const gchar *alamat = gtk_editable_get_text(GTK_EDITABLE(entry->entry_alamat));
    const gchar *kota = gtk_editable_get_text(GTK_EDITABLE(entry->entry_kota));
    const gchar *tempat_lahir = gtk_editable_get_text(GTK_EDITABLE(entry->entry_tempat_lahir));
    const gchar *tanggal_lahir = gtk_editable_get_text(GTK_EDITABLE(entry->entry_tanggal_lahir));
    const gchar *no_bpjs = gtk_editable_get_text(GTK_EDITABLE(entry->entry_no_bpjs));

    char *tempNama = strdup(nama);
    char *tempAlamat = strdup(alamat);
    char *tempKota = strdup(kota);
    char *tempTempatLahir = strdup(tempat_lahir);
    char *tempTanggalLahir = strdup(tanggal_lahir);
    char *tempNoBPJS = strdup(no_bpjs);
    char *idPasien = strdup(entry->id_pasien);

    // Clear the input box entry
    const gchar *default_text = "";
    gtk_editable_set_text(GTK_EDITABLE(entry->entry_nama), default_text);
    gtk_editable_set_position(GTK_EDITABLE(entry->entry_nama), strlen(default_text));

    gtk_editable_set_text(GTK_EDITABLE(entry->entry_alamat), default_text);
    gtk_editable_set_position(GTK_EDITABLE(entry->entry_alamat), strlen(default_text));

    gtk_editable_set_text(GTK_EDITABLE(entry->entry_kota), default_text);
    gtk_editable_set_position(GTK_EDITABLE(entry->entry_kota), strlen(default_text));

    gtk_editable_set_text(GTK_EDITABLE(entry->entry_tempat_lahir), default_text);
    gtk_editable_set_position(GTK_EDITABLE(entry->entry_tempat_lahir), strlen(default_text));

    gtk_editable_set_text(GTK_EDITABLE(entry->entry_tanggal_lahir), default_text);
    gtk_editable_set_position(GTK_EDITABLE(entry->entry_tanggal_lahir), strlen(default_text));

    gtk_editable_set_text(GTK_EDITABLE(entry->entry_no_bpjs), default_text);
    gtk_editable_set_position(GTK_EDITABLE(entry->entry_no_bpjs), strlen(default_text));

    struct dataPasien newPasienHolder;
    int confirm;

    ubahDataPasien(&pasien, jumlahPasien, idPasien, tempNoBPJS, tempNama, tempAlamat, tempKota, tempTempatLahir, tempTanggalLahir, &newPasienHolder, &confirm);

    if (confirm == 1)
    {

        GtkWidget *tempWidget = gtk_stack_get_child_by_name(GTK_STACK(dataPasienPage_Stack), "NewPatientData");

        if (tempWidget != NULL)
        {
            gtk_stack_remove(GTK_STACK(dataPasienPage_Stack), tempWidget);
        }

        // Create and show the new patient data page
        dataPasienPage_tambahData_pasienInfo = ShowNewPatientDataPage(&newPasienHolder, on_back_ubahDataPasien_gui);
        gtk_stack_add_named(GTK_STACK(dataPasienPage_Stack), dataPasienPage_tambahData_pasienInfo, "NewPatientData");
        gtk_stack_set_visible_child(GTK_STACK(dataPasienPage_Stack), dataPasienPage_tambahData_pasienInfo);
    }
    else
    {

        GtkWidget *tempWidget = gtk_stack_get_child_by_name(GTK_STACK(dataPasienPage_Stack), "FailedPage");

        if (tempWidget != NULL)
        {
            gtk_stack_remove(GTK_STACK(dataPasienPage_Stack), tempWidget);
        }

        dataPasienPage_tambahData_pasienInfo = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
        GtkWidget *failedLabel = gtk_label_new("Nomor BPJS Pasien Telah Terdaftar");
        gtk_widget_set_halign(failedLabel, GTK_ALIGN_CENTER);
        gtk_box_append(GTK_BOX(dataPasienPage_tambahData_pasienInfo), failedLabel);

        GtkWidget *tempPasienInfo = ShowNewPatientDataPage(&newPasienHolder, on_back_ubahDataPasien_gui);
        gtk_box_append(GTK_BOX(dataPasienPage_tambahData_pasienInfo), tempPasienInfo);

        gtk_stack_add_named(GTK_STACK(dataPasienPage_Stack), dataPasienPage_tambahData_pasienInfo, "FailedPage");
        gtk_stack_set_visible_child(GTK_STACK(dataPasienPage_Stack), dataPasienPage_tambahData_pasienInfo);
    }
}

GtkWidget *ubahData_form_page(char *IdPasien_data)
{
    GtkWidget *page = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    GtkWidget *entry_nama;
    GtkWidget *entry_alamat;
    GtkWidget *entry_kota;
    GtkWidget *entry_tempat_lahir;
    GtkWidget *entry_tanggal_lahir;
    GtkWidget *entry_no_bpjs;

    GtkWidget *title = gtk_label_new("Tambah Data Pasien");
    gtk_widget_set_halign(title, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(page), title);

    GtkWidget *formGrid = gtk_grid_new();
    gtk_grid_set_column_homogeneous(GTK_GRID(formGrid), TRUE);
    gtk_grid_set_row_homogeneous(GTK_GRID(formGrid), TRUE);
    gtk_grid_set_row_spacing(GTK_GRID(formGrid), 10);
    gtk_widget_set_halign(formGrid, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(page), formGrid);

    // Nama
    GtkWidget *label_nama = gtk_label_new("Nama Pasien: ");
    entry_nama = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(formGrid), label_nama, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(formGrid), entry_nama, 1, 0, 1, 1);

    // Alamat
    GtkWidget *label_alamat = gtk_label_new("Alamat Pasien: ");
    entry_alamat = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(formGrid), label_alamat, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(formGrid), entry_alamat, 1, 1, 1, 1);

    // Kota
    GtkWidget *label_kota = gtk_label_new("Kota:");
    entry_kota = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(formGrid), label_kota, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(formGrid), entry_kota, 1, 2, 1, 1);

    // Tempat Lahir
    GtkWidget *label_tempat_lahir = gtk_label_new("Tempat Lahir:");
    entry_tempat_lahir = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(formGrid), label_tempat_lahir, 0, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(formGrid), entry_tempat_lahir, 1, 3, 1, 1);

    // Tanggal Lahir
    GtkWidget *label_tanggal_lahir = gtk_label_new("Tanggal Lahir (DD-MM-YYYY):");
    entry_tanggal_lahir = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(formGrid), label_tanggal_lahir, 0, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(formGrid), entry_tanggal_lahir, 1, 4, 1, 1);

    // No BPJS
    GtkWidget *label_no_bpjs = gtk_label_new("No BPJS:");
    entry_no_bpjs = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(formGrid), label_no_bpjs, 0, 5, 1, 1);
    gtk_grid_attach(GTK_GRID(formGrid), entry_no_bpjs, 1, 5, 1, 1);

    // Submit Button
    GtkWidget *submit_button = gtk_button_new_with_label("Submit");
    gtk_widget_set_halign(submit_button, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(page), submit_button);


    // Wrap the data into a struct
    DataPasienEntry *entry_data = g_malloc(sizeof(DataPasienEntry));
    entry_data->entry_nama = entry_nama;
    entry_data->entry_alamat = entry_alamat;
    entry_data->entry_kota = entry_kota;
    entry_data->entry_tempat_lahir = entry_tempat_lahir;
    entry_data->entry_tanggal_lahir = entry_tanggal_lahir;
    entry_data->entry_no_bpjs = entry_no_bpjs;
    entry_data->id_pasien = strdup(IdPasien_data);

    g_signal_connect(submit_button, "clicked", G_CALLBACK(on_submit_ubahData_pasien_page), entry_data);

    GtkWidget *back_button = gtk_button_new_with_label("Back");
    gtk_widget_set_halign(back_button, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(page), back_button);

    DataCallBack *callBack = g_malloc(sizeof(DataCallBack));
    callBack->stackContainer = dataPasienPage_Stack;
    callBack->page_name = "UbahDataPasien";
    g_signal_connect(back_button, "clicked", G_CALLBACK(on_back_ubahDataPasien_gui), callBack);
    return page;
}

void on_confirm_ubahData_pasien_page(GtkButton *button, gpointer user_data)
{
    char *IdPasien_data = user_data;

    GtkWidget *ubahPage = ubahData_form_page(IdPasien_data);

    GtkWidget *tempWidget = gtk_stack_get_child_by_name(GTK_STACK(dataPasienPage_Stack), "UbahDataPasienFormPage");

    if (tempWidget != NULL)
    {
        gtk_stack_remove(GTK_STACK(dataPasienPage_Stack), tempWidget);
    }
    gtk_stack_add_named(GTK_STACK(dataPasienPage_Stack), ubahPage, "UbahDataPasienFormPage");
    gtk_stack_set_visible_child(GTK_STACK(dataPasienPage_Stack), ubahPage);
}

void on_cari_pasienData_ubahData_gui(GtkButton *button, gpointer user_data)
{
    GtkWidget *data = user_data;
    const char *input_text = gtk_editable_get_text(GTK_EDITABLE(data)); // get the input text from the entry

    char *idPasien = strdup(input_text); // get the data from the entry
    struct dataPasien dataHolder;
    int confirm;
    cariPasien(pasien, jumlahPasien, idPasien, &dataHolder, &confirm); // search the data from the patient data

    // Clear the input box entry
    const gchar *default_text = "KX ";
    gtk_editable_set_text(GTK_EDITABLE(data), default_text);
    gtk_editable_set_position(GTK_EDITABLE(data), strlen(default_text));

    // Clear the existing content of the box
    GtkWidget *child = gtk_widget_get_first_child(GTK_WIDGET(dataPasienPage_ubahData_pasienInfo));
    while (child != NULL)
    {
        GtkWidget *next = gtk_widget_get_next_sibling(child);
        gtk_box_remove(GTK_BOX(dataPasienPage_ubahData_pasienInfo), child);
        child = next;
    }

    if (confirm == 1)
    {
        // Create new labels to display the data
        char info[256]; // Ensure that the buffer is large enough

        snprintf(info, sizeof(info), "ID Pasien: %s", dataHolder.IdPasien);
        GtkWidget *id_label = gtk_label_new(info);
        gtk_box_append(GTK_BOX(dataPasienPage_ubahData_pasienInfo), id_label);

        snprintf(info, sizeof(info), "Nama: %s", dataHolder.nama);
        GtkWidget *nama_label = gtk_label_new(info);
        gtk_box_append(GTK_BOX(dataPasienPage_ubahData_pasienInfo), nama_label);

        snprintf(info, sizeof(info), "Alamat: %s", dataHolder.alamat);
        GtkWidget *alamat_label = gtk_label_new(info);
        gtk_box_append(GTK_BOX(dataPasienPage_ubahData_pasienInfo), alamat_label);

        snprintf(info, sizeof(info), "Kota: %s", dataHolder.kota);
        GtkWidget *kota_label = gtk_label_new(info);
        gtk_box_append(GTK_BOX(dataPasienPage_ubahData_pasienInfo), kota_label);

        snprintf(info, sizeof(info), "Tempat Lahir: %s", dataHolder.tempatLahir);
        GtkWidget *tempat_lahir_label = gtk_label_new(info);
        gtk_box_append(GTK_BOX(dataPasienPage_ubahData_pasienInfo), tempat_lahir_label);

        snprintf(info, sizeof(info), "Tanggal Lahir: %02d-%02d-%04d", dataHolder.tanggalLahir.tanggal, dataHolder.tanggalLahir.bulan, dataHolder.tanggalLahir.tahun);
        GtkWidget *tanggal_lahir_label = gtk_label_new(info);
        gtk_box_append(GTK_BOX(dataPasienPage_ubahData_pasienInfo), tanggal_lahir_label);

        snprintf(info, sizeof(info), "Umur: %d", dataHolder.umur);
        GtkWidget *umur_label = gtk_label_new(info);
        gtk_box_append(GTK_BOX(dataPasienPage_ubahData_pasienInfo), umur_label);

        snprintf(info, sizeof(info), "Nomor BPJS: %s", dataHolder.nomorBPJS);
        GtkWidget *bpjs_label = gtk_label_new(info);
        gtk_box_append(GTK_BOX(dataPasienPage_ubahData_pasienInfo), bpjs_label);

        GtkWidget *ubah_button = gtk_button_new_with_label("Ubah Data");
        gtk_widget_set_halign(ubah_button, GTK_ALIGN_CENTER);
        gtk_box_append(GTK_BOX(dataPasienPage_ubahData_pasienInfo), ubah_button);

        char *tempIdPasien = strdup(dataHolder.IdPasien);
        g_signal_connect(ubah_button, "clicked", G_CALLBACK(on_confirm_ubahData_pasien_page), tempIdPasien);
    }
    else
    {
        GtkWidget *not_found_label = gtk_label_new("Data Pasien tidak ditemukan");
        gtk_box_append(GTK_BOX(dataPasienPage_ubahData_pasienInfo), not_found_label);
    }

    GtkWidget *back_button = gtk_button_new_with_label("Back");
    gtk_widget_set_halign(back_button, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(dataPasienPage_ubahData_pasienInfo), back_button);
    DataCallBack *callBack = g_malloc(sizeof(DataCallBack));
    callBack->stackContainer = dataPasienPage_Stack;
    callBack->page_name = "MainGrid";
    g_signal_connect(back_button, "clicked", G_CALLBACK(on_back_ubahDataPasien_gui), callBack);
}

GtkWidget *DataPasienPage_UbahData()
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

    dataPasienPage_ubahData_pasienInfo = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_append(GTK_BOX(page), dataPasienPage_ubahData_pasienInfo);

    g_signal_connect(button, "clicked", G_CALLBACK(on_cari_pasienData_ubahData_gui), entry);

    GtkWidget *back_button = gtk_button_new_with_label("Back");
    gtk_widget_set_halign(back_button, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(dataPasienPage_ubahData_pasienInfo), back_button);
    DataCallBack *callBack = g_malloc(sizeof(DataCallBack));
    callBack->stackContainer = dataPasienPage_Stack;
    callBack->page_name = "MainGrid";
    g_signal_connect(back_button, "clicked", G_CALLBACK(on_button_clicked_with_page), callBack);

    return page;
}
// -------- END OF UBAH DATA PASIEN PAGE --------

// -------- HAPUS DATA PASIEN PAGE --------
void reset_hapusData_pasien_page()
{
    // Count the children
    GtkWidget *child = gtk_widget_get_first_child(GTK_WIDGET(dataPasienPage_hapusData_pasienInfo));
    int child_count = 0;
    while (child != NULL)
    {
        child = gtk_widget_get_next_sibling(child);
        child_count++;
    }

    // Remove all but the last child
    child = gtk_widget_get_first_child(GTK_WIDGET(dataPasienPage_hapusData_pasienInfo));
    for (int i = 0; i < child_count - 1; i++)
    {
        GtkWidget *next = gtk_widget_get_next_sibling(child);
        gtk_box_remove(GTK_BOX(dataPasienPage_hapusData_pasienInfo), child);
        child = next;
    }
}

// Back to previous page button click
void on_back_hapusDataPasien_gui(GtkButton *button, gpointer user_data)
{
    reset_hapusData_pasien_page();
    DataCallBack *data = (DataCallBack *)user_data;
    gtk_stack_set_visible_child_name(GTK_STACK(data->stackContainer), data->page_name);
}

void on_confirm_hapusData_pasien_page(GtkButton *button, gpointer user_data)
{
    char *IdPasien_data = user_data;
    int confirm;
    hapusDataPasien(&pasien, &jumlahPasien, IdPasien_data, &confirm);

    GtkWidget *tempWidget = gtk_stack_get_child_by_name(GTK_STACK(dataPasienPage_Stack), "HapusDataPasienFormPage");

    if (tempWidget != NULL)
    {
        gtk_stack_remove(GTK_STACK(dataPasienPage_Stack), tempWidget);
    }
    GtkWidget *hapusPage = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    GtkWidget *hapusLabel;
    if (confirm == 1)
    {
        hapusLabel = gtk_label_new("Data Pasien berhasil dihapus");
    }
    else
    {
        hapusLabel = gtk_label_new("Data Pasien tidak ditemukan");
    }
    gtk_widget_set_halign(hapusLabel, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(hapusPage), hapusLabel);

    GtkWidget *back_button = gtk_button_new_with_label("Back");
    gtk_widget_set_halign(back_button, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(hapusPage), back_button);

    DataCallBack *callBack = g_malloc(sizeof(DataCallBack));
    callBack->stackContainer = dataPasienPage_Stack;
    callBack->page_name = "HapusDataPasien";
    g_signal_connect(back_button, "clicked", G_CALLBACK(on_back_hapusDataPasien_gui), callBack);
    gtk_stack_add_named(GTK_STACK(dataPasienPage_Stack), hapusPage, "HapusDataPasienFormPage");
    gtk_stack_set_visible_child(GTK_STACK(dataPasienPage_Stack), hapusPage);


}

void on_cari_pasienData_hapusData_gui(GtkButton *button, gpointer user_data)
{
    GtkWidget *data = user_data;
    const char *input_text = gtk_editable_get_text(GTK_EDITABLE(data)); // get the input text from the entry

    char *idPasien = strdup(input_text); // get the data from the entry
    struct dataPasien dataHolder;
    int confirm;
    cariPasien(pasien, jumlahPasien, idPasien, &dataHolder, &confirm); // search the data from the patient data

    // Clear the input box entry
    const gchar *default_text = "KX ";
    gtk_editable_set_text(GTK_EDITABLE(data), default_text);
    gtk_editable_set_position(GTK_EDITABLE(data), strlen(default_text));

    // Clear the existing content of the box
    GtkWidget *child = gtk_widget_get_first_child(GTK_WIDGET(dataPasienPage_hapusData_pasienInfo));
    while (child != NULL)
    {
        GtkWidget *next = gtk_widget_get_next_sibling(child);
        gtk_box_remove(GTK_BOX(dataPasienPage_hapusData_pasienInfo), child);
        child = next;
    }

    if (confirm == 1)
    {
        // Create new labels to display the data
        char info[256]; // Ensure that the buffer is large enough

        snprintf(info, sizeof(info), "ID Pasien: %s", dataHolder.IdPasien);
        GtkWidget *id_label = gtk_label_new(info);
        gtk_box_append(GTK_BOX(dataPasienPage_hapusData_pasienInfo), id_label);

        snprintf(info, sizeof(info), "Nama: %s", dataHolder.nama);
        GtkWidget *nama_label = gtk_label_new(info);
        gtk_box_append(GTK_BOX(dataPasienPage_hapusData_pasienInfo), nama_label);

        snprintf(info, sizeof(info), "Alamat: %s", dataHolder.alamat);
        GtkWidget *alamat_label = gtk_label_new(info);
        gtk_box_append(GTK_BOX(dataPasienPage_hapusData_pasienInfo), alamat_label);

        snprintf(info, sizeof(info), "Kota: %s", dataHolder.kota);
        GtkWidget *kota_label = gtk_label_new(info);
        gtk_box_append(GTK_BOX(dataPasienPage_hapusData_pasienInfo), kota_label);

        snprintf(info, sizeof(info), "Tempat Lahir: %s", dataHolder.tempatLahir);
        GtkWidget *tempat_lahir_label = gtk_label_new(info);
        gtk_box_append(GTK_BOX(dataPasienPage_hapusData_pasienInfo), tempat_lahir_label);

        snprintf(info, sizeof(info), "Tanggal Lahir: %02d-%02d-%04d", dataHolder.tanggalLahir.tanggal, dataHolder.tanggalLahir.bulan, dataHolder.tanggalLahir.tahun);
        GtkWidget *tanggal_lahir_label = gtk_label_new(info);
        gtk_box_append(GTK_BOX(dataPasienPage_hapusData_pasienInfo), tanggal_lahir_label);

        snprintf(info, sizeof(info), "Umur: %d", dataHolder.umur);
        GtkWidget *umur_label = gtk_label_new(info);
        gtk_box_append(GTK_BOX(dataPasienPage_hapusData_pasienInfo), umur_label);

        snprintf(info, sizeof(info), "Nomor BPJS: %s", dataHolder.nomorBPJS);
        GtkWidget *bpjs_label = gtk_label_new(info);
        gtk_box_append(GTK_BOX(dataPasienPage_hapusData_pasienInfo), bpjs_label);

        GtkWidget *hapus_button = gtk_button_new_with_label("Hapus Data");
        gtk_widget_set_halign(hapus_button, GTK_ALIGN_CENTER);
        gtk_box_append(GTK_BOX(dataPasienPage_hapusData_pasienInfo), hapus_button);

        char *tempIdPasien = strdup(dataHolder.IdPasien);
        g_signal_connect(hapus_button, "clicked", G_CALLBACK(on_confirm_hapusData_pasien_page), tempIdPasien);
    }
    else
    {
        GtkWidget *not_found_label = gtk_label_new("Data Pasien tidak ditemukan");
        gtk_box_append(GTK_BOX(dataPasienPage_hapusData_pasienInfo), not_found_label);
    }

    GtkWidget *back_button = gtk_button_new_with_label("Back");
    gtk_widget_set_halign(back_button, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(dataPasienPage_hapusData_pasienInfo), back_button);
    DataCallBack *callBack = g_malloc(sizeof(DataCallBack));
    callBack->stackContainer = dataPasienPage_Stack;
    callBack->page_name = "MainGrid";
    g_signal_connect(back_button, "clicked", G_CALLBACK(on_back_hapusDataPasien_gui), callBack);
}

GtkWidget *DataPasienPage_HapusData()
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

    dataPasienPage_hapusData_pasienInfo = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_append(GTK_BOX(page), dataPasienPage_hapusData_pasienInfo);

    g_signal_connect(button, "clicked", G_CALLBACK(on_cari_pasienData_hapusData_gui), entry);

    GtkWidget *back_button = gtk_button_new_with_label("Back");
    gtk_widget_set_halign(back_button, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(dataPasienPage_hapusData_pasienInfo), back_button);
    DataCallBack *callBack = g_malloc(sizeof(DataCallBack));
    callBack->stackContainer = dataPasienPage_Stack;
    callBack->page_name = "MainGrid";
    g_signal_connect(back_button, "clicked", G_CALLBACK(on_back_hapusDataPasien_gui), callBack);

    return page;
}

// BASE PAGE
GtkWidget *DataPasienPage()
{
    GtkWidget *page = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    GtkWidget *header = addHeader(page);

    dataPasienPage_Stack = gtk_stack_new();
    gtk_stack_set_transition_type(GTK_STACK(dataPasienPage_Stack), GTK_STACK_TRANSITION_TYPE_SLIDE_LEFT_RIGHT);

    gtk_box_append(GTK_BOX(page), dataPasienPage_Stack);

    GtkWidget *mainGrid = gtk_grid_new();
    gtk_stack_add_named(GTK_STACK(dataPasienPage_Stack), mainGrid, "MainGrid");

    GtkWidget *mainContent = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_grid_attach(GTK_GRID(mainGrid), mainContent, 1, 1, 1, 1);
    gtk_widget_set_size_request(mainContent, WINDOW_WIDTH, WINDOW_HEIGHT - HEADER_HEIGHT - FOOTER_HEIGHT);
    gtk_widget_set_valign(mainContent, GTK_ALIGN_CENTER);

    GtkWidget *baseGrid = gtk_grid_new();
    gtk_widget_set_size_request(baseGrid, WINDOW_WIDTH, -1);
    gtk_widget_set_vexpand(baseGrid, TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(baseGrid), TRUE);
    gtk_grid_set_row_homogeneous(GTK_GRID(baseGrid), TRUE);
    gtk_box_append(GTK_BOX(mainContent), baseGrid);

    GtkWidget *leftHalf = gtk_center_box_new();
    GtkWidget *leftLabel = gtk_label_new("Data Pasien");
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
    char *button_labels[4] = {"Cari Data Pasien", "Tambah Data Pasien", "Ubah Data Pasien", "Hapus Data Pasien"};
    char *page_names[4] = {"CariDataPasien", "TambahDataPasien", "UbahDataPasien", "HapusDataPasien"};

    for (int i = 0; i < 4; i++)
    {
        funcButton[i] = gtk_button_new_with_label(button_labels[i]);
        gtk_grid_attach(GTK_GRID(rightHalfButton), funcButton[i], 0, i, 1, 1);
        gtk_widget_set_size_request(funcButton[i], 150, 50);
    }

    gtk_grid_attach(GTK_GRID(baseGrid), leftHalf, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(baseGrid), rightHalf, 1, 0, 1, 1);

    // Center the mainContent
    gtk_grid_set_column_spacing(GTK_GRID(mainGrid), 0);
    gtk_grid_set_row_spacing(GTK_GRID(mainGrid), 0);
    gtk_grid_set_column_homogeneous(GTK_GRID(mainGrid), TRUE);
    gtk_grid_set_row_homogeneous(GTK_GRID(mainGrid), TRUE);

    // Cari Data Page
    GtkWidget *dataPasienPage_cariData = DataPasienPage_CariData();
    gtk_stack_add_named(GTK_STACK(dataPasienPage_Stack), dataPasienPage_cariData, page_names[0]);
    DataCallBack *callBack = g_malloc(sizeof(DataCallBack));
    callBack->stackContainer = dataPasienPage_Stack;
    callBack->page_name = page_names[0];
    g_signal_connect(funcButton[0], "clicked", G_CALLBACK(on_button_clicked_with_page), callBack);

    // Tambah Data Page
    GtkWidget *dataPasienPage_tambahData = DataPasienPage_TambahData();
    gtk_stack_add_named(GTK_STACK(dataPasienPage_Stack), dataPasienPage_tambahData, page_names[1]);
    callBack = g_malloc(sizeof(DataCallBack));
    callBack->stackContainer = dataPasienPage_Stack;
    callBack->page_name = page_names[1];
    g_signal_connect(funcButton[1], "clicked", G_CALLBACK(on_button_clicked_with_page), callBack);

    // Ubah Data Page
    GtkWidget *dataPasienPage_ubahData = DataPasienPage_UbahData();
    gtk_stack_add_named(GTK_STACK(dataPasienPage_Stack), dataPasienPage_ubahData, page_names[2]);
    callBack = g_malloc(sizeof(DataCallBack));
    callBack->stackContainer = dataPasienPage_Stack;
    callBack->page_name = page_names[2];
    g_signal_connect(funcButton[2], "clicked", G_CALLBACK(on_button_clicked_with_page), callBack);

    // Hapus Data Page
    GtkWidget *dataPasienPage_hapusData = DataPasienPage_HapusData();
    gtk_stack_add_named(GTK_STACK(dataPasienPage_Stack), dataPasienPage_hapusData, page_names[3]);
    callBack = g_malloc(sizeof(DataCallBack));
    callBack->stackContainer = dataPasienPage_Stack;
    callBack->page_name = page_names[3];
    g_signal_connect(funcButton[3], "clicked", G_CALLBACK(on_button_clicked_with_page), callBack);

    GtkWidget *footer = addFooter(page);
    return page;
}
