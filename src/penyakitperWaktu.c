#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../header/getData.h"
#include "../header/penyakitperWaktuUtil.h"

//cek apakah data tahun sudah terdata, jika belum kembalikan nilai 1
int cekdataTahun (int *daftarTahun, int Tahun){
    for (int i = 0; i < 50; i++){
        if (daftarTahun[i] == Tahun){
            return 0;
        }
    }
    return 1;
}

//cek apakah data penyakit sudah terdata, jika belum kembalikan nilai 1
int cekdataPenyakit (char (*daftarPenyakit)[50], char penyakit[50]){
    for (int i = 0; i < 50; i++){
        if (strcmp(daftarPenyakit[i], penyakit) == 0){
            return 0;
        }
    }
    return 1;
}

void tambahData (struct perTahun **data, int bulan, int index){
    struct perTahun *curr = *data;

    if (bulan == 1){
        curr[index].bulan->jan = curr[index].bulan->jan + 1;
    }
    else if (bulan == 2){
        curr[index].bulan->feb = curr[index].bulan->feb + 1;
    }
    else if (bulan == 3){
        curr[index].bulan->mar = curr[index].bulan->mar + 1;
    }
    else if (bulan == 4){
        curr[index].bulan->apr = curr[index].bulan->apr + 1;
    }
    else if (bulan == 5){
        curr[index].bulan->mei = curr[index].bulan->mei + 1;
    }
    else if (bulan == 6){
        curr[index].bulan->jun = curr[index].bulan->jun + 1;
    }
    else if (bulan == 7){
        curr[index].bulan->jul = curr[index].bulan->jul + 1;
    }
    else if (bulan == 8){
        curr[index].bulan->agu = curr[index].bulan->agu + 1;
    }
    else if (bulan == 9){
        curr[index].bulan->sep = curr[index].bulan->sep + 1;
    }
    else if (bulan == 10){
        curr[index].bulan->okt = curr[index].bulan->okt + 1;
    }
    else if (bulan == 11){
        curr[index].bulan->nov = curr[index].bulan->nov + 1;
    }
    else if (bulan == 12){
        curr[index].bulan->des = curr[index].bulan->des + 1;
    }
    curr[index].jumlahperTahun = curr[index].jumlahperTahun +1;
}

