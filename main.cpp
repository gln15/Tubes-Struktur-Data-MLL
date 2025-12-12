#include <iostream>
#include "MLL.h"

using namespace std;

int main(){
    string nama,namaResep, kategori,deskripsi;
    int x, durasi, jumlah;
    adrResep p;
    adrBahan q;
    ListR L;
    createList(L);
    loadDummyData(L);
    showCover();
    menu();
    cin >> x;
    while (x != 0){
        if (x == 1){
            cout << "Masukkan nama resep: ";
            cin >> nama;
            if (searchResepByNama(L, nama) != nullptr){
                cout << "Resep gagal ditambahkan karena memiliki nama yang sama!" << endl;
            }else{
                cout << "Masukkan durasi masak (menit): ";
                cin >> durasi;
                cout << "Pilih kategori makanan: ";
                cout << "\n1. Appetizer \n2. Main Course \n3. Dessert \n4. Snack" << endl;
                cout << "\nMasukan pilihan anda: ";
                cin >> x;
                kategori = pilihKategori(x);
                p = createElmResep(nama, durasi, kategori);
                insertResep(L, p);
                cout << "Resep berhasil ditambahkan!" << endl;
            }
        }else if (x == 2){
            cout << "Masukkan nama resep ingin ditambah: ";
            cin >> nama;
            p = searchResepByNama(L, nama);
            if (p == nullptr){
                cout << "Resep tidak ditemukan!" << endl;
            }else{
                cout << "\nMasukkan nama bahan: ";
                cin >> nama;
                cout << "\nMasukkan jumlah bahan: ";
                cin >> jumlah;
                cout << "\nMasukkan deskripsi bahan (gr, pcs, cup): ";
                cin >> deskripsi;
                q = createElmBahan(nama, jumlah, deskripsi);
                insertBahan(p,q);
                cout << "Bahan berhasil ditambahkan!" << endl;
            }
        }else if (x == 3){
            viewAll(L);
        }else if (x == 4){
            cout << "1. Cari resep berdasarkan nama " << endl;
            cout << "2. Cari resep berdasarkan bahan " << endl;
            cout << "3. Cari resep berdasarkan durasi " << endl;
            cout << "9. Kembali ke menu ";
            cout << "\nMasukkan pilihan anda: ";
            cin >> x;
            if (x == 1){
                cout << "Masukkan nama resep yang ingin dicari: ";
                cin >> nama;
                p = searchResepByNama(L,nama);
                printResep(p);
            }else if(x == 2){
                cout << "Masukkan nama bahan yang ada pada resep yang ingin dicari: ";
                cin >> nama;
                searchResepByBahan(L, nama);
            }else if (x == 3){
                cout << "Masukkan durasi maximal pada resep yang anda ingin cari: ";
                cin >> durasi;
                searchResepByDurasi(L, durasi);
            }else if (x == 9){
                    menu();
            }
        }else if (x == 5){
            cout << "Masukkan nama resep yang ingin dihapus: ";
            cin >> nama;
            deleteResep(L, nama);
        }else if (x == 6){
            cout << "Masukkan nama resep yang durasi nya ingin dihapus: ";
            cin >> nama;
            deleteDurasiFromResep(L, nama);
        }else if (x == 7){
            cout << "Masukkan nama resep: ";
            cin >> namaResep;
            p = searchResepByNama(L, namaResep);
            if(p == nullptr){
                cout << "Resep " << namaResep << " tidak ditemukan!" << endl;
            }else{
                if(isEmptyBahan(p)){
                cout << "Resep " << namaResep << " tidak memiliki bahan!" << endl;
                }else{
                    printResep(p);
                    cout << "\n Masukkan nama bahan yang ingin dihapus: ";
                    cin >> nama;
                    deleteBahanFromResep(p,nama);
                }
            }
        }else if (x == 8){
            cout << "Pilih kategori yang ingin dilihat:" << endl;
            cout << "1. Appetizer" << endl;
            cout << "2. Main Course" << endl;
            cout << "3. Dessert " << endl;
            cout << "4. Snack " << endl;
            cout << "Masukkan pilihan anda(1-4): ";
            cin >> x;
            kategori = pilihKategori(x);
            viewResepByCategory(L, kategori);
        }else if (x == 9){
            durasiMinMax(L);
        }else if (x == 10){
            cout << "Masukkan jumlah bahan dari resep: ";
            cin >> jumlah;
            viewResepByJumlahBahan(L,jumlah);
        }else{
            cout << "Masukkan nilai yang valid (1-10): ";
            menu();
        }
        cout << endl;
        menu();
        cin >> x;
    }

    if (x == 0){
        showPenutup();
    }
}

