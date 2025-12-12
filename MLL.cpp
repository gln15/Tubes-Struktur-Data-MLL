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
    cout << "6. Hapus Durasi Dari Resep" << endl;
    cout << "7. Hapus Bahan Dari Resep" << endl;
    cout << "8. View Resep Berdasarkan Kategori" << endl;
    cout << "9. View Resep Tercepat dan Terlama" << endl;
    cout << "10. View Resep Dengan Jumlah Bahan" << endl;
    cout << "0. exit " << endl;
    cout << "\nMasukkan pilihan anda: ";
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
    //cout << "Resep berhasil ditambahkan!" << endl;
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
    //cout << "Bahan berhasil ditambahkan!" << endl;
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
            cout << "Bahan belum tersedia" << endl;
            cout << "---------------------------------------------------" << endl;
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
        cout << "\nTotal Resep: " << countResep(L);
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
    bool bahanDitemukan;
    if(isEmptyResep(L)){
        cout << "Resep tidak ditemukan!" << endl;
    }
    cout << "=== Resep Yang Menggunakan Bahan: " << bahan << " ===" << endl;
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
        }
        p = p->next;
    }
}

void deleteResep(ListR &L, string nama){
    adrResep p;
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
    cout << "Resep " << nama << " berhasil dihapus dari daftar!" << endl;
}

void deleteDurasiFromResep(ListR &L, string nama){
    adrResep p;
    p = searchResepByNama(L, nama);
    if(p == nullptr){
        cout << "Resep " << nama << " tidak ditemukan!" << endl;
    }
    p->info.durasiMasak = 0;
    cout << "Durasi masak dari resep " << nama << " berhasil dihapus! (diatur ke 0 menit)" << endl;
}

void deleteBahanFromResep(adrResep p, string namaBahan){
    adrBahan q, prec;
    bool found;
    q = p->firstBahan;
    prec = nullptr;
    found = false;

    while (q != nullptr && !found){
        if (q->info.namaBahan == namaBahan){
            found = true;
        }else {
            prec = q;
            q = q->next;
        }
    }

    if(found){
        if(prec == nullptr){
            p->firstBahan = q->next;
        }else {
            prec->next = q->next;
        }
        q->next = nullptr;
        cout << "Bahan " << namaBahan << " berhasil dihapus!" << endl;
    }else {
        cout << "Bahan " << namaBahan << " tidak ditemukan pada resep ini!" << endl;
    }
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
    if(isEmptyResep(L)){
        cout << "Resep kosong!";
    }else {
        adrResep p;
        int Min,Max,durasi;
        bool valid;

        p = L.first;
        Min = 9999999;
        Max = 0;
        valid = false;

        while (p != nullptr){
            durasi = p->info.durasiMasak;
            if (durasi > 0){
                valid = true;
                if (durasi < Min){
                    Min = durasi;
                }
                if (durasi > Max){
                    Max = durasi;
                }
            }
            p = p->next;
        }
        if (valid == true){
            cout << "\n=== Resep tercepat dengan " << Min << " menit ===" << endl;
            p = L.first;
            while (p != nullptr){
                if (p->info.durasiMasak == Min){
                    printResep(p);
                }
                p = p->next;
            }

            cout << "\n=== Resep terlama dengan " << Max << " menit ===" << endl;
            p = L.first;
            while (p != nullptr){
                if (p->info.durasiMasak == Max){
                    printResep(p);
                }
                p = p->next;
            }
        }else {
            cout << "Semua resep memiliki durasi 0 (tidak valid)" << endl;
        }
    }
}

void viewResepByJumlahBahan(ListR L, int jumlah){
    adrResep p = L.first;
    adrBahan q;
    int countBahan = 0;
    cout << "=== Resep Dengan Jumlah Bahan: " << jumlah << " ===" << endl;
    while(p != nullptr){
        q = p->firstBahan;
        while(q != nullptr){
            countBahan++;
            q = q->next;
        }
        if(countBahan == jumlah){
            printResep(p);
        }
        p = p->next;
    }
}

string pilihKategori(int x){
    if (x == 1){
        return "Appetizer";
    }else if (x == 2){
        return "Main Course";
    }else if (x == 3){
        return "Dessert";
    }else if (x == 4){
        return "Snack";
    }else{
        cout << "Silahkan pilih kategori yang valid (1-4): ";
        cin >> x;
        return pilihKategori(x);
    }
}

