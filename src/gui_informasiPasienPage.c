#include "../header/gui_informasiPasienPage.h"

// Informasi Pasien Page

void reset_informasiPasienPage_info()
{
    GtkWidget *child = gtk_widget_get_first_child(GTK_WIDGET(informasiPasienPage_pasienInfo));
    while (child != NULL)
    {
        GtkWidget *next = gtk_widget_get_next_sibling(child);
        gtk_box_remove(GTK_BOX(informasiPasienPage_pasienInfo), child);
        child = next;
    }
}

void on_clicked_footer_informasiPasienPage(GtkButton *button, gpointer user_data)
{
    reset_informasiPasienPage_info();
    DataCallBack *data = (DataCallBack *)user_data;
    gtk_stack_set_visible_child_name(GTK_STACK(data->stackContainer), data->page_name);
}   

GtkWidget *InformasiPasien_footer_with_reset(GtkWidget *page)
{
    GtkWidget *fixed = gtk_fixed_new();
    gtk_box_append(GTK_BOX(page), fixed);

    GtkWidget *footer = gtk_button_new_with_label("Back to Landing Page");
    gtk_fixed_put(GTK_FIXED(fixed), footer, 0, FOOTER_HEIGHT);
    DataCallBack *data = (DataCallBack *)malloc(sizeof(DataCallBack));
    data->stackContainer = stackContainer;
    data->page_name = "LandingPage";
    g_signal_connect(footer, "clicked", G_CALLBACK(on_clicked_footer_informasiPasienPage), data);
    return fixed;
}

