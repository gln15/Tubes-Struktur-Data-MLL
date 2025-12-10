#include <iostream>
#include "MLL.h"
#include "iomanip"
using namespace std;
void menu(){
    cout << "1. Tambah Resep " << endl;
    cout << "2. Tambah Bahan " << endl;
    cout << "3. View All" << endl;
    cout << "4. Cari Resep" << endl;
    cout << "5. Hapus Resep" << endl;
    cout << "6. Hapus Durasi dari resep" << endl;
    cout << "7. Hapus Bahan dari resep" << endl;
    cout << "8. View Resep berdasarkan kategori" << endl;
    cout << "9. View Resep Tercepat" << endl;
    cout << "10. View Resep Terlama" << endl;
    cout << "10. View Resep dengan jumlah bahan" << endl;
    cout << "0. exit " << endl;
    cout << "Masukkan pilihan anda: ";
}

void createList(ListR &L){
    L.first = nullptr;
    L.last = nullptr;
}

bool isEmptyResep(ListR L){
    return L.first == nullptr;
}

bool isEmptyBahan(adrResep p){
    return p->firstBahan == nullptr;
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
    p->next = nullptr;

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
                menu();
            }
        }
    }
}

void searchResepByBahan(ListR L, string bahan){
    adrResep p;
    adrBahan q;
    bool found, bahanDitemukan;
    if(isEmptyResep(L)){
        cout << "Resep tidak ditemukan!" << endl;
    }
    cout << "=== Resep Yang Menggunakan Bahan: " << bahan << " ===" << endl;
    found = false;
    p = L.first;
    while(p != nullptr){
        q = p->firstBahan;
        bahanDitemukan = false;
        while(q != nullptr && !bahanDitemukan){
            if(q->info.namaBahan == bahan){
                bahanDitemukan = true;
            }
            q = q->next;
        }
        if(bahanDitemukan){
            printResep(p);
            found = true;
        }
        p = p->next;
    }
}

void deleteResep(ListR &L, string nama){
    adrResep p;
    adrBahan q, temp;
    p = searchResepByNama(L, nama);
    if(p == nullptr){
        cout << "Resep '" << nama << "' tidak ditemukan!" << endl;
    }
    if(p == L.first && p ==L.last){
        L.first = nullptr;
        L.last = nullptr;
    } else if(p == L.first){
        L.first = p->next;
        if(L.first != nullptr){
            L.first->prev = nullptr;
        }
    } else if (p == L.last){
        L.last = p->prev;
        if(L.last != nullptr){
            L.last->next = nullptr;
        }
    } else {
        p->prev->next = p->next;
        p->next->prev = p->prev;
    }
    cout << "Resep '" << nama << "' berhasil dihapus dari daftar!" << endl;
}

void deleteDurasiFromResep(ListR &L, string nama){
    adrResep p;
    p = searchResepByNama(L, nama);
    if(p == nullptr){
        cout << "Resep '" << nama << "' tidak ditemukan!" << endl;
    }
    p->info.durasiMasak = 0;
    cout << "Durasi masak dari resep '" << nama << "' berhasil dihapus! (diatur ke 0 menit)" << endl;
}

void deleteBahanFromResep(ListR &L, string namaResep, string namaBahan){
    adrResep p;
    adrBahan q, prev;
    bool found;
    p = searchResepByNama(L, namaResep);
    if(p == nullptr){
        cout << "Resep '" << namaResep << "' tidak ditemukan!" << endl;
    }
    if(isEmptyBahan(p)){
        cout << "Resep '" << namaResep << "' tidak memiliki bahan!" << endl;
    }
    q = p->firstBahan;
    prev = nullptr;
    found = false;
    while(q != nullptr && !found){
        if (q->info.namaBahan == namaBahan){
            found = true;
        } else {
            prev = q;
            q = q->next;
        }
    }
    if(prev == nullptr){
        p->firstBahan = q->next;
    } else {
        prev->next = q->next;
    }
    cout << "Bahan '" << namaBahan << "' berhasil dihapus dari resep '" << namaResep << "'" << endl;
}

int countResep(ListR L){
    int count = 0;
    adrResep p;
    p = L.first;
    while(p != nullptr){
        count++;
        p = p->next;
    }
    return count;
}

void viewResepByCategory(ListR L, string kategori){
    adrResep p = L.first;
    int count = 0;
    bool found = false;
    cout << "=== Resep Kategori: " << kategori << " ===" << endl;
    while(p != nullptr){
        if(p->info.kategori == kategori){
            printResep(p);
            count++;
            found = true;
        }
        p = p->next;
    }
    if(found){
        cout << "Total resep kategori " << kategori << ": " << count << endl;
    } else {
        cout << "Resep dengan kategori: " << kategori << " tidak ditemukan!" << endl;
    }
}

void durasiMinMax(ListR L){
    adrResep p, minResep, maxResep;
    p = L.first;
    minResep = p;
    maxResep = p;
    while(p != nullptr){
        if(p->info.durasiMasak < minResep->info.durasiMasak){
            minResep = p;
        }
        if(p->info.durasiMasak > maxResep->info.durasiMasak){
            maxResep = p;
        }
        p = p->next;
    }
    cout << "=== Resep Dengan Durasi Tercepat ===" << endl;
    printResep(minResep);
    cout << "=== Resep Dengan Durasi Terlama ===" << endl;
    printResep(maxResep);
}

void viewResepByJumlahBahan(ListR L, int jumlah){
    adrResep p = L.first;
    adrBahan q;
    int countBahan = 0;
    bool found = false;
    cout << "=== Resep Dengan Jumlah Bahan: " << jumlah << " ===" << endl;
    while(p != nullptr){
        q = p->firstBahan;
        while(q != nullptr){
            countBahan++;
            q = q->next;
        }
        if(countBahan == jumlah){
            printResep(p);
            found = true;
        }
        p = p->next;
    }
}

