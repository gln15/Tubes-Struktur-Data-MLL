#ifndef MLL_H_INCLUDED
#define MLL_H_INCLUDED
#include <iostream>

using namespace std;

typedef struct elmResep *adrResep;
typedef struct elmBahan *adrBahan;

struct resep{
    string namaResep;
    int durasiMasak;
    string kategori;
};

struct bahan{
    string namaBahan;
    int jumlahBahan;
    string deskripsi;
};

struct elmResep{
    resep info;
    adrResep next;
    adrResep prev;
    adrBahan firstBahan;
};

struct elmBahan{
    bahan info;
    adrBahan next;
};

struct ListR{
    adrResep first;
    adrResep last;
};

void menu();
void createList(ListR &L);
adrResep createElmResep(string nama, int durasi, string kategori);
adrBahan createElmBahan(string nama, int jumlah, string deskripsi);
bool isEmptyResep(ListR L);
bool isEmptyBahan(adrResep p);
void printResep(adrResep p);
void insertResep(ListR &L, adrResep p);
void insertBahan(adrResep &p, adrBahan q);
void viewAll(ListR L);
adrResep searchResepByNama(ListR L, string nama);
void searchResepByDurasi(ListR L, int durasi);
void searchResepByBahan(ListR L, string bahan);
void deleteResep(ListR &L, string nama);
void deleteDurasiFromResep(ListR &L, string nama);
void deleteBahanFromResep(adrResep p, string NamaBahan);
int countResep(ListR L);
void viewResepByCategory(ListR L, string kategori);
void durasiMinMax(ListR L);
void viewResepByJumlahBahan(ListR L, int jumlah);
string pilihKategori(int x);
void loadDummyData(ListR &L);
void showCover();
void showPenutup();
void updateKategoriResep(ListR &L, string namaResep);
void showNamaResep(ListR L);
#endif // MLL_H_INCLUDED

