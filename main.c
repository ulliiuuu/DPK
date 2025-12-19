#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filedata.h"

void tampilkanUsage(const char *namaProgram) {
    printf("Usage: %s [PILIHAN]\n", namaProgram);
    printf("Pilihan:\n");
    printf("  1 : Jalankan Modul Input Matakuliah\n");
    printf("  2 : Jalankan Modul Input Mahasiswa\n");
    printf("  3 : Jalankan Modul Input KRS\n");
    printf("  4 : Tambah input Mahasiswa\n");
    printf("  5 : Hapus input Mahasiswa\n");
}

int main(int argc, char *argv[]) {

    int pilihan = atoi(argv[1]);
    if (pilihan < 1 || pilihan > 5) {
        fprintf(stderr, "Error: Pilihan '%s' tidak valid.\n", argv[1]);
        tampilkanUsage(argv[0]);
        return 1;
    }
    int jumlah = 0;
    switch (pilihan) {
        case 1: {
            printf("--- MODUL INPUT MATAKULIAH ---\n");
            Matakuliah *daftar_mk = inputDataMatakuliah(&jumlah);
            if (daftar_mk == NULL) {
                fprintf(stderr, "Gagal mendapatkan data matakuliah.\n");
                return 1;
            }
            simpanMatakuliahKeCSV(daftar_mk, jumlah);
            free(daftar_mk);
            bacaDariFileCSV(FILE_NAME_MK);
            break;
        }
        case 2: {
            printf("--- MODUL INPUT MAHASISWA ---\n");
            Mahasiswa *daftar = inputDataMahasiswa(&jumlah);
            if (daftar == NULL) {
                fprintf(stderr, "Gagal mendapatkan data mahasiswa.\n");
                return 1;
            }
            simpanKeFileCSV(daftar, jumlah, FILE_NAME_MHS);
            free(daftar);
            bacaDariFileCSV(FILE_NAME_MHS);
            break;
        }
        case 3: {
            printf("--- MODUL INPUT KRS ---\n");
            KRS *daftar_krs = inputDataKRS(&jumlah);
            if (daftar_krs == NULL) {
                fprintf(stderr, "Gagal mendapatkan data KRS.\n");
                return 1;
            }
            simpanKRSKeCSV(daftar_krs, jumlah);
            free(daftar_krs);
            bacaDariFileCSV(FILE_NAME_KRS);
            break;
        }
        case 4: {
            printf("--- TAMBAH MAHASISWA ---\n");
            tambahDataMahasiswa();
            break;
        }
        case 5: {
            printf("--- HAPUS MAHASISWA ---\n");
            hapusDataMahasiswa();
            break;
        }
        default:
            fprintf(stderr, "Pilihan tidak dikenali.\n");
            return 1;
    }
    return 0;
}
