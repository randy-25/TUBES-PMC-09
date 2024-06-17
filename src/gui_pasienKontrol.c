#include "../header/gui_pasienKontrol.h"

void reset_pasienKontrolPage_info()
{
    GtkWidget *child = gtk_widget_get_first_child(GTK_WIDGET(informasiPasienKontrolPage_pasienInfo));
    while (child != NULL)
    {
        GtkWidget *next = gtk_widget_get_next_sibling(child);
        gtk_box_remove(GTK_BOX(informasiPasienKontrolPage_pasienInfo), child);
        child = next;
    }
}

void on_clicked_footer_pasienKontrolPage(GtkButton *button, gpointer user_data)
{
    reset_pasienKontrolPage_info();
    DataCallBack *data = (DataCallBack *)user_data;
    gtk_stack_set_visible_child_name(GTK_STACK(data->stackContainer), data->page_name);
}

GtkWidget *PasienKontrol_footer_with_reset(GtkWidget *page)
{
    GtkWidget *fixed = gtk_fixed_new();
    gtk_box_append(GTK_BOX(page), fixed);

    GtkWidget *footer = gtk_button_new_with_label("Back to Landing Page");
    gtk_fixed_put(GTK_FIXED(fixed), footer, 0, FOOTER_HEIGHT);
    DataCallBack *data = (DataCallBack *)malloc(sizeof(DataCallBack));
    data->stackContainer = stackContainer;
    data->page_name = "LandingPage";
    g_signal_connect(footer, "clicked", G_CALLBACK(on_clicked_footer_pasienKontrolPage), data);
    return fixed;
}

void on_cari_pasienKontrol_data_gui(GtkButton *button, gpointer user_data)
{
    reset_pasienKontrolPage_info();
    GtkWidget *data = user_data;
    const gchar *tanggalKontrol = gtk_editable_get_text(GTK_EDITABLE(data));
    char *tempTanggalKontrol = strdup(tanggalKontrol);

    struct tanggal tanggalPasienKontrol;

    // clear the input entry
    const gchar *default_text = "";
    gtk_editable_set_text(GTK_EDITABLE(data), default_text);
    gtk_editable_set_position(GTK_EDITABLE(data), strlen(default_text));

    parseTanggal(tempTanggalKontrol, &(tanggalPasienKontrol.tanggal), &(tanggalPasienKontrol.bulan), &(tanggalPasienKontrol.tahun));

    struct DataPasienKontrol *dataPasienKontrolHolder = NULL;
    int jumlahDataPasienKontrolHolder = 0;

    pasienKontrol(pasien, jumlahPasien, riwayatPasien, jumlahRiwayatPasien, tanggalPasienKontrol, &dataPasienKontrolHolder, &jumlahDataPasienKontrolHolder);

    GtkWidget *infoBox;
    if (jumlahDataPasienKontrolHolder != 0)
    {
        char info[256];
        infoBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

        GtkWidget *title = gtk_label_new("Informasi Kontrol Pasien");

        snprintf(info, sizeof(info), "Tanggal: %02d-%02d-%04d\n", tanggalPasienKontrol.tanggal, tanggalPasienKontrol.bulan, tanggalPasienKontrol.tahun);
        GtkWidget *tanggal_kontrol_label = gtk_label_new(info);
        gtk_box_append(GTK_BOX(infoBox), tanggal_kontrol_label);

        for (int i = 0; i < jumlahDataPasienKontrolHolder; i++)
        {
            struct DataPasienKontrol *current = &dataPasienKontrolHolder[i];

            char buffer[256];
            snprintf(buffer, sizeof(buffer), "ID Pasien: %s\nNama: %s\nTanggal Periksa: %d-%d-%d\nDiagnosis: %s\nTindakan: %s\nBiaya: %d",
                     current->IdPasien,
                     current->nama,
                     current->tanggalPeriksa.tanggal, current->tanggalPeriksa.bulan, current->tanggalPeriksa.tahun,
                     current->diagnosis,
                     current->tindakan,
                     current->biaya);

            GtkWidget *riwayat_label = gtk_label_new(buffer);
            gtk_box_append(GTK_BOX(infoBox), riwayat_label);
            GtkWidget *label = gtk_label_new("-------------------------------------------------");
            gtk_box_append(GTK_BOX(infoBox), label);
        }
        GtkWidget *scrolled_window = gtk_scrolled_window_new();
        gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window), infoBox);

        gtk_widget_set_size_request(scrolled_window, WINDOW_WIDTH / 2, 300);
        gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
        gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window), infoBox);

        gtk_box_append(GTK_BOX(informasiPasienKontrolPage_pasienInfo), scrolled_window);
    }
    else
    {
        GtkWidget *not_found_label = gtk_label_new("Tidak ada pasien yang melakukan kontrol");
        gtk_box_append(GTK_BOX(informasiPasienKontrolPage_pasienInfo), not_found_label);
    }
}

GtkWidget *PasienKontrolPage()
{
    GtkWidget *page;
    GtkWidget *entry;
    GtkWidget *button;

    page = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    GtkWidget *header = addHeader(page);

    GtkWidget *title = gtk_label_new("Informasi Kontrol Pasien");
    gtk_box_append(GTK_BOX(page), title);
    gtk_widget_set_halign(title, GTK_ALIGN_CENTER);

    entry = gtk_entry_new();
    GtkWidget *formLabel = gtk_label_new("Masukkan Tanggal Kontrol Yang Ingin Di Periksa (DD-MM-YYYY) : ");

    gtk_box_append(GTK_BOX(page), formLabel);
    gtk_box_append(GTK_BOX(page), entry);

    button = gtk_button_new_with_label("Cari");
    gtk_widget_set_halign(button, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(page), button);

    informasiPasienKontrolPage_pasienInfo = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_size_request(informasiPasienKontrolPage_pasienInfo, WINDOW_WIDTH, 450);
    gtk_box_append(GTK_BOX(page), informasiPasienKontrolPage_pasienInfo);

    g_signal_connect(button, "clicked", G_CALLBACK(on_cari_pasienKontrol_data_gui), entry);
    GtkWidget *footer = PasienKontrol_footer_with_reset(page);
    return page;
}