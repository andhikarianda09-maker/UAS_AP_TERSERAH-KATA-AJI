#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

struct KataGame {
    string kataAsli;
    string statusTebak;
    int sisaNyawa;
    char tebakanSalah[26];
    int jumlahSalah;
};

string bankKata[] = {
    "apel", "buku", "meja", "kursi", "lampu",
    "pintu", "jendela", "komputer", "telepon", "kamera",
    "sepatu", "bantal", "cermin", "piring", "sendok",
    "garpu", "gelas", "botol", "ember", "gayung"
};

int totalKata = 20;

string piliKataAcak() {
    srand(time(0));
    int index = rand() % totalKata;
    return bankKata[index];
}

void inisialisasiGame(KataGame* game, string kata, int nyawa) {
    game->kataAsli   = kata;
    game->sisaNyawa  = nyawa;
    game->jumlahSalah = 0;
    game->statusTebak = string(kata.length(), '_');
    for (int i = 0; i < 26; i++) game->tebakanSalah[i] = '\0';
}

void tampilStatus(KataGame* game) {
    cout << "\nKata  : ";
    for (int i = 0; i < (int)game->statusTebak.length(); i++) {
        cout << game->statusTebak[i] << " ";
    }
    cout << "\nNyawa : " << game->sisaNyawa;
    cout << "\nSalah : ";
    for (int i = 0; i < game->jumlahSalah; i++) cout << game->tebakanSalah[i] << " ";
    cout << "\n";
}

int main() {
    cout << "==============================\n";
    cout << "      GAME TEBAK KATA\n";
    cout << "==============================\n";

    cout << "Pilih tingkat kesulitan:\n";
    cout << "1. Easy   (8 nyawa)\n";
    cout << "2. Medium (6 nyawa)\n";
    cout << "3. Hard   (4 nyawa)\n";
    cout << "Pilihan : ";

    int pilih;
    cin >> pilih;

    int nyawa;
    if      (pilih == 1) nyawa = 8;
    else if (pilih == 2) nyawa = 6;
    else                 nyawa = 4;

    string kata = piliKataAcak();

    KataGame game;
    inisialisasiGame(&game, kata, nyawa);

    cout << "\nPermainan dimulai!\n";
    tampilStatus(&game);

    return 0;
}
