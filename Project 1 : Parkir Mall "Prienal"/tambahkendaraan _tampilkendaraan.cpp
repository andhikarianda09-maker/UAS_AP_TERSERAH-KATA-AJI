#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <ctime>
using namespace std;

// ===================== STRUCT =====================

struct Kendaraan {
    string platMobil;
    string merkMobil;
    string warnaMobil;
    time_t waktuMasuk;
};

struct Petugas {
    string nama;
    string id;
};

// ===================== GLOBAL VARIABLE =====================

const int KAPASITAS_MAX = 20;
vector<Kendaraan*> daftarParkir; 

// ===================== FUNCTION DECLARATIONS =====================

void tampilHeader();
void inputPetugas(Petugas &p);
void tampilMenu(const Petugas &p);
void tambahKendaraan();
void tampilKendaraan();
void pembayaran();         // TODO: dikerjakan Anggota 3
string formatWaktu(double detik);   // TODO: dikerjakan Anggota 3
double hitungDurasi(time_t masuk);  // TODO: dikerjakan Anggota 3
double hitungBiaya(double detikParkir); // TODO: dikerjakan Anggota 3

// ===================== FUNGSI TAMPIL HEADER =====================

void tampilHeader() {
    cout << "\n";
    cout << string(60, '-') << "\n";
    cout << "              --- SELAMAT DATANG ---\n";
    cout << "          DI PORTAL PARKIR KHUSUS MOBIL\n";
    cout << "                  MALL PRIENAL\n";
    cout << string(60, '-') << "\n\n";
    cout << "Kami senang Anda telah hadir.\n";
    cout << "Sebelum melanjutkan, silahkan masukkan informasi Anda\n";
    cout << "yang akan bertugas hari ini.\n\n";
}

// ===================== FUNGSI INPUT PETUGAS =====================

void inputPetugas(Petugas &p) {
    cout << "Masukkan nama  : ";
    getline(cin, p.nama);
    cout << "Masukkan ID    : ";
    getline(cin, p.id);

    cout << "\n";
    cout << string(60, '-') << "\n";
    cout << "  Nama Petugas : " << p.nama << "\n";
    cout << "  ID Petugas   : " << p.id << "\n";
    cout << string(60, '-') << "\n";
    cout << "         TERIMA KASIH ATAS KERJASAMANYA !\n";
    cout << "            --- SELAMAT BERTUGAS ---\n";
    cout << string(60, '-') << "\n\n";
}

// ===================== FUNGSI TAMPIL MENU =====================

void tampilMenu(const Petugas &p) {
    cout << "\nSilahkan input opsi berikut dalam bentuk angka.\n";
    cout << "1. Tambahkan Daftar Kendaraan\n";
    cout << "2. Tampilkan Daftar Kendaraan\n";
    cout << "3. Pembayaran\n";
    cout << "4. Keluar Program\n";
}

// ===================== MAIN =====================

int main() {
    tampilHeader();

    Petugas petugas;
    inputPetugas(petugas);

    int opsi;
    do {
        tampilMenu(petugas);
        cout << "Masukkan opsi : ";
        cin >> opsi;
        cin.ignore();

        switch (opsi) {
            case 1:
                tambahKendaraan();
                break;
            case 2:
                tampilKendaraan();
                break;
            case 3:
                pembayaran();
                break;
            case 4:
                cout << "\n";
                cout << string(60, '-') << "\n";
                cout << "          TERIMA KASIH TELAH MENGGUNAKAN SISTEM\n";
                cout << "               PARKIR MALL PRIENAL :)\n";
                cout << string(60, '-') << "\n";
                break;
            default:
                cout << "Opsi tidak valid! Silakan masukkan angka 1-4.\n";
        }
    } while (opsi != 4);

    for (int i = 0; i < (int)daftarParkir.size(); i++) {
        delete daftarParkir[i];
    }
    daftarParkir.clear();

    return 0;
}

// ===================== FUNGSI TAMBAH KENDARAAN =====================

void tambahKendaraan() {
    int jumlah;
    cout << "Masukkan jumlah mobil yang akan di parkirkan : ";
    cin >> jumlah;
    cin.ignore();

    int slotTersedia = KAPASITAS_MAX - (int)daftarParkir.size();
    if (jumlah > slotTersedia) {
        cout << "Maaf, parkiran hanya dapat memuat " << KAPASITAS_MAX << " mobil !\n";
        if (slotTersedia <= 0) {
            cout << "Parkiran sudah penuh!\n";
            return;
        }
        jumlah = slotTersedia;
        cout << "Hanya dapat menambahkan " << jumlah << " mobil lagi.\n";
    }

    for (int i = 0; i < jumlah; i++) {
        int nomorUrut = (int)daftarParkir.size() + 1;
        cout << "\nMobil ke-" << nomorUrut << "\n";

        Kendaraan* mobilBaru = new Kendaraan();
        cout << "Masukkan plat mobil  : ";
        getline(cin, mobilBaru->platMobil);
        cout << "Masukkan merk mobil  : ";
        getline(cin, mobilBaru->merkMobil);
        cout << "Masukkan warna mobil : ";
        getline(cin, mobilBaru->warnaMobil);
        mobilBaru->waktuMasuk = time(nullptr);

        daftarParkir.push_back(mobilBaru);
    }
}

// ===================== FUNGSI TAMPIL KENDARAAN =====================
// Dibuat oleh Anggota 2

void tampilKendaraan() {
    if (daftarParkir.empty()) {
        cout << "\nBelum ada kendaraan yang terparkir.\n";
        return;
    }

    cout << "\n" << string(60, '-') << "\n";
    cout << "        DAFTAR MOBIL YANG SUDAH TERPARKIR :\n";
    cout << string(60, '-') << "\n";

    for (int i = 0; i < (int)daftarParkir.size(); i++) {
        Kendaraan* k = daftarParkir[i];
        double durasi = hitungDurasi(k->waktuMasuk);

        cout << "\nMobil ke-" << (i + 1) << "\n";
        cout << "  Plat mobil   : " << k->platMobil << "\n";
        cout << "  Merk mobil   : " << k->merkMobil << "\n";
        cout << "  Warna mobil  : " << k->warnaMobil << "\n";
        cout << "  Waktu parkir : " << formatWaktu(durasi) << "\n";
        cout << string(60, '-') << "\n";
    }
}

// ===================== STUB SEMENTARA =====================

void pembayaran()           { cout << "[TODO - Anggota 3]\n"; }
string formatWaktu(double d){ return "0 jam 0 menit 0 detik"; }
double hitungDurasi(time_t t){ return 0; }
double hitungBiaya(double d) { return 0; }
