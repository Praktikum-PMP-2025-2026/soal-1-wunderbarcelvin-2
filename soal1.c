/** EL2008 Praktikum Pemecahan Masalah dengan Pemrograman 2024/2025
 *   Modul               : 2
 *   Hari dan Tanggal    : Senin, 20 April 2026
 *   Nama (NIM)          : Celvin Ello X. Silitonga (13224107)
 *   Nama File           : fragmensensor.c
 *   Deskripsi           : */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

/**Kondisi/Aturan
1. Nilai hilang ditandai -1
2. Untuk tiap -1:
• cari tetangga valid terdekat di kiri dan kanan
• jika dua-duanya ada, ganti dengan floor((kiri+kanan)/2)
• jika hanya kiri ada, pakai kiri
• jika hanya kanan ada, pakai kanan
• jika tidak ada keduanya, ganti 0
3. Setelah semua elemen dipulihkan, hitung jumlah maksimum dari semua subarray kontigu non-
kosong */


void load(int* temp_array, int* nums);
void normalize(int* temp_array, int* nums);
void recurr(int* temp_array, int* nums, int idx, int* next);
void count_sum(int* temp_array, int* nums, int* sum);

//ngetes dulu, subfungsi dalam fungsi

int main(void){
    int storage[20];
    int nums, sum=0;
    load(storage, &nums);
    normalize(storage, &nums);
    count_sum(storage, &nums, &sum);
    return 0;
}

void load(int* temp_array, int* nums){
    char line[20];
    fgets(line, sizeof(line), stdin);
    char* token = strtok(line, " ");

    if(token){
        *nums = atoi(token);
        for (int i = 0; i < *nums; i++)
        {
            token = strtok(NULL, " ");
            int temp = atoi(token);
            //printf("[DEBUG] Nilai masukan: %d\n", temp);
            temp_array[i] = temp;
        }
        //harusnya udah ditampung semua ke array
    }
}

void normalize(int* temp_array, int* nums){
    int size = *nums;
    int before = 0, next=0;
    
    for (int i = 0; i < size; i++)
    {
        recurr(temp_array, nums, i, &next); //update nilai next

        if(temp_array[i]==-1){ //ini kalau nilainya -1
            
            if(i==0){ //ini jikalau berada di indeks depan
                temp_array[i]=next;
            } else if (i==size-1)
            {
                temp_array[i]=before;
            } //ini ketika mencapai indeks terakhir
            
            
            else{ //kasus di depan atau di tengah array
                if(next==0){
                    temp_array[i]=before;
                } else{
                    float avg = (before+next)/2;
                    temp_array[i] = floor(avg);
                }
            }

             //direassign ulang preceeding valuenya
        }

        printf("[DEBUG] NEXT: %d\n", next);
        printf("[DEBUG] BEFORE: %d\n", before);

        printf("[DEBUG] INDEKS KE-%d\n", i);
        printf("[DEBUG] NILAI: %d\n", temp_array[i]);

        before = temp_array[i]; //update nilai before
    }
    
}
//preceeeding valuenya disimpan dari framing yang berjalan
//next valuenya direkursi aja?

void recurr(int* temp_array, int* nums, int idx, int* next){ //ini bakal digunain kalau kasusnya ketemu -1 
    //next itu nilai yang bakal digunaian [OUTPUT]

    //neglect dulu kasus semuanya nilainya -1
    if(idx==*nums) return;

    if(temp_array[idx+1]!=-1){
        *next = temp_array[idx+1];
        return;
    } else if (temp_array[idx+1]==-1){
        recurr(temp_array, nums, idx+1, next);
    }
}

void count_sum(int* temp_array, int* nums, int* sum){
    printf("\nRECOVERED ");
    for (int i = 0; i < *nums; i++)
    {
        printf("%d", temp_array[i]);
        if(i==*nums-1) printf("\n");
        else printf(" ");

        *sum+=temp_array[i]; //akumulasi jumlah subarray
        //printf("%d\n", *sum);
    }    

    printf("MAX_SUM %d", *sum);
}

