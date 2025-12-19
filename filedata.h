void tambahDataMahasiswa();
void hapusDataMahasiswa();
#ifndef FILEDATA_H
#define FILEDATA_H
#define MAX_NAME_LEN 100
#define MAX_PRODI_LEN 100
#define MAX_NAME_MK_LEN 100
#define MAX_KODE_MK_LEN 100
#define MAX_FAKULTAS_LEN 100

#define FILE_NAME_MHS "mahasiswa.csv"
#define FILE_NAME_MK "matakuliah.csv"
#define FILE_NAME_KRS "krs.csv"

//mahasiswa
typedef struct {
    char nim[20];
    char nama[MAX_NAME_LEN];
    char fakultas[MAX_FAKULTAS_LEN];
    char prodi[MAX_PRODI_LEN];
    int angkatan;
    float ipk;
} Mahasiswa;


//matakuliah
typedef struct {
    char kode_mk[MAX_KODE_MK_LEN];
    char nama_mk[MAX_NAME_MK_LEN];
    int sks;
} Matakuliah;

//KRS
typedef struct {
    char nim[20];
    char kode_mk[MAX_KODE_MK_LEN];
    char nama_mk[MAX_NAME_MK_LEN];
    int sks;
} KRS;


void bersihkanBufferInput(void);

Mahasiswa* inputDataMahasiswa(int *jumlah);
void simpanKeFileCSV(Mahasiswa *mhs, int jumlah, const char *namaFile);
Matakuliah* inputDataMatakuliah(int *jumlah);
void simpanMatakuliahKeCSV(Matakuliah *mk, int jumlah);
KRS* inputDataKRS(int *jumlah);
void simpanKRSKeCSV(KRS *krs, int jumlah);

void tampilkanDaftarMatakuliah();

int cariNamaMahasiswaByNIM(const char *nim, char *nama, int max_len);
int cariMatakuliahByKode(const char *kode_mk, char *nama_mk, int *sks);
void bacaDariFileCSV(const char *namaFile);

#endif