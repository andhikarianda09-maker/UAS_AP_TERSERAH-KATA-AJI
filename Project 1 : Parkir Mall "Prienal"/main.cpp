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
void pembayaran();
string formatWaktu(double detik);
double hitungDurasi(time_t masuk);
double hitungBiaya(double detikParkir);

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
