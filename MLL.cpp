#include <iostream>
#include "MLL.h"

using namespace std;
void start();
void createList(ListR &L){
    L.first = nullptr;
    L.last = nullptr;
}

bool isEmptyResep(ListR L){
    return L.first = nullptr;
}

bool isEmptyBahan(adrResep p){
    return p->firstBahan = nullptr;
}

adrResep createElmResep(string nama, int durasi, string kategori){
    adrResep p;

    p = new elmResep;
    p->info.namaResep = nama;
    p->info.durasiMasak = durasi;
    p->info.kategori = kategori;
    p->next = nullptr;
    p->prev = nullptr;
    p->firstBahan = nullptr;

    return p;
}

adrBahan createElmBahan(string nama, int jumlah, string deskripsi){
    adrBahan p;

    p = new elmBahan;
    p->info.namaBahan = nama;
    p->info.jumlahBahan = jumlah;
    p->info.deskripsi = deskripsi;
    p->next = nullptr

    return p;
}

void insertResep(ListR &L, adrResep p){
    if (isEmptyResep(L)){
        L.first = p;
        L.last = p;
    }else {
        p->prev = L.last;
        L.last->next = p;
        L.last = p;
    }
}

void insertBahan(adrResep &p, adrBahan q){
    if (isEmptyBahan(p)){
        p->firstBahan = q;
    }else {
        adrBahan temp;
        temp = p->firstBahan;

        while (temp->next != nullptr){
            temp = temp->next;
        }
        temp->next = q;
        q->prev = temp;
    }
}

void printResep(adrResep p){
    if (p == nullptr){
        cout << "Resep kosong" << endl;
    }else{
        adrBahan q;
        q = p->firstBahan;
        cout << "---------------------------------------------------" << endl;
        cout << "Resep : " << p->info.namaResep << endl;
        cout << "Durasi Masak : " << p->info.durasiMasak << " Menit" << endl;
        cout << "Kategori : " << p->info.kategori << endl;
        if (isEmptyBahan(p)){
            cout << "Bahan belum tersedia";
        }else{
            cout << " ------------------------" << endl;
            cout << " |\t  Bahan          |" << endl;
            cout << " ------------------------" << endl;
            while (q != nullptr){
                string teks;
                teks = q->info.namaBahan + " " + to_string(q->info.jumlahBahan) + " " + q->info.deskripsi;
                cout << " | " ;
                cout << left << setw(21) << teks;
                cout << "|" << endl;
                q = q->next;
            }
                cout << " ------------------------" << endl;
        }
    }
}

void viewAll(ListR L){
    if (isEmptyResep(L)){
        cout << "Resep Kosong";
    }else {
        adrResep p;
        p = L.first;
        while (p != nullptr){
            printResep(p);
            p = p->next;
        }
    }
}

adrResep searchResepByNama(ListR L, string nama){
    if (isEmptyResep(L)){
        return nullptr;
    }else {
        adrResep p;
        p = L.first;
        while(p != nullptr){
            if (p->info.namaResep == nama){
                return p;
            }
            p = p->next;
        }
        return nullptr;
    }
}

void searchResepByDurasi(ListR L, int durasi){
    string option;

    if (isEmptyResep(L)){
        cout << "Resep tidak ditemukan!" << endl;
    }else {
        adrResep p;
        bool found;
        p = L.first;
        while (p != nullptr){
            if (p->info.durasiMasak < durasi){
                printResep(p);
                found = true;
            }
            p = p->next;
        }
        if (!found){
            cout << "Resep tidak ditemukan!";
            cout << "Sepertinya kamu terlalu sibuk ya?";
            cout << "Mau coba masukkan waktu yang lebih lama? (Y/N): ";
            cin >> option;
            if (option == "Y" || option == "y"){
                int New;
                cout << "Masukkan perkiraan waktu yang kamu miliki(hanya angka): ";
                cin >> New;
                searchResepByDurasi(L, New);
            }else{
                start();
            }
        }
    }
}

void searchResepByBahan(ListR L, adrBahan q);
void deleteResep(ListR &L, string nama);
void deleteDurasiFromResep(ListR &L, string nama);
void deleteBahanFromResep(ListR &L, string namaResep, string NamaBahan);
int countResep(ListR L);
void viewResepByCategory(ListR L, string kategori);
void durasiMinMax(ListR L);
void viewResepByJumlahBahan(ListR L);
