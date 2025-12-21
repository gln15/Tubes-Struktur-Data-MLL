#include <iostream>
#include "MLL.h"
#include "iomanip"
using namespace std;
void menu(){
    cout << "1.  Tambah Resep " << endl;
    cout << "2.  Tambah Bahan " << endl;
    cout << "3.  View All" << endl;
    cout << "4.  Cari Resep" << endl;
    cout << "5.  Hapus Resep" << endl;
    cout << "6.  Hapus Durasi Dari Resep" << endl;
    cout << "7.  Hapus Bahan Dari Resep" << endl;
    cout << "8.  View Resep Berdasarkan Kategori" << endl;
    cout << "9.  View Resep Tercepat dan Terlama" << endl;
    cout << "10. View Resep Dengan Jumlah Bahan" << endl;
    cout << "11. Update Durasi Resep" << endl;
    cout << "12. Update Kategori Resep" << endl;
    cout << "0.  exit " << endl;
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
        if (p->info.durasiMasak <= 0){
            cout << "Durasi Masak : TIDAK TERSEDIA" << endl;
        } else {
            cout << "Durasi Masak : " << p->info.durasiMasak << " Menit" << endl;
        }
        cout << "Kategori : " << p->info.kategori << endl;
        if (isEmptyBahan(p)){
            cout << "BAHAN BELUM TERSEDIA" << endl;
            cout << "---------------------------------------------------" << endl;
        }else{
            cout << " --------------------------------" << endl;
            cout << " |\t      BAHAN             |" << endl;
            cout << " --------------------------------" << endl;
            while (q != nullptr){
                string teks;
                teks = q->info.namaBahan + " " + to_string(q->info.jumlahBahan) + " " + q->info.deskripsi;
                cout << " | " ;
                cout << left << setw(29) << teks;
                cout << "|" << endl;
                q = q->next;
            }
                cout << " --------------------------------" << endl;
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
        cout << "\nTOTAL RESEP: " << countResep(L);
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
    bool found;
    if (isEmptyResep(L)){
        cout << "Resep dengan durasi " << durasi << " menit tidak ditemukan!" << endl;
    }else {
        adrResep p;
        p = L.first;
        while (p != nullptr){
            if (p->info.durasiMasak <= durasi){
                printResep(p);
                found = true;
            }
            p = p->next;
        }
        if (!found){
            cout << "Resep dengan durasi " << durasi << " menit tidak ditemukan!" << endl;
            cout << "Sepertinya kamu terlalu sibuk ya?" << endl;
            cout << "Mau coba masukkan waktu yang lebih lama? (Y/N): ";
            cin >> option;
            if (option == "Y" || option == "y"){
                int New;
                cout << "Masukkan perkiraan waktu yang kamu miliki (menit): ";
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
    bool bahanDitemukan, resepDitemukan;
    resepDitemukan = false;
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
            if(!resepDitemukan){
                cout << "=== Resep Yang Menggunakan Bahan '" << bahan << "' ===" << endl;
            }
            printResep(p);
            resepDitemukan = true;
        }
        p = p->next;
    }
    if(!resepDitemukan){
        cout << "Resep dengan bahan '" << bahan << "' tidak ditemukan" << endl;
    }
}

void deleteResep(ListR &L, string nama){
    adrResep p;
    string konfirmasi;
    p = searchResepByNama(L, nama);
    if(p == nullptr){
        cout << "Resep '" << nama << "' tidak ditemukan!" << endl;
        return;
    }

    cout << "Apakah anda yakin ingin menghapus resep '" << nama << "'? (y/n): ";
    cin >> konfirmasi;
    if(konfirmasi == "n" || konfirmasi == "N"){
        cout << "Penghapusan resep dibatalkan" << endl;
        return;
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
    cout << "Resep '" << nama << "' telah dihapus dari daftar!" << endl;
}

void deleteDurasiFromResep(ListR &L, string nama){
    adrResep p;
    string konfirmasi;
    p = searchResepByNama(L, nama);
    if(p == nullptr){
        cout << "Resep '" << nama << "' tidak ditemukan!" << endl;
        return;
    }

    cout << "Apakah anda yakin ingin menghapus durasi masak resep '" << nama << "'? (y/n): ";
    cin >> konfirmasi;
    if(konfirmasi == "n" || konfirmasi == "N"){
        cout << "Penghapusan durasi dibatalkan" << endl;
        return;
    }

    p->info.durasiMasak = 0;
    cout << "Durasi masak dari resep '" << nama << "' telah dihapus!" << endl;
    printResep(p);
}

void deleteBahanFromResep(adrResep p, string namaBahan){
    adrBahan q, prec;
    string konfirmasi;
    if(p == nullptr){
        cout << "Resep tidak valid!" << endl;
        return;
    }

    q = p->firstBahan;
    prec = nullptr;
    while(q != nullptr && q->info.namaBahan != namaBahan){
        prec = q;
        q = q->next;
    }
     if(q == nullptr){
        cout << "Bahan '" << namaBahan << "' tidak ditemukan pada resep ini!" << endl;
        return;
    }

    cout << "Apakah anda yakin ingin menghapus bahan '"<< namaBahan << "'? (y/n): ";
    cin >> konfirmasi;
    if(konfirmasi == "n" || konfirmasi == "N"){
        cout << "Penghapusan bahan dibatalkan" << endl;
        return;
    }

    if(prec == nullptr){
        p->firstBahan = q->next;
    } else {
        prec->next = q->next;
    }
    q->next = nullptr;
    cout << "Bahan '" << namaBahan << "' berhasil dihapus!" << endl;
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
            cout << "\n=== RESEP TERCEPAT dengan durasi " << Min << " menit ===" << endl;
            p = L.first;
            while (p != nullptr){
                if (p->info.durasiMasak == Min){
                    printResep(p);
                }
                p = p->next;
            }

            cout << "\n=== RESEP TERLAMA dengan durasi " << Max << " menit ===" << endl;
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
    adrResep p;
    adrBahan q;
    bool found;
    int countBahan;
    p = L.first;
    found = false;
    while(p != nullptr){
        countBahan = 0;
        q = p->firstBahan;
        while(q != nullptr){
            countBahan++;
            q = q->next;
        }
        if(countBahan == jumlah){
            if(!found){
                cout << "=== Resep Yang Memiliki " << jumlah << " Bahan ===" << endl;
            }
            printResep(p);
            found = true;
        }
        p = p->next;
    }
    if(!found){
        cout << "Tidak ada resep yang memiliki " << jumlah << " bahan" << endl;
    }
}

string pilihKategori(int x){
    if (x == 1){
        return "Appetizer";
    }else if (x == 2){
        return "Main_Course";
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

    // ==========================================
    // BAGIAN 1: DATA LAMA (SEDERHANA)
    // ==========================================

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
    insertBahan(p, createElmBahan("Santan_Kental", 1, "Liter"));
    insertBahan(p, createElmBahan("Santan_Cair", 1, "Liter"));
    insertBahan(p, createElmBahan("Lengkuas", 2, "Ruas"));
    insertBahan(p, createElmBahan("Daun_Kunyit", 1, "Lembar"));

    // --- 3. SATE AYAM (Main_Course) ---
    p = createElmResep("Sate_Ayam", 45, "Main_Course");
    insertResep(L, p);
    insertBahan(p, createElmBahan("Daging_Ayam", 500, "Gr"));
    insertBahan(p, createElmBahan("Kacang_Tanah", 200, "Gr"));
    insertBahan(p, createElmBahan("Tusuk_Sate", 20, "Pcs"));
    insertBahan(p, createElmBahan("Jeruk_Limo", 2, "Buah"));

    // --- 4. GADO-GADO (Main_Course) ---
    p = createElmResep("Gado_Gado", 30, "Main_Course");
    insertResep(L, p);
    insertBahan(p, createElmBahan("Bayam", 1, "Ikat"));
    insertBahan(p, createElmBahan("Tauge", 100, "Gr"));
    insertBahan(p, createElmBahan("Bumbu_Kacang", 1, "Mangkok"));
    insertBahan(p, createElmBahan("Kerupuk_Udang", 5, "Pcs"));

    // --- 5. SOTO AYAM (Main_Course) ---
    p = createElmResep("Soto_Ayam", 60, "Main_Course");
    insertResep(L, p);
    insertBahan(p, createElmBahan("Ayam_Kampung", 1, "Ekor"));
    insertBahan(p, createElmBahan("Bihun_Jagung", 1, "Bungkus"));
    insertBahan(p, createElmBahan("Kunyit", 3, "Ruas"));
    insertBahan(p, createElmBahan("Serai", 2, "Batang"));

    // --- 6. BAKSO KUAH (Main_Course) ---
    p = createElmResep("Bakso_Sapi", 40, "Main_Course");
    insertResep(L, p);
    insertBahan(p, createElmBahan("Daging_Giling", 500, "Gr"));
    insertBahan(p, createElmBahan("Tepung_Tapioka", 100, "Gr"));
    insertBahan(p, createElmBahan("Es_Batu", 50, "Gr"));

    // --- 7. MIE GORENG (Main_Course) ---
    p = createElmResep("Mie_Goreng_Jawa", 20, "Main_Course");
    insertResep(L, p);
    insertBahan(p, createElmBahan("Mie_Telur", 1, "Bungkus"));
    insertBahan(p, createElmBahan("Sawi_Hijau", 1, "Ikat"));
    insertBahan(p, createElmBahan("Kecap_Manis", 3, "Sdm"));
    insertBahan(p, createElmBahan("Bakso_Iris", 5, "Pcs"));

    // --- 8. AYAM GEPREK (Main_Course) ---
    p = createElmResep("Ayam_Geprek", 35, "Main_Course");
    insertResep(L, p);
    insertBahan(p, createElmBahan("Ayam_Potong", 1, "Pcs"));
    insertBahan(p, createElmBahan("Tepung_Serbaguna", 100, "Gr"));
    insertBahan(p, createElmBahan("Cabai_Rawit_Merah", 15, "Biji"));
    insertBahan(p, createElmBahan("Bawang_Putih", 3, "Siung"));

    // --- 9. RAWON (Main_Course) ---
    p = createElmResep("Rawon_Setan", 180, "Main_Course");
    insertResep(L, p);
    insertBahan(p, createElmBahan("Daging_Sandung_Lamur", 500, "Gr"));
    insertBahan(p, createElmBahan("Kluwek", 5, "Buah"));
    insertBahan(p, createElmBahan("Tauge_Pendek", 100, "Gr"));

    // --- 10. SALAD BUAH (Appetizer) ---
    p = createElmResep("Salad_Buah", 10, "Appetizer");
    insertResep(L, p);
    insertBahan(p, createElmBahan("Apel_Fuji", 2, "Buah"));
    insertBahan(p, createElmBahan("Anggur_Hitam", 10, "Butir"));
    insertBahan(p, createElmBahan("Mayonaise", 5, "Sdm"));
    insertBahan(p, createElmBahan("Keju_Cheddar", 50, "Gr"));

    // --- 11. SUP KRIM JAGUNG (Appetizer) ---
    p = createElmResep("Sup_Krim_Jagung", 25, "Appetizer");
    insertResep(L, p);
    insertBahan(p, createElmBahan("Jagung_Manis_Pipil", 200, "Gr"));
    insertBahan(p, createElmBahan("Susu_Full_Cream", 250, "Ml"));
    insertBahan(p, createElmBahan("Tepung_Maizena", 1, "Sdm"));
    insertBahan(p, createElmBahan("Parsley", 1, "Sdt"));

    // --- 12. BRUSCHETTA (Appetizer) ---
    p = createElmResep("Bruschetta", 15, "Appetizer");
    insertResep(L, p);
    insertBahan(p, createElmBahan("Roti_Baguette", 6, "Iris"));
    insertBahan(p, createElmBahan("Tomat_Merah", 2, "Buah"));
    insertBahan(p, createElmBahan("Minyak_Zaitun", 2, "Sdm"));
    insertBahan(p, createElmBahan("Basil", 3, "Lembar"));

    // --- 13. RISOLES (Snack) ---
    p = createElmResep("Risoles_Mayo", 45, "Snack");
    insertResep(L, p);
    insertBahan(p, createElmBahan("Kulit_Lumpia", 10, "Lembar"));
    insertBahan(p, createElmBahan("Smoked_Beef", 2, "Lembar"));
    insertBahan(p, createElmBahan("Telur_Rebus", 2, "Butir"));
    insertBahan(p, createElmBahan("Mayonaise", 5, "Sdm"));
    insertBahan(p, createElmBahan("Tepung_Panir", 150, "Gr"));

    // --- 14. PISANG GORENG (Snack) ---
    p = createElmResep("Pisang_Goreng_Pasir", 20, "Snack");
    insertResep(L, p);
    insertBahan(p, createElmBahan("Pisang_Kepok", 1, "Sisir"));
    insertBahan(p, createElmBahan("Tepung_Terigu", 200, "Gr"));
    insertBahan(p, createElmBahan("Tepung_Roti_Kasar", 100, "Gr"));
    insertBahan(p, createElmBahan("Susu_Kental_Manis", 1, "Sachet"));

    // --- 15. KENTANG GORENG (Snack) ---
    p = createElmResep("French_Fries", 12, "Snack");
    insertResep(L, p);
    insertBahan(p, createElmBahan("Kentang_Shoestring", 500, "Gr"));
    insertBahan(p, createElmBahan("Garam_Himalaya", 1, "Sdt"));
    insertBahan(p, createElmBahan("Minyak_Goreng", 500, "Ml"));

    // --- 16. MARTABAK MANIS (Dessert) ---
    p = createElmResep("Martabak_Manis", 30, "Dessert");
    insertResep(L, p);
    insertBahan(p, createElmBahan("Tepung_Segitiga", 250, "Gr"));
    insertBahan(p, createElmBahan("Soda_Kue", 1, "Sdt"));
    insertBahan(p, createElmBahan("Gula_Pasir", 5, "Sdm"));
    insertBahan(p, createElmBahan("Coklat_Meises", 50, "Gr"));
    insertBahan(p, createElmBahan("Kacang_Sangrai", 50, "Gr"));

    // --- 17. KLEPON (Dessert) ---
    p = createElmResep("Klepon_Pandan", 40, "Dessert");
    insertResep(L, p);
    insertBahan(p, createElmBahan("Tepung_Ketan", 200, "Gr"));
    insertBahan(p, createElmBahan("Pasta_Pandan", 1, "Sdt"));
    insertBahan(p, createElmBahan("Gula_Merah", 100, "Gr"));
    insertBahan(p, createElmBahan("Kelapa_Parut_Kukus", 100, "Gr"));

    // --- 18. ES CAMPUR (Dessert) ---
    p = createElmResep("Es_Campur_Oyen", 10, "Dessert");
    insertResep(L, p);
    insertBahan(p, createElmBahan("Es_Serut", 1, "Mangkok"));
    insertBahan(p, createElmBahan("Alpukat", 1, "Buah"));
    insertBahan(p, createElmBahan("Kelapa_Muda", 1, "Butir"));
    insertBahan(p, createElmBahan("Nangka", 5, "Biji"));
    insertBahan(p, createElmBahan("Susu_Kental_Manis", 3, "Sdm"));

    // ==========================================
    // BAGIAN 2: DATA BARU (LEBIH KOMPLEKS)
    // ==========================================

    // --- 19. LASAGNA (Main_Course - Kompleks) ---
    p = createElmResep("Lasagna_Beef", 90, "Main_Course");
    insertResep(L, p);
    insertBahan(p, createElmBahan("Pasta_Lasagna", 6, "Lembar"));
    insertBahan(p, createElmBahan("Daging_Giling", 300, "Gr"));
    insertBahan(p, createElmBahan("Saus_Bolognese", 1, "Botol"));
    insertBahan(p, createElmBahan("Susu_Cair", 500, "Ml"));
    insertBahan(p, createElmBahan("Keju_Mozzarella", 200, "Gr"));
    insertBahan(p, createElmBahan("Keju_Parmesan", 50, "Gr"));

    // --- 20. SUSHI ROLL (Main_Course - Kompleks) ---
    p = createElmResep("Salmon_Sushi_Roll", 60, "Main_Course");
    insertResep(L, p);
    insertBahan(p, createElmBahan("Beras_Jepang", 300, "Gr"));
    insertBahan(p, createElmBahan("Cuka_Beras", 2, "Sdm"));
    insertBahan(p, createElmBahan("Nori", 5, "Lembar"));
    insertBahan(p, createElmBahan("Salmon_Sashimi", 200, "Gr"));
    insertBahan(p, createElmBahan("Alpukat", 1, "Buah"));
    insertBahan(p, createElmBahan("Kecap_Asin", 1, "Botol"));

    // --- 21. OPOR AYAM (Main_Course - Tradisional) ---
    p = createElmResep("Opor_Ayam_Kuning", 75, "Main_Course");
    insertResep(L, p);
    insertBahan(p, createElmBahan("Ayam_Potong", 1, "Ekor"));
    insertBahan(p, createElmBahan("Santan_Kental", 500, "Ml"));
    insertBahan(p, createElmBahan("Kemiri", 5, "Butir"));
    insertBahan(p, createElmBahan("Ketumbar", 1, "Sdt"));
    insertBahan(p, createElmBahan("Serai", 2, "Batang"));
    insertBahan(p, createElmBahan("Daun_Jeruk", 3, "Lembar"));

    // --- 22. ZUPPA SOUP (Appetizer - Kompleks) ---
    p = createElmResep("Zuppa_Soup", 45, "Appetizer");
    insertResep(L, p);
    insertBahan(p, createElmBahan("Puff_Pastry", 4, "Lembar"));
    insertBahan(p, createElmBahan("Daging_Ayam_Dadu", 100, "Gr"));
    insertBahan(p, createElmBahan("Jamur_Kancing", 5, "Pcs"));
    insertBahan(p, createElmBahan("Bawang_Bombay", 1, "Buah"));
    insertBahan(p, createElmBahan("Cooking_Cream", 100, "Ml"));

    // --- 23. LUMPIA SEMARANG (Appetizer - Tradisional) ---
    p = createElmResep("Lumpia_Semarang", 60, "Appetizer");
    insertResep(L, p);
    insertBahan(p, createElmBahan("Kulit_Lumpia", 10, "Lembar"));
    insertBahan(p, createElmBahan("Rebung", 200, "Gr"));
    insertBahan(p, createElmBahan("Udang_Cincang", 100, "Gr"));
    insertBahan(p, createElmBahan("Telur_Orak_Arik", 2, "Butir"));
    insertBahan(p, createElmBahan("Saus_Tauco", 1, "Mangkok"));

    // --- 24. DIMSUM (Snack - Kukus) ---
    p = createElmResep("Dimsum_Ayam_Udang", 40, "Snack");
    insertResep(L, p);
    insertBahan(p, createElmBahan("Kulit_Pangsit", 15, "Lembar"));
    insertBahan(p, createElmBahan("Paha_Ayam_Fillet", 300, "Gr"));
    insertBahan(p, createElmBahan("Udang_Kupas", 100, "Gr"));
    insertBahan(p, createElmBahan("Tepung_Tapioka", 3, "Sdm"));
    insertBahan(p, createElmBahan("Minyak_Wijen", 1, "Sdm"));
    insertBahan(p, createElmBahan("Wortel_Parut", 1, "Buah"));

    // --- 25. NACHOS (Snack - Western) ---
    p = createElmResep("Beef_Nachos", 20, "Snack");
    insertResep(L, p);
    insertBahan(p, createElmBahan("Keripik_Tortilla", 1, "Bungkus"));
    insertBahan(p, createElmBahan("Daging_Cincang", 150, "Gr"));
    insertBahan(p, createElmBahan("Saus_Salsa", 1, "Jar"));
    insertBahan(p, createElmBahan("Saus_Keju", 100, "Ml"));
    insertBahan(p, createElmBahan("Jalapeno", 5, "Iris"));

    // --- 26. SEBLAK (Snack - Pedas) ---
    p = createElmResep("Seblak_Komplit", 25, "Snack");
    insertResep(L, p);
    insertBahan(p, createElmBahan("Kerupuk_Oren", 1, "Genggam"));
    insertBahan(p, createElmBahan("Kencur", 2, "Ruas"));
    insertBahan(p, createElmBahan("Cabai_Rawit", 15, "Biji"));
    insertBahan(p, createElmBahan("Sosis", 2, "Pcs"));
    insertBahan(p, createElmBahan("Bakso", 3, "Pcs"));
    insertBahan(p, createElmBahan("Telur", 1, "Butir"));

    // --- 27. TIRAMISU (Dessert - Kompleks) ---
    p = createElmResep("Tiramisu_Cake", 120, "Dessert");
    insertResep(L, p);
    insertBahan(p, createElmBahan("Biskuit_Lady_Finger", 1, "Pack"));
    insertBahan(p, createElmBahan("Keju_Mascarpone", 250, "Gr"));
    insertBahan(p, createElmBahan("Kopi_Espresso", 1, "Gelas"));
    insertBahan(p, createElmBahan("Coklat_Bubuk", 2, "Sdm"));
    insertBahan(p, createElmBahan("Telur_Kuning", 3, "Butir"));
    insertBahan(p, createElmBahan("Gula_Halus", 50, "Gr"));

    // --- 28. RED VELVET (Dessert - Baking) ---
    p = createElmResep("Red_Velvet_Cupcake", 50, "Dessert");
    insertResep(L, p);
    insertBahan(p, createElmBahan("Tepung_Terigu", 200, "Gr"));
    insertBahan(p, createElmBahan("Pewarna_Merah", 1, "Sdt"));
    insertBahan(p, createElmBahan("Buttermilk", 100, "Ml"));
    insertBahan(p, createElmBahan("Cream_Cheese", 100, "Gr"));
    insertBahan(p, createElmBahan("Butter", 100, "Gr"));

    // --- 29. KOLAK PISANG (Dessert - Tradisional) ---
    p = createElmResep("Kolak_Pisang_Ubi", 40, "Dessert");
    insertResep(L, p);
    insertBahan(p, createElmBahan("Pisang_Tanduk", 2, "Buah"));
    insertBahan(p, createElmBahan("Ubi_Jalar", 2, "Buah"));
    insertBahan(p, createElmBahan("Santan", 500, "Ml"));
    insertBahan(p, createElmBahan("Gula_Merah", 200, "Gr"));
    insertBahan(p, createElmBahan("Daun_Pandan", 2, "Lembar"));

    // --- 30. TOM YUM (Main_Course - Asian) ---
    p = createElmResep("Tom_Yum_Seafood", 35, "Main_Course");
    insertResep(L, p);
    insertBahan(p, createElmBahan("Udang_Galah", 5, "Ekor"));
    insertBahan(p, createElmBahan("Cumi_Cumi", 2, "Ekor"));
    insertBahan(p, createElmBahan("Jamur_Merang", 100, "Gr"));
    insertBahan(p, createElmBahan("Pasta_Tom_Yum", 2, "Sdm"));
    insertBahan(p, createElmBahan("Jeruk_Nipis", 1, "Buah"));
    insertBahan(p, createElmBahan("Kecap_Ikan", 1, "Sdm"));
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

void updateKategoriResep(ListR &L, string namaResep){
    adrResep p;
    string kategoriLama, kategoriBaru, konfirmasi;
    int x;
    p = searchResepByNama(L, namaResep);

    kategoriLama = p->info.kategori;
    cout << "-------------------------------------------" << endl;
    cout << "Kategori Saat Ini : " << kategoriLama << endl;
    cout << "-------------------------------------------" << endl;
    cout << "Pilih Kategori Baru (Selain " << kategoriLama << "):" << endl;

    if (kategoriLama != "Appetizer"){
        cout << "1. Appetizer" << endl;
    }
    if (kategoriLama != "Main_Course"){
        cout << "2. Main Course" << endl;
    }
    if (kategoriLama != "Dessert"){
        cout << "3. Dessert" << endl;
    }
    if (kategoriLama != "Snack"){
        cout << "4. Snack" << endl;
    }
    cout << "Masukkan pilihan anda (angka): ";
    cin >> x;
    cout << "Apakah anda yakin ingin mengupdate kategori resep '" << namaResep << "'? (y/n): ";
    cin >> konfirmasi;
    if(konfirmasi == "n" || konfirmasi == "Y"){
        cout << "Kategori tidak jadi diupdate" << endl;
        return;
    }

    kategoriBaru = pilihKategori(x);
    if (kategoriBaru == kategoriLama || x < 1 || x > 4) {
        cout << "[GAGAL] Pilihan tidak valid atau sama dengan kategori lama!" << endl;
    } else {
        // UPDATE DATA DI SINI
        p->info.kategori = kategoriBaru;
        cout << "[SUKSES] Kategori berhasil diubah menjadi: " << kategoriBaru << endl;
    }
}

void showNamaResep(ListR L){
    if (isEmptyResep(L)){
        cout << "Daftar Resep Masih Kosong!" << endl;
    }else {
        adrResep p;
        int i;
        i = 1;
        cout << "\n=== DAFTAR NAMA RESEP ===" << endl;
        p = L.first;
        while (p != nullptr){
            cout << i << ". " << p->info.namaResep << endl;
            p = p->next;
            i++;
        }
       cout << "=========================" << endl;
    }
}
