#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

struct Barang {
    string kodeBarang;
    string namaBarang;
    double harga;
    int stok;
};

vector<Barang> daftarBarang;

void tampilkanHeader() {
    cout << "\n========================================\n";
    cout << "     SISTEM MANAJEMEN INVENTARIS TOKO   \n";
    cout << "========================================\n";
}

void tampilkanMenu() {
    cout << "\n--- MENU UTAMA ---\n";
    cout << "1. Tambah Barang\n";
    cout << "2. Tampilkan Semua Barang\n";
    cout << "3. Cari Barang Termahal\n";
    cout << "4. Hitung Total Nilai Inventaris\n";
    cout << "5. Cek Restock (Stok < 5)\n";
    cout << "6. Update Stok\n";
    cout << "7. Keluar\n";
    cout << "Pilihan: ";
}

bool kodeBarangSudahAda(const string &kode) {
    for (int i = 0; i < (int)daftarBarang.size(); i++) {
        if (daftarBarang[i].kodeBarang == kode) return true;
    }
    return false;
}

void tambahBarang() {
    Barang b;

    cout << "\n--- TAMBAH BARANG ---\n";

    cout << "Kode Barang : ";
    cin >> b.kodeBarang;

    if (kodeBarangSudahAda(b.kodeBarang)) {
        cout << "[ERROR] Kode barang sudah ada!\n";
        return;
    }

    cin.ignore();
    cout << "Nama Barang : ";
    getline(cin, b.namaBarang);

    while (true) {
        cout << "Harga       : ";
        if (cin >> b.harga && b.harga >= 0) break;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "[ERROR] Harga tidak boleh negatif. Masukkan ulang.\n";
    }

    while (true) {
        cout << "Stok        : ";
        if (cin >> b.stok && b.stok >= 0) break;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "[ERROR] Stok tidak boleh negatif. Masukkan ulang.\n";
    }

    daftarBarang.push_back(b);
    cout << "[SUKSES] Barang berhasil ditambahkan!\n";
}

void tampilkanSemuaBarang() {
    cout << "\n--- DAFTAR SEMUA BARANG ---\n";

    if (daftarBarang.empty()) {
        cout << "Belum ada barang dalam inventaris.\n";
        return;
    }

    cout << left
         << setw(12) << "Kode"
         << setw(25) << "Nama Barang"
         << setw(15) << "Harga (Rp)"
         << setw(8)  << "Stok"
         << "\n";
    cout << string(60, '-') << "\n";

    for (int i = 0; i < (int)daftarBarang.size(); i++) {
        cout << left
             << setw(12) << daftarBarang[i].kodeBarang
             << setw(25) << daftarBarang[i].namaBarang
             << setw(15) << fixed << setprecision(0) << daftarBarang[i].harga
             << setw(8)  << daftarBarang[i].stok
             << "\n";
    }
    cout << string(60, '-') << "\n";
}

void cariBarangTermahal() {
    cout << "\n--- BARANG TERMAHAL ---\n";

    if (daftarBarang.empty()) {
        cout << "Belum ada barang dalam inventaris.\n";
        return;
    }

    int indexTermahal = 0;
    for (int i = 1; i < (int)daftarBarang.size(); i++) {
        if (daftarBarang[i].harga > daftarBarang[indexTermahal].harga) {
            indexTermahal = i;
        }
    }

    Barang &b = daftarBarang[indexTermahal];
    cout << "Kode Barang : " << b.kodeBarang  << "\n";
    cout << "Nama Barang : " << b.namaBarang  << "\n";
    cout << "Harga       : Rp " << fixed << setprecision(0) << b.harga << "\n";
    cout << "Stok        : " << b.stok << "\n";
}

void hitungTotalNilaiInventaris() {
    cout << "\n--- TOTAL NILAI INVENTARIS ---\n";

    if (daftarBarang.empty()) {
        cout << "Belum ada barang dalam inventaris.\n";
        return;
    }

    double total = 0;
    for (int i = 0; i < (int)daftarBarang.size(); i++) {
        total += daftarBarang[i].harga * daftarBarang[i].stok;
    }

    cout << "Total Nilai Inventaris: Rp " << fixed << setprecision(0) << total << "\n";
}

