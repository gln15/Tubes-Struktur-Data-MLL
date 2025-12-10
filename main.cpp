#include <iostream>
#include "MLL.h"

using namespace std;

int main(){
    string nama, kategori,deskripsi;
    int x, durasi, jumlah;
    adrResep p;
    adrBahan q;
    ListR L;
    createList(L);

    menu();
    cin >> x;
    while (x != 0){
        menu();
        cin >> x;
        switch (x){
            case 1:
                    cout << "Masukkan nama resep: ";
                    cin >> nama;
                    cout << "\n Masukkan durasi masak: ";
                    cin >> durasi;
                    cout << "\n Masukkan kategori makanan: ";
                    cin >> kategori;
                    p = createElmResep(nama, durasi, kategori);
                    insertResep(L, p);
            case 2:
                    cout << "Masukkan nama resep ingin ditambah: ";
                    cin >> nama;
                    p = searchResepByNama(L, nama);
                    cout << "\nMasukkan nama bahan: ";
                    cin >> nama;
                    cout << "\nMasukkan jumlah bahan: ";
                    cin >> jumlah;
                    cout << "\nMasukkan deskripsi bahan (gr, pcs, cup): ";
                    cin >> deskripsi;
                    q = createElmBahan(nama, jumlah, deskripsi);
                    insertBahan(p,q);

        }

    }
}
