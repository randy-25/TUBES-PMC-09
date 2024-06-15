#include "../header/util_laporanPendapatanUtil.h"

int cekdataPendapatanTahun (int *daftarTahun, int Tahun)
{
    for (int i = 0; i < 50; i++){
        if (daftarTahun[i] == Tahun){
            return 0;
        }
    }
    return 1; //1 jika belum terdata
}

void tambahPendapatan (struct pendapatanTahun **data, int bulan, int index, int pendapatan)
{
    struct pendapatanTahun *curr = *data;

    if (bulan == 1){
        curr[index].bulan->jan = curr[index].bulan->jan + pendapatan;
    }
    else if (bulan == 2){
        curr[index].bulan->feb = curr[index].bulan->feb + pendapatan;
    }
    else if (bulan == 3){
        curr[index].bulan->mar = curr[index].bulan->mar + pendapatan;
    }
    else if (bulan == 4){
        curr[index].bulan->apr = curr[index].bulan->apr + pendapatan;
    }
    else if (bulan == 5){
        curr[index].bulan->mei = curr[index].bulan->mei + pendapatan;
    }
    else if (bulan == 6){
        curr[index].bulan->jun = curr[index].bulan->jun + pendapatan;
    }
    else if (bulan == 7){
        curr[index].bulan->jul = curr[index].bulan->jul + pendapatan;
    }
    else if (bulan == 8){
        curr[index].bulan->agu = curr[index].bulan->agu + pendapatan;
    }
    else if (bulan == 9){
        curr[index].bulan->sep = curr[index].bulan->sep + pendapatan;
    }
    else if (bulan == 10){
        curr[index].bulan->okt = curr[index].bulan->okt + pendapatan;
    }
    else if (bulan == 11){
        curr[index].bulan->nov = curr[index].bulan->nov + pendapatan;
    }
    else if (bulan == 12){
        curr[index].bulan->des = curr[index].bulan->des + pendapatan;
    }
    curr[index].jumlahperTahun = curr[index].jumlahperTahun + pendapatan;
}

void LaporanPendapatan (struct riwayat *RiwayatPasien, int jumlahRiwayatPasien)
{

    int daftarTahun[50]; //membatasi jumlah tahun yang dapat didata

    int indexTahun = 0;

    int tahunterdata = 0;
    int penyakitterdata = 0;

    for (int i = 0; i < jumlahRiwayatPasien; i++){
        tahunterdata = cekdataPendapatanTahun(daftarTahun, RiwayatPasien[i].tanggalPeriksa.tahun);

        if (tahunterdata == 1){
            daftarTahun[indexTahun] = RiwayatPasien[i].tanggalPeriksa.tahun;
            indexTahun++;
        }
    }
    int jumlahstruct = indexTahun;

    //asumsi riwayat pasien dipastikan ada
    struct pendapatanTahun *LaporanPendapatan = (pendapatanTahun*)malloc(jumlahstruct * sizeof(pendapatanTahun)); 

    int helper = 0;
 
    //inisiasi struct per tahun
    for (int i = 0; i < jumlahstruct; i++){
        LaporanPendapatan[i].tahun = daftarTahun[i];
        LaporanPendapatan[i].jumlahperTahun = 0;
        LaporanPendapatan[i].bulan = (PerBulan *)malloc(sizeof(PerBulan));
        memset(LaporanPendapatan[i].bulan, 0, sizeof(PerBulan));
    }
    

    //mulai pengisian data
    int temp;
    for (int k = 0; k < jumlahRiwayatPasien; k++){
        for (int l = 0; l < jumlahstruct; l++){
            if (RiwayatPasien[k].tanggalPeriksa.tahun == LaporanPendapatan[l].tahun){
                temp = l;
                tambahPendapatan(&LaporanPendapatan, RiwayatPasien[k].tanggalPeriksa.bulan, temp, RiwayatPasien[k].biaya);
            }
        }
    }

    //printdata
    int tahunprint = INT_MAX;
    int tempindex = 0;
    int validyear=0;
    

    printf ("Masukkan Tahun yang diinginkan : ");
    scanf("%d", &tahunprint);

    // Use getchar to consume the newline character left by scanf
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);

    for (int i = 0; i < indexTahun; i++)
    {
        if (daftarTahun[i] == tahunprint)
        {
            validyear = 1;
        }
    }
    
    if (validyear == 0)
    {
        printf("Tahun tidak valid / Tidak ada data\n");
        return;
    }
        //cari indeks tahun yang diinput
        for (int l = 0; l < jumlahstruct;l++){
            if (LaporanPendapatan[l].tahun == tahunprint){
                tempindex = l;
                break;
            }
        }

        printf("\n");
        printf("Tahun %d \n", tahunprint);

        printf("Januari %d : %d\n", tahunprint, LaporanPendapatan[tempindex].bulan->jan);
        printf("Februari %d : %d\n", tahunprint, LaporanPendapatan[tempindex].bulan->feb);
        printf("Maret %d : %d\n", tahunprint, LaporanPendapatan[tempindex].bulan->mar);
        printf("April %d : %d\n", tahunprint, LaporanPendapatan[tempindex].bulan->apr);
        printf("Mei %d : %d\n", tahunprint, LaporanPendapatan[tempindex].bulan->mei);
        printf("Juni %d : %d\n", tahunprint, LaporanPendapatan[tempindex].bulan->jun);
        printf("Juli %d : %d\n", tahunprint, LaporanPendapatan[tempindex].bulan->jul);
        printf("Agustus %d : %d\n", tahunprint, LaporanPendapatan[tempindex].bulan->agu);
        printf("September %d : %d\n", tahunprint, LaporanPendapatan[tempindex].bulan->sep);
        printf("Oktober %d : %d\n", tahunprint, LaporanPendapatan[tempindex].bulan->okt);
        printf("November %d : %d\n", tahunprint, LaporanPendapatan[tempindex].bulan->nov);
        printf("Desember %d : %d\n", tahunprint, LaporanPendapatan[tempindex].bulan->des);
        
        printf("TOTAL : %d\n", LaporanPendapatan[tempindex].bulan->des);
        printf("Rata-rata : %d\n", LaporanPendapatan[tempindex].bulan->des/12);


    //free alocationg memori
    for (int i = 0 ; i < jumlahstruct; i++){
        free(LaporanPendapatan[i].bulan);

    }
    free(LaporanPendapatan);
}