void cekRestock() {
    cout << "\n--- BARANG PERLU RESTOCK (Stok < 5) ---\n";

    if (daftarBarang.empty()) {
        cout << "Belum ada barang dalam inventaris.\n";
        return;
    }

    bool adaRestock = false;

    cout << left
         << setw(12) << "Kode"
         << setw(25) << "Nama Barang"
         << setw(8)  << "Stok"
         << "\n";
    cout << string(45, '-') << "\n";

    for (int i = 0; i < (int)daftarBarang.size(); i++) {
        if (daftarBarang[i].stok < 5) {
            cout << left
                 << setw(12) << daftarBarang[i].kodeBarang
                 << setw(25) << daftarBarang[i].namaBarang
                 << setw(8)  << daftarBarang[i].stok
                 << "\n";
            adaRestock = true;
        }
    }

    if (!adaRestock) {
        cout << "Semua barang memiliki stok yang cukup.\n";
    } else {
        cout << string(45, '-') << "\n";
    }
}

void updateStok() {
    cout << "\n--- UPDATE STOK ---\n";

    if (daftarBarang.empty()) {
        cout << "Belum ada barang dalam inventaris.\n";
        return;
    }

    string kode;
    cout << "Masukkan Kode Barang: ";
    cin >> kode;

    int *pStok = nullptr;
    string namaBarang;

    for (int i = 0; i < (int)daftarBarang.size(); i++) {
        if (daftarBarang[i].kodeBarang == kode) {
            pStok = &daftarBarang[i].stok;
            namaBarang = daftarBarang[i].namaBarang;
            break;
        }
    }

    if (pStok == nullptr) {
        cout << "[ERROR] Barang dengan kode '" << kode << "' tidak ditemukan.\n";
        return;
    }

    cout << "Barang     : " << namaBarang << "\n";
    cout << "Stok saat ini: " << *pStok << "\n";
    cout << "1. Tambah Stok\n";
    cout << "2. Kurangi Stok\n";
    cout << "Pilihan: ";

    int pilihan;
    cin >> pilihan;

    int jumlah;
    if (pilihan == 1) {
        cout << "Jumlah yang ditambah: ";
        while (true) {
            if (cin >> jumlah && jumlah >= 0) break;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "[ERROR] Jumlah tidak valid. Masukkan ulang: ";
        }
        *pStok += jumlah;
        cout << "[SUKSES] Stok berhasil ditambah. Stok sekarang: " << *pStok << "\n";

    } else if (pilihan == 2) {
        cout << "Jumlah yang dikurangi: ";
        while (true) {
            if (cin >> jumlah && jumlah >= 0) break;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "[ERROR] Jumlah tidak valid. Masukkan ulang: ";
        }
        if (jumlah > *pStok) {
            cout << "[ERROR] Stok tidak mencukupi! Stok saat ini hanya " << *pStok << ".\n";
        } else {
            *pStok -= jumlah;
            cout << "[SUKSES] Stok berhasil dikurangi. Stok sekarang: " << *pStok << "\n";
        }

    } else {
        cout << "[ERROR] Pilihan tidak valid.\n";
    }
}

int main() {
    tampilkanHeader();

    int pilihan;

    while (true) {
        tampilkanMenu();

        if (!(cin >> pilihan)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "[ERROR] Input tidak valid.\n";
            continue;
        }

        switch (pilihan) {
            case 1: tambahBarang();              break;
            case 2: tampilkanSemuaBarang();      break;
            case 3: cariBarangTermahal();        break;
            case 4: hitungTotalNilaiInventaris();break;
            case 5: cekRestock();                break;
            case 6: updateStok();                break;
            case 7:
                cout << "\nTerima kasih. Program selesai.\n\n";
                return 0;
            default:
                cout << "[ERROR] Pilihan tidak tersedia. Pilih 1-7.\n";
        }
    }

    return 0;
}