void loadDummyData(ListR &L) {
    adrResep p;

    // --- 1. NASI GORENG (Main_Course) ---
    p = createElmResep("Nasi_Goreng", 15, "Main_Course");
    insertResep(L, p);
    insertBahan(p, createElmBahan("Nasi_Putih", 1, "Piring"));
    insertBahan(p, createElmBahan("Telur", 2, "Butir"));
    insertBahan(p, createElmBahan("Kecap", 2, "Sdm"));

    // --- 2. RENDANG (Main_Course) ---
    p = createElmResep("Rendang_Sapi", 240, "Main_Course");
    insertResep(L, p);
    insertBahan(p, createElmBahan("Daging_Sapi", 1, "Kg"));
    insertBahan(p, createElmBahan("Santan", 2, "Liter"));
    insertBahan(p, createElmBahan("Rempah", 1, "Paket"));

    // --- 3. SATE AYAM (Main_Course) ---
    p = createElmResep("Sate_Ayam", 45, "Main_Course");
    insertResep(L, p);
    insertBahan(p, createElmBahan("Daging_Ayam", 500, "Gr"));
    insertBahan(p, createElmBahan("Kacang_Tanah", 200, "Gr"));
    insertBahan(p, createElmBahan("Tusuk_Sate", 20, "Pcs"));

    // --- 4. GADO-GADO (Main_Course) ---
    p = createElmResep("Gado_Gado", 30, "Main_Course");
    insertResep(L, p);
    insertBahan(p, createElmBahan("Sayuran", 1, "Ikat"));
    insertBahan(p, createElmBahan("Bumbu_Kacang", 1, "Mangkok"));
    insertBahan(p, createElmBahan("Kerupuk", 5, "Pcs"));

    // --- 5. SOTO AYAM (Main_Course) ---
    p = createElmResep("Soto_Ayam", 60, "Main_Course");
    insertResep(L, p);
    insertBahan(p, createElmBahan("Ayam", 1, "Ekor"));
    insertBahan(p, createElmBahan("Bihun", 1, "Bungkus"));
    insertBahan(p, createElmBahan("Kuah_Kuning", 1, "Panci"));

    // --- 6. BAKSO KUAH (Main_Course) ---
    p = createElmResep("Bakso_Sapi", 40, "Main_Course");
    insertResep(L, p);
    insertBahan(p, createElmBahan("Daging_Giling", 500, "Gr"));
    insertBahan(p, createElmBahan("Tepung_Tapioka", 100, "Gr"));

    // --- 7. MIE GORENG (Main_Course) ---
    p = createElmResep("Mie_Goreng_Jawa", 20, "Main_Course");
    insertResep(L, p);
    insertBahan(p, createElmBahan("Mie_Telur", 1, "Bungkus"));
    insertBahan(p, createElmBahan("Sawi", 1, "Ikat"));
    insertBahan(p, createElmBahan("Kecap", 3, "Sdm"));

    // --- 8. AYAM GEPREK (Main_Course) ---
    p = createElmResep("Ayam_Geprek", 35, "Main_Course");
    insertResep(L, p);
    insertBahan(p, createElmBahan("Ayam_Crispy", 1, "Potong"));
    insertBahan(p, createElmBahan("Cabai_Rawit", 10, "Biji"));
    insertBahan(p, createElmBahan("Bawang_Putih", 2, "Siung"));

    // --- 9. RAWON (Main_Course) ---
    p = createElmResep("Rawon", 180, "Main_Course");
    insertResep(L, p);
    insertBahan(p, createElmBahan("Daging_Sandung_Lamur", 500, "Gr"));
    insertBahan(p, createElmBahan("Kluwek", 5, "Buah"));

    // --- 10. SALAD BUAH (Appetizer) ---
    p = createElmResep("Salad_Buah", 10, "Appetizer");
    insertResep(L, p);
    insertBahan(p, createElmBahan("Apel", 2, "Buah"));
    insertBahan(p, createElmBahan("Anggur", 10, "Butir"));
    insertBahan(p, createElmBahan("Mayonaise", 5, "Sdm"));

    // --- 11. SUP KRIM JAGUNG (Appetizer) ---
    p = createElmResep("Sup_Krim_Jagung", 25, "Appetizer");
    insertResep(L, p);
    insertBahan(p, createElmBahan("Jagung_Manis", 2, "Bonggol"));
    insertBahan(p, createElmBahan("Susu_Cair", 200, "Ml"));
    insertBahan(p, createElmBahan("Maizena", 1, "Sdm"));

    // --- 12. BRUSCHETTA (Appetizer) ---
    p = createElmResep("Bruschetta_Tomat", 15, "Appetizer");
    insertResep(L, p);
    insertBahan(p, createElmBahan("Roti_Baguette", 5, "Iris"));
    insertBahan(p, createElmBahan("Tomat", 2, "Buah"));
    insertBahan(p, createElmBahan("Minyak_Zaitun", 1, "Sdm"));

    // --- 13. RISOLES (Snack) ---
    p = createElmResep("Risoles_Mayo", 45, "Snack");
    insertResep(L, p);
    insertBahan(p, createElmBahan("Kulit_Lumpia", 10, "Lembar"));
    insertBahan(p, createElmBahan("Telur_Rebus", 2, "Butir"));
    insertBahan(p, createElmBahan("Mayonaise", 5, "Sdm"));
    insertBahan(p, createElmBahan("Tepung_Roti", 100, "Gr"));

    // --- 14. PISANG GORENG (Snack) ---
    p = createElmResep("Pisang_Goreng", 15, "Snack");
    insertResep(L, p);
    insertBahan(p, createElmBahan("Pisang_Kepok", 1, "Sisir"));
    insertBahan(p, createElmBahan("Tepung_Terigu", 200, "Gr"));
    insertBahan(p, createElmBahan("Gula_Pasir", 2, "Sdm"));

    // --- 15. KENTANG GORENG (Snack) ---
    p = createElmResep("French_Fries", 12, "Snack");
    insertResep(L, p);
    insertBahan(p, createElmBahan("Kentang", 3, "Buah"));
    insertBahan(p, createElmBahan("Garam", 1, "Sdt"));
    insertBahan(p, createElmBahan("Minyak_Goreng", 500, "Ml"));

    // --- 16. MARTABAK MANIS (Dessert) ---
    p = createElmResep("Martabak_Manis", 30, "Dessert");
    insertResep(L, p);
    insertBahan(p, createElmBahan("Tepung_Terigu", 250, "Gr"));
    insertBahan(p, createElmBahan("Gula", 5, "Sdm"));
    insertBahan(p, createElmBahan("Coklat_Meises", 50, "Gr"));
    insertBahan(p, createElmBahan("Keju_Parut", 50, "Gr"));

    // --- 17. KLEPON (Dessert) ---
    p = createElmResep("Klepon", 40, "Dessert");
    insertResep(L, p);
    insertBahan(p, createElmBahan("Tepung_Ketan", 200, "Gr"));
    insertBahan(p, createElmBahan("Gula_Merah", 100, "Gr"));
    insertBahan(p, createElmBahan("Kelapa_Parut", 100, "Gr"));

    // --- 18. ES CAMPUR (Dessert) ---
    p = createElmResep("Es_Campur", 10, "Dessert");
    insertResep(L, p);
}

