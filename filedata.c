#include "filedata.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


//untuk mahasiswa
Mahasiswa* inputDataMahasiswa(int *jumlah) {
    printf("Masukkan jumlah mahasiswa: ");
    while (scanf("%d", jumlah) != 1 || *jumlah <= 0) {
        printf("Input tidak valid. Masukkan angka positif untuk jumlah mahasiswa: ");
        bersihkanBufferInput();
    }
    bersihkanBufferInput();

    Mahasiswa *data = (Mahasiswa*) malloc((*jumlah) * sizeof(Mahasiswa));
    if (!data) {
        printf("Alokasi memori gagal!\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < *jumlah; i++) {
        printf("\nMahasiswa #%d\n", i + 1);
        while (1) {
            printf("NIM      : ");
            if (fgets(data[i].nim, sizeof(data[i].nim), stdin) == NULL) {
                data[i].nim[0] = '\0';
            } else {
                data[i].nim[strcspn(data[i].nim, "\n")] = '\0';
            }
            // Cek duplikasi NIM pada input batch saja
            int duplikat = 0;
            for (int j = 0; j < i; j++) {
                if (strcmp(data[i].nim, data[j].nim) == 0) {
                    duplikat = 1;
                    break;
                }
            }
            if (duplikat) {
                printf("NIM sudah ada, Silahkan gunakan NIM lain!\n");
                continue;
            }
            break;
        }

        printf("Nama     : ");
        if (fgets(data[i].nama, MAX_NAME_LEN, stdin) == NULL) {
            data[i].nama[0] = '\0';
        } else {
            data[i].nama[strcspn(data[i].nama, "\n")] = '\0';
        }

        printf("Fakultas : ");
        if (fgets(data[i].fakultas, MAX_FAKULTAS_LEN, stdin) == NULL) {
            data[i].fakultas[0] = '\0';
        } else {
            data[i].fakultas[strcspn(data[i].fakultas, "\n")] = '\0';
        }

        printf("Prodi    : ");
        if (fgets(data[i].prodi, MAX_PRODI_LEN, stdin) == NULL) {
            data[i].prodi[0] = '\0';
        } else {
            data[i].prodi[strcspn(data[i].prodi, "\n")] = '\0';
        }

        printf("Angkatan : ");
        while (scanf("%d", &data[i].angkatan) != 1) {
            printf("Input tidak valid. Masukkan angka untuk angkatan: ");
            bersihkanBufferInput();
        }
        bersihkanBufferInput();

        printf("IPK      : ");
        while (scanf("%f", &data[i].ipk) != 1) {
            printf("Input tidak valid. Masukkan angka desimal untuk IPK: ");
            bersihkanBufferInput();
        }
        bersihkanBufferInput();

    }

    return data;
}

void simpanKeFileCSV(Mahasiswa *mhs, int jumlah, const char *namaFile) {

    FILE *fp = fopen(namaFile, "w");
    if (!fp) {
        printf("Gagal membuka file untuk menulis!\n");
        return;
    }

    fprintf(fp, "NIM,Nama,Fakultas,Prodi,Angkatan,IPK\n");
    for (int i = 0; i < jumlah; i++) {
        fprintf(fp, "%s,%s,%s,%s,%d,%.2f\n",
                mhs[i].nim, mhs[i].nama, mhs[i].fakultas, mhs[i].prodi, mhs[i].angkatan, mhs[i].ipk);
    }

    fclose(fp);
    printf("\nData berhasil disimpan ke file '%s'\n", namaFile);
}

//untuk matakuliah
Matakuliah* inputDataMatakuliah(int *jumlah) {
    printf("Masukkan jumlah matakuliah: ");
    while (scanf("%d", jumlah) != 1 || *jumlah <= 0) {
        printf("Input tidak valid. Masukkan angka positif untuk jumlah matakuliah: ");
        bersihkanBufferInput();
    }
    bersihkanBufferInput();

    Matakuliah *data = (Matakuliah*) malloc((*jumlah) * sizeof(Matakuliah));
    if (!data) {
        printf("Alokasi memori gagal!\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < *jumlah; i++) {
        printf("\nMatakuliah #%d\n", i + 1);

        printf("Kode MK: ");
        if (fgets(data[i].kode_mk, MAX_KODE_MK_LEN, stdin) == NULL) {
            data[i].kode_mk[0] = '\0';
        } else {
            data[i].kode_mk[strcspn(data[i].kode_mk, "\n")] = '\0';
        }

        printf("Nama MK: ");
        if (fgets(data[i].nama_mk, MAX_NAME_MK_LEN, stdin) == NULL) {
            data[i].nama_mk[0] = '\0';
        } else {
            data[i].nama_mk[strcspn(data[i].nama_mk, "\n")] = '\0';
        }

        printf("SKS    : ");
        while (scanf("%d", &data[i].sks) != 1) {
            printf("Input tidak valid. Masukkan angka untuk SKS: ");
            bersihkanBufferInput();
        }
        bersihkanBufferInput();
    }

    return data;
}

void simpanMatakuliahKeCSV(Matakuliah *mk, int jumlah) {
    FILE *fp = fopen(FILE_NAME_MK, "w");
    if (!fp) {
        printf("Gagal membuka file untuk menulis!\n");
        return;
    }

    fprintf(fp, "Kode MK,Nama MK,SKS\n");
    for (int i = 0; i < jumlah; i++) {
        fprintf(fp, "%s,%s,%d\n",
                mk[i].kode_mk, mk[i].nama_mk, mk[i].sks);
    }
    fclose(fp);
    printf("\nData berhasil disimpan ke file '%s'\n", FILE_NAME_MK);
}

// untuk KRS
KRS* inputDataKRS(int *jumlah) {
    char nim[20] = "";
    printf("Masukkan NIM : ");
    if (fgets(nim, sizeof(nim), stdin) == NULL)
        nim[0] = '\0';
    else
        nim[strcspn(nim, "\n")] = '\0';

    char nama_mhs[100] = "";
    if (cariNamaMahasiswaByNIM(nim, nama_mhs, sizeof(nama_mhs))) {
        printf("Nama Mahasiswa : %s\n", nama_mhs);
    } else {
        printf("Nama mahasiswa tidak ditemukan!\n");
    }

    tampilkanDaftarMatakuliah();

    printf("Masukkan jumlah mata kuliah yang ingin dipilih: ");
    while (scanf("%d", jumlah) != 1 || *jumlah <= 0) {
        printf("Input tidak valid. Masukkan angka positif: ");
        bersihkanBufferInput();
    }
    bersihkanBufferInput();

    KRS *data = (KRS*) malloc((*jumlah) * sizeof(KRS));
    if (!data) {
        printf("Memori gagal dialokasikan!\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < *jumlah; i++) {
        while (1) {
            printf("Pilih matakuliah #%d, masukkan Kode MK : ", i+1);
            if (fgets(data[i].kode_mk, sizeof(data[i].kode_mk), stdin) == NULL)
                data[i].kode_mk[0] = '\0';
            else
                data[i].kode_mk[strcspn(data[i].kode_mk, "\n")] = '\0';

            if (cariMatakuliahByKode(data[i].kode_mk, data[i].nama_mk, &(data[i].sks))) {
                printf("Matakuliah ditemukan : %s (SKS: %d)\n", data[i].nama_mk, data[i].sks);
                strncpy(data[i].nim, nim, sizeof(data[i].nim));
                break;
            }
            printf("Kode MK tidak ditemukan, coba lagi!\n");
        }
    }
    return data;
}

void simpanKRSKeCSV(KRS *krs, int jumlah) {
    FILE *fp = fopen(FILE_NAME_KRS, "w");
    if (!fp) {
        printf("Gagal membuka file untuk menulis!\n");
        return;
    }

    fprintf(fp, "NIM,KodeMK,NamaMK,SKS\n");

    for (int i = 0; i < jumlah; i++) {
        fprintf(fp, "%s,%s,%s,%d\n",
            krs[i].nim, krs[i].kode_mk, krs[i].nama_mk, krs[i].sks
        );
    }

    fclose(fp);
    printf("\nData berhasil disimpan ke file '%s'\n", FILE_NAME_KRS);
}

void tampilkanDaftarMatakuliah() {
    FILE *fp = fopen(FILE_NAME_MK, "r");
    if (!fp) {
        printf("Tidak bisa membuka file matakuliah!\n");
        return;
    }
    char line[256];
    fgets(line, sizeof(line), fp); 
    printf("\nDaftar Matakuliah Tersedia:\n");
    printf("%-10s   | %-20s          | %s\n", "Kode MK", "Nama MK", "SKS");
    printf("---------------------------------------------\n");
    while (fgets(line, sizeof(line), fp)) {
        char kode[32], nama[128];
        int sks = 0;
        sscanf(line, "%[^,],%[^,],%d", kode, nama, &sks);
        printf("%-10s | %-20s | %d\n", kode, nama, sks);
    }
    fclose(fp);
}

int cariNamaMahasiswaByNIM(const char *nim, char *nama, int max_len) {
    FILE *fp = fopen(FILE_NAME_MHS, "r");
    if (!fp) return 0;
    char line[256];
    fgets(line, sizeof(line), fp); // skip header
    while (fgets(line, sizeof(line), fp)) {
        char file_nim[32], file_nama[128];
        sscanf(line, "%[^,],%[^,]", file_nim, file_nama);
        if (strcmp(file_nim, nim) == 0) {
            strncpy(nama, file_nama, max_len - 1);
            nama[max_len-1] = '\0';
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    if (nama && max_len > 0) nama[0] = '\0';
    return 0;
}

int cariMatakuliahByKode(const char *kode_mk, char *nama_mk, int *sks) {
    FILE *fp = fopen(FILE_NAME_MK, "r");
    if (!fp) return 0;
    char line[256];
    fgets(line, sizeof(line), fp); // skip header
    while (fgets(line, sizeof(line), fp)) {
        char file_kode[32], file_nama[128];
        int file_sks = 0;
        sscanf(line, "%[^,],%[^,],%d", file_kode, file_nama, &file_sks);
        if (strcmp(file_kode, kode_mk) == 0) {
            if (nama_mk) {
                strncpy(nama_mk, file_nama, MAX_NAME_MK_LEN);
                nama_mk[MAX_NAME_MK_LEN-1] = '\0';
            }
            if (sks) *sks = file_sks;
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    if (nama_mk) nama_mk[0] = '\0';
    if (sks) *sks = 0;
    return 0;
}

void bacaDariFileCSV(const char *namaFile) {
}

// Tambah satu data mahasiswa ke mahasiswa.csv
void tambahDataMahasiswa() {
    Mahasiswa m;
    printf("Masukkan data mahasiswa baru\n");
    printf("NIM      : ");
    if (fgets(m.nim, sizeof(m.nim), stdin) == NULL) m.nim[0] = '\0';
    else m.nim[strcspn(m.nim, "\n")] = '\0';

    // Cek duplikasi NIM di file
    FILE *fp = fopen(FILE_NAME_MHS, "r");
    char line[256];
    int duplikat = 0;
    if (fp) {
        fgets(line, sizeof(line), fp); // skip header
        while (fgets(line, sizeof(line), fp)) {
            char file_nim[32];
            sscanf(line, "%[^,]", file_nim);
            if (strcmp(file_nim, m.nim) == 0) {
                duplikat = 1;
                break;
            }
        }
        fclose(fp);
    }
    if (duplikat) {
        printf("NIM sudah ada, Silahkan gunakan NIM lain!\n");
        return;
    }

    printf("Nama     : ");
    if (fgets(m.nama, MAX_NAME_LEN, stdin) == NULL) m.nama[0] = '\0';
    else m.nama[strcspn(m.nama, "\n")] = '\0';

    printf("Fakultas : ");
    if (fgets(m.fakultas, MAX_FAKULTAS_LEN, stdin) == NULL) m.fakultas[0] = '\0';
    else m.fakultas[strcspn(m.fakultas, "\n")] = '\0';

    printf("Prodi    : ");
    if (fgets(m.prodi, MAX_PRODI_LEN, stdin) == NULL) m.prodi[0] = '\0';
    else m.prodi[strcspn(m.prodi, "\n")] = '\0';

    printf("Angkatan : ");
    while (scanf("%d", &m.angkatan) != 1) {
        printf("Input tidak valid. Masukkan angka untuk angkatan: ");
        bersihkanBufferInput();
    }
    bersihkanBufferInput();

    printf("IPK      : ");
    while (scanf("%f", &m.ipk) != 1) {
        printf("Input tidak valid. Masukkan angka desimal untuk IPK: ");
        bersihkanBufferInput();
    }
    bersihkanBufferInput();

    int fileBaru = 0;
    fp = fopen(FILE_NAME_MHS, "r");
    if (!fp) fileBaru = 1;
    else fclose(fp);

    fp = fopen(FILE_NAME_MHS, "a");
    if (!fp) {
        printf("Gagal membuka file untuk menulis!\n");
        return;
    }
    if (fileBaru) {
        fprintf(fp, "NIM,Nama,Fakultas,Prodi,Angkatan,IPK\n");
    }
    fprintf(fp, "%s,%s,%s,%s,%d,%.2f\n", m.nim, m.nama, m.fakultas, m.prodi, m.angkatan, m.ipk);
    fclose(fp);
    printf("\nData mahasiswa berhasil ditambahkan.\n");
}

// Hapus data mahasiswa dari mahasiswa.csv berdasarkan NIM dengan konfirmasi
void hapusDataMahasiswa() {
    char nim[20];
    printf("Masukkan NIM mahasiswa yang akan dihapus: ");
    if (fgets(nim, sizeof(nim), stdin) == NULL) nim[0] = '\0';
    else nim[strcspn(nim, "\n")] = '\0';

    FILE *fp = fopen(FILE_NAME_MHS, "r");
    if (!fp) {
        printf("File mahasiswa tidak ditemukan!\n");
        return;
    }
    FILE *fp_tmp = fopen("mahasiswa_tmp.csv", "w");
    if (!fp_tmp) {
        printf("Gagal membuat file sementara!\n");
        fclose(fp);
        return;
    }
    char line[256];
    int found = 0;
    fgets(line, sizeof(line), fp); // header
    fprintf(fp_tmp, "%s", line);
    while (fgets(line, sizeof(line), fp)) {
        char file_nim[32];
        sscanf(line, "%[^,]", file_nim);
        if (strcmp(file_nim, nim) == 0) {
            found = 1;
            continue; // skip baris ini
        }
        fprintf(fp_tmp, "%s", line);
    }
    fclose(fp);
    fclose(fp_tmp);
    if (found) {
        char konfirmasi;
        printf("Apakah Anda yakin ingin menghapus data mahasiswa dengan NIM %s? (y/n): ", nim);
        scanf(" %c", &konfirmasi);
        bersihkanBufferInput();
        if (konfirmasi == 'y' || konfirmasi == 'Y') {
            remove(FILE_NAME_MHS);
            rename("mahasiswa_tmp.csv", FILE_NAME_MHS);
            printf("Data mahasiswa dengan NIM %s berhasil dihapus.\n", nim);
        } else {
            remove("mahasiswa_tmp.csv");
            printf("Penghapusan dibatalkan.\n");
        }
    } else {
        remove("mahasiswa_tmp.csv");
        printf("Data mahasiswa dengan NIM %s tidak ditemukan.\n", nim);
    }
}

void bersihkanBufferInput() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
