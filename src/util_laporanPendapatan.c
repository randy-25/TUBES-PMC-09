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
        curr[index].bulan.jan = curr[index].bulan.jan + pendapatan;
    }
    else if (bulan == 2){
        curr[index].bulan.feb = curr[index].bulan.feb + pendapatan;
    }
    else if (bulan == 3){
        curr[index].bulan.mar = curr[index].bulan.mar + pendapatan;
    }
    else if (bulan == 4){
        curr[index].bulan.apr = curr[index].bulan.apr + pendapatan;
    }
    else if (bulan == 5){
        curr[index].bulan.mei = curr[index].bulan.mei + pendapatan;
    }
    else if (bulan == 6){
        curr[index].bulan.jun = curr[index].bulan.jun + pendapatan;
    }
    else if (bulan == 7){
        curr[index].bulan.jul = curr[index].bulan.jul + pendapatan;
    }
    else if (bulan == 8){
        curr[index].bulan.agu = curr[index].bulan.agu + pendapatan;
    }
    else if (bulan == 9){
        curr[index].bulan.sep = curr[index].bulan.sep + pendapatan;
    }
    else if (bulan == 10){
        curr[index].bulan.okt = curr[index].bulan.okt + pendapatan;
    }
    else if (bulan == 11){
        curr[index].bulan.nov = curr[index].bulan.nov + pendapatan;
    }
    else if (bulan == 12){
        curr[index].bulan.des = curr[index].bulan.des + pendapatan;
    }
    curr[index].jumlahperTahun = curr[index].jumlahperTahun + pendapatan;
}

void LaporanPendapatan (struct riwayat *RiwayatPasien, int jumlahRiwayatPasien, struct pendapatanTahun **Hasil, int tahun, int *confirm)
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
        LaporanPendapatan[i].bulan.jan = 0;
        LaporanPendapatan[i].bulan.feb = 0;
        LaporanPendapatan[i].bulan.mar = 0;
        LaporanPendapatan[i].bulan.apr = 0;
        LaporanPendapatan[i].bulan.mei = 0;
        LaporanPendapatan[i].bulan.jun = 0;
        LaporanPendapatan[i].bulan.jul = 0;
        LaporanPendapatan[i].bulan.agu = 0;
        LaporanPendapatan[i].bulan.sep = 0;
        LaporanPendapatan[i].bulan.okt = 0;
        LaporanPendapatan[i].bulan.nov = 0;
        LaporanPendapatan[i].bulan.des = 0;
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
    int tempindex = 0;
    int validyear=0;

    for (int i = 0; i < jumlahstruct; i++)
    {
        if (tahun == daftarTahun[i]){
            validyear= 1;
            *confirm = 1;
        }
    }   
     
    if (validyear == 0)
    {
        *confirm = 0;
        return;
    }
        //cari indeks tahun yang diinput
        for (int l = 0; l < jumlahstruct;l++){
            if (LaporanPendapatan[l].tahun == tahun){
                tempindex = l;
                break;
            }
        }
        // printf()
        (*Hasil) = (pendapatanTahun*)malloc(sizeof(pendapatanTahun)); 
        (*Hasil)->bulan.jan = LaporanPendapatan[tempindex].bulan.jan;
        (*Hasil)->bulan.feb = LaporanPendapatan[tempindex].bulan.feb;
        (*Hasil)->bulan.mar = LaporanPendapatan[tempindex].bulan.mar;
        (*Hasil)->bulan.apr = LaporanPendapatan[tempindex].bulan.apr;
        (*Hasil)->bulan.mei = LaporanPendapatan[tempindex].bulan.mei;
        (*Hasil)->bulan.jun = LaporanPendapatan[tempindex].bulan.jun;
        (*Hasil)->bulan.jul = LaporanPendapatan[tempindex].bulan.jul;
        (*Hasil)->bulan.agu = LaporanPendapatan[tempindex].bulan.agu;
        (*Hasil)->bulan.sep = LaporanPendapatan[tempindex].bulan.sep;
        (*Hasil)->bulan.okt = LaporanPendapatan[tempindex].bulan.okt;
        (*Hasil)->bulan.nov = LaporanPendapatan[tempindex].bulan.nov;
        (*Hasil)->bulan.des = LaporanPendapatan[tempindex].bulan.des;
        (*Hasil)->jumlahperTahun = LaporanPendapatan[tempindex].jumlahperTahun;
        (*Hasil)->tahun = LaporanPendapatan[tempindex].tahun;

        //debug
        // printf("Januari %d : %d\n", tahun, LaporanPendapatan[tempindex].bulan.jan);
        // printf("Februari %d : %d\n", tahun, LaporanPendapatan[tempindex].bulan.feb);
        // printf("Maret %d : %d\n", tahun, LaporanPendapatan[tempindex].bulan.mar);
        // printf("April %d : %d\n", tahun, LaporanPendapatan[tempindex].bulan.apr);
        // printf("Mei %d : %d\n", tahun, LaporanPendapatan[tempindex].bulan.mei);
        // printf("Juni %d : %d\n", tahun, LaporanPendapatan[tempindex].bulan.jun);
        // printf("Juli %d : %d\n", tahun, LaporanPendapatan[tempindex].bulan.jul);
        // printf("Agustus %d : %d\n", tahun, LaporanPendapatan[tempindex].bulan.agu);
        // printf("September %d : %d\n", tahun, LaporanPendapatan[tempindex].bulan.sep);
        // printf("Oktober %d : %d\n", tahun, LaporanPendapatan[tempindex].bulan.okt);
        // printf("November %d : %d\n", tahun, LaporanPendapatan[tempindex].bulan.nov);
        // printf("Desember %d : %d\n", tahun, LaporanPendapatan[tempindex].bulan.des);
        
        // printf("TOTAL : %d\n", LaporanPendapatan[tempindex].bulan->des);
        // printf("Rata-rata : %d\n", LaporanPendapatan[tempindex].bulan->des/12);


    //free alocationg memori
    free(LaporanPendapatan);
}