void on_cari_informasiPasien_data_gui(GtkButton *button, gpointer user_data)
{
    reset_informasiPasienPage_info();
    GtkWidget *data = user_data;
    const gchar *entry_idPasien = gtk_editable_get_text(GTK_EDITABLE(data));
    ;

    char *idPasien = strdup(entry_idPasien);

    // clear the input entry
    const gchar *default_text = "KX ";
    gtk_editable_set_text(GTK_EDITABLE(data), default_text);
    gtk_editable_set_position(GTK_EDITABLE(data), strlen(default_text));

    struct dataPasien dataHolder;
    int confirmData;
    cariPasien(pasien, jumlahPasien, idPasien, &dataHolder, &confirmData);

    struct riwayat *riwayatHolder = NULL;
    int jumlahRiwayatHolder = 0;
    int confirmRiwayat;
    char *nameHolder;
    cariRiwayat(riwayatPasien, jumlahRiwayatPasien, idPasien, &riwayatHolder, &jumlahRiwayatHolder, &confirmRiwayat, &nameHolder, pasien, jumlahPasien);

    if (confirmData && confirmRiwayat)
    {
        GtkWidget *baseGrid = gtk_grid_new();
        gtk_widget_set_size_request(baseGrid, WINDOW_WIDTH, 300);
        gtk_widget_set_vexpand(baseGrid, TRUE);
        gtk_grid_set_column_homogeneous(GTK_GRID(baseGrid), TRUE);
        gtk_grid_set_row_homogeneous(GTK_GRID(baseGrid), TRUE);
        gtk_box_append(GTK_BOX(informasiPasienPage_pasienInfo), baseGrid);

        GtkWidget *leftHalf = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

        GtkWidget *leftLabel = gtk_label_new("Data Pasien");
        gtk_box_append(GTK_BOX(leftHalf), leftLabel);
        // gtk_center_box_set_center_widget(GTK_CENTER_BOX(leftHalf), leftLabel);
        gtk_grid_attach(GTK_GRID(baseGrid), leftHalf, 0, 0, 1, 1);

        // Create new labels to display the data
        char info[256]; // Ensure that the buffer is large enough

        snprintf(info, sizeof(info), "ID Pasien: %s", dataHolder.IdPasien);
        GtkWidget *id_label = gtk_label_new(info);
        gtk_box_append(GTK_BOX(leftHalf), id_label);

        snprintf(info, sizeof(info), "Nama: %s", dataHolder.nama);
        GtkWidget *nama_label = gtk_label_new(info);
        gtk_box_append(GTK_BOX(leftHalf), nama_label);

        snprintf(info, sizeof(info), "Alamat: %s", dataHolder.alamat);
        GtkWidget *alamat_label = gtk_label_new(info);
        gtk_box_append(GTK_BOX(leftHalf), alamat_label);

        snprintf(info, sizeof(info), "Kota: %s", dataHolder.kota);
        GtkWidget *kota_label = gtk_label_new(info);
        gtk_box_append(GTK_BOX(leftHalf), kota_label);

        snprintf(info, sizeof(info), "Tempat Lahir: %s", dataHolder.tempatLahir);
        GtkWidget *tempat_lahir_label = gtk_label_new(info);
        gtk_box_append(GTK_BOX(leftHalf), tempat_lahir_label);

        snprintf(info, sizeof(info), "Tanggal Lahir: %02d-%02d-%04d", dataHolder.tanggalLahir.tanggal, dataHolder.tanggalLahir.bulan, dataHolder.tanggalLahir.tahun);
        GtkWidget *tanggal_lahir_label = gtk_label_new(info);
        gtk_box_append(GTK_BOX(leftHalf), tanggal_lahir_label);

        snprintf(info, sizeof(info), "Umur: %d", dataHolder.umur);
        GtkWidget *umur_label = gtk_label_new(info);
        gtk_box_append(GTK_BOX(leftHalf), umur_label);

        snprintf(info, sizeof(info), "Nomor BPJS: %s", dataHolder.nomorBPJS);
        GtkWidget *bpjs_label = gtk_label_new(info);
        gtk_box_append(GTK_BOX(leftHalf), bpjs_label);

        // right half of the page
        GtkWidget *rightHalf = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

        for (int i = 0; i < jumlahRiwayatHolder; i++)
        {
            struct riwayat *current = &riwayatHolder[i];

            char buffer[256];
            snprintf(buffer, sizeof(buffer), "No: %d\nTanggal Periksa: %d-%d-%d\nDiagnosis: %s\nTindakan: %s\nTanggal Kontrol: %d-%d-%d\nBiaya: %d",
                     current->no,
                     current->tanggalPeriksa.tanggal, current->tanggalPeriksa.bulan, current->tanggalPeriksa.tahun,
                     current->diagnosis,
                     current->tindakan,
                     current->tanggalKontrol.tanggal, current->tanggalKontrol.bulan, current->tanggalKontrol.tahun,
                     current->biaya);

            GtkWidget *riwayat_label = gtk_label_new(buffer);
            gtk_box_append(GTK_BOX(rightHalf), riwayat_label);
            GtkWidget *label = gtk_label_new("-------------------------------------------------");
            gtk_box_append(GTK_BOX(rightHalf), label);
        }
        GtkWidget *rightHalf_scrolled_window = gtk_scrolled_window_new();
        gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(rightHalf_scrolled_window), rightHalf);

        gtk_widget_set_size_request(rightHalf_scrolled_window, WINDOW_WIDTH / 2, 150);
        gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(rightHalf_scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
        gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(rightHalf_scrolled_window), rightHalf);
        gtk_grid_attach(GTK_GRID(baseGrid), rightHalf_scrolled_window, 1, 0, 1, 1);
    }
    else{
        GtkWidget *not_found_label = gtk_label_new("Data Pasien tidak ditemukan");
        gtk_box_append(GTK_BOX(informasiPasienPage_pasienInfo), not_found_label);
    }
}

GtkWidget *InformasiPasienPage()
{
    GtkWidget *page;
    GtkWidget *entry;
    GtkWidget *button;

    page = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    GtkWidget *header = addHeader(page);

    GtkWidget *title = gtk_label_new("Informasi Pasien");
    gtk_box_append(GTK_BOX(page), title);
    gtk_widget_set_halign(title, GTK_ALIGN_CENTER);

    entry = gtk_entry_new();
    GtkWidget *formLabel = gtk_label_new("Masukkan ID Pasien : ");

    const gchar *default_text = "KX ";
    gtk_editable_set_text(GTK_EDITABLE(entry), default_text);
    gtk_editable_set_position(GTK_EDITABLE(entry), strlen(default_text));

    gtk_box_append(GTK_BOX(page), formLabel);
    gtk_box_append(GTK_BOX(page), entry);

    button = gtk_button_new_with_label("Cari");
    gtk_widget_set_halign(button, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(page), button);

    informasiPasienPage_pasienInfo = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_size_request(informasiPasienPage_pasienInfo, WINDOW_WIDTH, 450);
    gtk_box_append(GTK_BOX(page), informasiPasienPage_pasienInfo);

    g_signal_connect(button, "clicked", G_CALLBACK(on_cari_informasiPasien_data_gui), entry);
    GtkWidget *footer = InformasiPasien_footer_with_reset(page);
    return page;
}