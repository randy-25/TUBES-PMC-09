#include "../header/util_saveData.h"

const char* getMonthName_CSV(int month)
{
    // Array of month names in Indonesian
    const char *monthsIndonesian[] = {"Januari", "Februari", "Maret", "April", "Mei", "Juni", 
                                      "Juli", "Agustus", "September", "Oktober", "November", "Desember"};

    if (month < 1 || month > 12) {
        return "Invalid month";  // Return an error message for invalid month numbers
    }
    return monthsIndonesian[month - 1];  // Return the Indonesian month name
}

// Function to write dataPasien to CSV
void write_DataPasien_CSV(const struct dataPasien *Data, int JumlahDataPasien)
{
    FILE *file = fopen("data/Data Pasien.csv", "w");
    if (file == NULL)
    {
        printf("Failed to open file for writing.\n");
        return;
    }

    // Write each patient's data
    for (int i = 0; i < JumlahDataPasien; i++)
    {
        const struct dataPasien *current = &Data[i];
        fprintf(file, "%d,%s,%s,%s,%s,%d %s %d,%d,%s,%s\n",
                current->no,
                current->nama,
                current->alamat,
                current->kota,
                current->tempatLahir,
                current->tanggalLahir.tanggal,
                getMonthName_CSV(current->tanggalLahir.bulan),
                current->tanggalLahir.tahun,
                current->umur,
                current->nomorBPJS,
                current->IdPasien);
    }

    fclose(file);
    // printf("DataPasien successfully written to %s\n", filename);
}


// Function to write riwayat to CSV
void write_RiwayatPasien_CSV(const struct riwayat *RiwayatPasien, int JumlahRiwayatPasien)
{
    FILE *file = fopen("data/Riwayat Pasien.csv", "w");
    if (file == NULL)
    {
        printf("Failed to open file for writing.\n");
        return;
    }

    // Write each patient's history
    for (int i = 0; i < JumlahRiwayatPasien; i++)
    {
        const struct riwayat *current = &RiwayatPasien[i];
        fprintf(file, "%d,%d %s %d,%s,%s,%d %s %d,%d\n",
                current->no,
                current->tanggalPeriksa.tanggal,
                getMonthName_CSV(current->tanggalPeriksa.bulan),
                current->tanggalPeriksa.tahun,
                current->IdPasien,
                current->diagnosis,
                current->tindakan,
                current->tanggalKontrol.tanggal,
                getMonthName_CSV(current->tanggalKontrol.bulan),
                current->tanggalKontrol.tahun,
                current->biaya);
    }

    fclose(file);
    // printf("RiwayatPasien successfully written to %s\n", filename);
}