void showCover() {
    system("cls");

    cout << "\n\n";
    cout << "\t==================================================" << endl;
    cout << "\t||                                              ||" << endl;
    cout << "\t||      APLIKASI MANAJEMEN RESEP MASAKAN        ||" << endl;
    cout << "\t||         (TUGAS BESAR STRUKTUR DATA)          ||" << endl;
    cout << "\t||                                              ||" << endl;
    cout << "\t==================================================" << endl;
    cout << "\t||                                              ||" << endl;
    cout << "\t||  Disusun Oleh Kelompok:                      ||" << endl;
    cout << "\t||                                              ||" << endl;
    cout << "\t||  1. Glen David Hadiono    (103012400106)     ||" << endl;
    cout << "\t||  2. Revalina Rasyiddin    (103012400156)     ||" << endl;
    cout << "\t||                                              ||" << endl;
    cout << "\t==================================================" << endl;
    cout << "\n\t   Selamat Datang! Silakan tekan Enter...";
    cin.get();
    system("cls");
}

void showPenutup() {
     system("cls");
    cout << "\n\n";
    cout << "\t==================================================" << endl;
    cout << "\t||                                              ||" << endl;
    cout << "\t||     TERIMA KASIH TELAH MENGGUNAKAN           ||" << endl;
    cout << "\t||               APLIKASI INI                   ||" << endl;
    cout << "\t||                                              ||" << endl;
    cout << "\t==================================================" << endl;
    cout << "\t||                                              ||" << endl;
    cout << "\t||        Jangan lupa makan hari ini! :)        ||" << endl;
    cout << "\t||                                              ||" << endl;
    cout << "\t==================================================" << endl;
    cout << "\n\n";
}