void DataPenyakitperWaktu (struct riwayat *RiwayatPasien, int jumlahRiwayatPasien){

    int daftarTahun[50]; //membatasi jumlah tahun yang dapat didata
    char daftarPenyakit[50][50]; //membatasi jumlah penyakit yang terdiagnosis

    int indexTahun = 0;
    int indexPenyakit = 0;

    int tahunterdata = 0;
    int penyakitterdata = 0;

    for (int i = 0; i < jumlahRiwayatPasien; i++){
        tahunterdata = cekdataTahun(daftarTahun, RiwayatPasien[i].tanggalPeriksa.tahun);
        penyakitterdata = cekdataPenyakit(daftarPenyakit, RiwayatPasien[i].diagnosis);

        if (tahunterdata == 1){
            daftarTahun[indexTahun] = RiwayatPasien[i].tanggalPeriksa.tahun;
            indexTahun++;
        }

        if (penyakitterdata == 1){
            strcpy(daftarPenyakit[indexPenyakit], RiwayatPasien[i].diagnosis);
            indexPenyakit++;
        }
    }

    int jumlahstruct = indexPenyakit*indexTahun;
    //asumsi riwayat pasien dipastikan ada
    struct perTahun *PenyakitperWaktu = (perTahun*)malloc(jumlahstruct * sizeof(perTahun)); 

    int helper = 0;
 
    //buat struct untuk setiap penyakit per tahun
    for (int i = 0; i < indexTahun; i++){
        for (int j = 0; j < indexPenyakit; j++){
            PenyakitperWaktu[helper].tahun = daftarTahun[i];
            PenyakitperWaktu[helper].penyakit = strdup(daftarPenyakit[j]);
            PenyakitperWaktu[helper].jumlahperTahun = 0;
            PenyakitperWaktu[helper].bulan = (PerBulan *)malloc(sizeof(PerBulan));

            memset(PenyakitperWaktu[helper].bulan, 0, sizeof(PerBulan));
            helper++;
        }
    }

    //mulai pengisian data
    int temp;
    for (int k = 0; k < jumlahRiwayatPasien; k++){
        for (int l = 0; l < jumlahstruct; l++){
            if (strcmp(RiwayatPasien[k].diagnosis, PenyakitperWaktu[l].penyakit) == 0 && RiwayatPasien[k].tanggalPeriksa.tahun == PenyakitperWaktu[l].tahun){
                temp = l;
                tambahData(&PenyakitperWaktu, RiwayatPasien[k].tanggalPeriksa.bulan, temp);
            }
        }
    }

    //printdata
    int tahunprint = INT_MAX;
    int tempindextahun = 0;
    int tempjumlah = 0;
    int tempindex = 0;
    

    //dimulai dengan mencari tahun terkecil
    for (int i = 0; i < indexTahun; i++){
        tahunprint = INT_MAX;
        //mencari tahun terkecil
        for (int j = 0; j < indexTahun; j++){
            if (tahunprint > daftarTahun[j] && daftarTahun[j] != 0){
                tahunprint = daftarTahun[j];
                tempindextahun = j;
            }
        }
        daftarTahun[tempindextahun] = INT_MAX;
        printf("\n");
        printf("Tahun %d \n", tahunprint);

        printf("Januari %d : \n", tahunprint);

        for (int k = 0; k < indexPenyakit; k++){
            for (int l = 0; l < jumlahstruct;l++){
                if (tempjumlah < PenyakitperWaktu[l].bulan->jan && PenyakitperWaktu[l].bulan->jan != INT_MAX && PenyakitperWaktu[l].tahun == tahunprint){
                    tempindex = l;
                    tempjumlah = PenyakitperWaktu[l].bulan->jan;
                }
            }
            PenyakitperWaktu[tempindex].bulan->jan = INT_MAX;
            printf("%s : %d \n", PenyakitperWaktu[tempindex].penyakit, tempjumlah);
            tempjumlah = -99;
            tempindex = 0;
        }
        
        printf("\n");
        printf("Februari %d : \n", tahunprint);
        for (int k = 0; k < indexPenyakit; k++){
            for (int l = 0; l < jumlahstruct;l++){
                if (tempjumlah < PenyakitperWaktu[l].bulan->feb && PenyakitperWaktu[l].bulan->feb != INT_MAX && PenyakitperWaktu[l].tahun == tahunprint){
                    tempindex = l;
                    tempjumlah = PenyakitperWaktu[l].bulan->feb;
                }
            }
            PenyakitperWaktu[tempindex].bulan->feb = INT_MAX;
            printf("%s : %d \n", PenyakitperWaktu[tempindex].penyakit, tempjumlah);
            tempjumlah = -99;
            tempindex = 0;
        }

        printf("\n");
        printf("Maret %d : \n", tahunprint);
        for (int k = 0; k < indexPenyakit; k++){
            for (int l = 0; l < jumlahstruct;l++){
                if (tempjumlah < PenyakitperWaktu[l].bulan->mar && PenyakitperWaktu[l].bulan->mar != INT_MAX && PenyakitperWaktu[l].tahun == tahunprint){
                    tempindex = l;
                    tempjumlah = PenyakitperWaktu[l].bulan->mar;
                }
            }
            PenyakitperWaktu[tempindex].bulan->mar = INT_MAX;
            printf("%s : %d \n", PenyakitperWaktu[tempindex].penyakit, tempjumlah);
            tempjumlah = -99;
            tempindex = 0;
        }

        printf("\n");
        printf("April %d : \n", tahunprint);
        for (int k = 0; k < indexPenyakit; k++){
            for (int l = 0; l < jumlahstruct;l++){
                if (tempjumlah < PenyakitperWaktu[l].bulan->apr && PenyakitperWaktu[l].bulan->apr != INT_MAX && PenyakitperWaktu[l].tahun == tahunprint){
                    tempindex = l;
                    tempjumlah = PenyakitperWaktu[l].bulan->apr;
                }
            }
            PenyakitperWaktu[tempindex].bulan->apr = INT_MAX;
            printf("%s : %d \n", PenyakitperWaktu[tempindex].penyakit, tempjumlah);
            tempjumlah = -99;
            tempindex = 0;
        }

        printf("\n");
        printf("Mei %d : \n", tahunprint);
        for (int k = 0; k < indexPenyakit; k++){
            for (int l = 0; l < jumlahstruct;l++){
                if (tempjumlah < PenyakitperWaktu[l].bulan->mei && PenyakitperWaktu[l].bulan->mei != INT_MAX && PenyakitperWaktu[l].tahun == tahunprint){
                    tempindex = l;
                    tempjumlah = PenyakitperWaktu[l].bulan->mei;
                }
            }
            PenyakitperWaktu[tempindex].bulan->mei = INT_MAX;
            printf("%s : %d \n", PenyakitperWaktu[tempindex].penyakit, tempjumlah);
            tempjumlah = -99;
            tempindex = 0;
        }

        printf("\n");
        printf("Juni %d : \n", tahunprint);
        for (int k = 0; k < indexPenyakit; k++){
            for (int l = 0; l < jumlahstruct;l++){
                if (tempjumlah < PenyakitperWaktu[l].bulan->jun && PenyakitperWaktu[l].bulan->jun != INT_MAX && PenyakitperWaktu[l].tahun == tahunprint){
                    tempindex = l;
                    tempjumlah = PenyakitperWaktu[l].bulan->jun;
                }
            }
            PenyakitperWaktu[tempindex].bulan->jun = INT_MAX;
            printf("%s : %d \n", PenyakitperWaktu[tempindex].penyakit, tempjumlah);
            tempjumlah = -99;
            tempindex = 0;
        }

        printf("\n");
        printf("Juli %d : \n", tahunprint);
        for (int k = 0; k < indexPenyakit; k++){
            for (int l = 0; l < jumlahstruct;l++){
                if (tempjumlah < PenyakitperWaktu[l].bulan->jul && PenyakitperWaktu[l].bulan->jul != INT_MAX && PenyakitperWaktu[l].tahun == tahunprint){
                    tempindex = l;
                    tempjumlah = PenyakitperWaktu[l].bulan->jul;
                }
            }
            PenyakitperWaktu[tempindex].bulan->jul = INT_MAX;
            printf("%s : %d \n", PenyakitperWaktu[tempindex].penyakit, tempjumlah);
            tempjumlah = -99;
            tempindex = 0;
        }

        printf("\n");
        printf("Agustus %d : \n", tahunprint);
        for (int k = 0; k < indexPenyakit; k++){
            for (int l = 0; l < jumlahstruct;l++){
                if (tempjumlah < PenyakitperWaktu[l].bulan->agu && PenyakitperWaktu[l].bulan->agu != INT_MAX && PenyakitperWaktu[l].tahun == tahunprint){
                    tempindex = l;
                    tempjumlah = PenyakitperWaktu[l].bulan->agu;
                }
            }
            PenyakitperWaktu[tempindex].bulan->agu = INT_MAX;
            printf("%s : %d \n", PenyakitperWaktu[tempindex].penyakit, tempjumlah);
            tempjumlah = -99;
            tempindex = 0;
        }

        printf("\n");
        printf("September %d : \n", tahunprint);
        for (int k = 0; k < indexPenyakit; k++){
            for (int l = 0; l < jumlahstruct;l++){
                if (tempjumlah < PenyakitperWaktu[l].bulan->sep && PenyakitperWaktu[l].bulan->sep != INT_MAX && PenyakitperWaktu[l].tahun == tahunprint){
                    tempindex = l;
                    tempjumlah = PenyakitperWaktu[l].bulan->sep;
                }
            }
            PenyakitperWaktu[tempindex].bulan->sep = INT_MAX;
            printf("%s : %d \n", PenyakitperWaktu[tempindex].penyakit, tempjumlah);
            tempjumlah = -99;
            tempindex = 0;
        }

        printf("\n");
        printf("Oktober %d : \n", tahunprint);
        for (int k = 0; k < indexPenyakit; k++){
            for (int l = 0; l < jumlahstruct;l++){
                if (tempjumlah < PenyakitperWaktu[l].bulan->okt && PenyakitperWaktu[l].bulan->okt != INT_MAX && PenyakitperWaktu[l].tahun == tahunprint){
                    tempindex = l;
                    tempjumlah = PenyakitperWaktu[l].bulan->okt;
                }
            }
            PenyakitperWaktu[tempindex].bulan->okt = INT_MAX;
            printf("%s : %d \n", PenyakitperWaktu[tempindex].penyakit, tempjumlah);
            tempjumlah = -99;
            tempindex = 0;
        }

        printf("\n");
        printf("November %d : \n", tahunprint);
        for (int k = 0; k < indexPenyakit; k++){
            for (int l = 0; l < jumlahstruct;l++){
                if (tempjumlah < PenyakitperWaktu[l].bulan->nov && PenyakitperWaktu[l].bulan->nov != INT_MAX && PenyakitperWaktu[l].tahun == tahunprint){
                    tempindex = l;
                    tempjumlah = PenyakitperWaktu[l].bulan->nov;
                }
            }
            PenyakitperWaktu[tempindex].bulan->nov = INT_MAX;
            printf("%s : %d \n", PenyakitperWaktu[tempindex].penyakit, tempjumlah);
            tempjumlah = -99;
            tempindex = 0;
        }
        
        printf("\n");
        printf("Desember %d : \n", tahunprint);
        for (int k = 0; k < indexPenyakit; k++){
            for (int l = 0; l < jumlahstruct;l++){
                if (tempjumlah < PenyakitperWaktu[l].bulan->des && PenyakitperWaktu[l].bulan->des != INT_MAX && PenyakitperWaktu[l].tahun == tahunprint){
                    tempindex = l;
                    tempjumlah = PenyakitperWaktu[l].bulan->des;
                }
            }
            PenyakitperWaktu[tempindex].bulan->des = INT_MAX;
            printf("%s : %d \n", PenyakitperWaktu[tempindex].penyakit, tempjumlah);
            tempjumlah = -99;
            tempindex = 0;
        }

        //Jumlah dalam Setahun
        printf("\n");
        printf("Dalam Tahun %d :\n", tahunprint);
        for (int i = 0 ; i < jumlahstruct; i++){
            if (PenyakitperWaktu[i].tahun == tahunprint){
                printf("%s : %d \n", PenyakitperWaktu[i].penyakit, PenyakitperWaktu[i].jumlahperTahun);
            }
        }
    }

    //free alocationg memori
    for (int i = 0 ; i < jumlahstruct; i++){
        free(PenyakitperWaktu[i].bulan);
        free(PenyakitperWaktu[i].penyakit);
    }
    free(PenyakitperWaktu);
}