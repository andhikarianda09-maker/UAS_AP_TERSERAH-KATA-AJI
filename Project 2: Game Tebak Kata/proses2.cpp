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
    game->kataAsli    = kata;
    game->sisaNyawa   = nyawa;
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

bool sudahDitebak(KataGame* game, char huruf) {
    for (int i = 0; i < (int)game->kataAsli.length(); i++)
        if (game->statusTebak[i] == huruf) return true;
    for (int i = 0; i < game->jumlahSalah; i++)
        if (game->tebakanSalah[i] == huruf) return true;
    return false;
}

void prosesTebakan(KataGame* game, char huruf) {
    bool ada = false;
    for (int i = 0; i < (int)game->kataAsli.length(); i++) {
        if (game->kataAsli[i] == huruf) {
            game->statusTebak[i] = huruf;
            ada = true;
        }
    }
    if (!ada) {
        game->tebakanSalah[game->jumlahSalah] = huruf;
        game->jumlahSalah++;
        game->sisaNyawa--;
        cout << "Huruf tidak ada! Nyawa berkurang.\n";
    } else {
        cout << "Benar! Huruf '" << huruf << "' ditemukan.\n";
    }
}

bool cekMenang(KataGame* game) {
    return game->statusTebak == game->kataAsli;
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
    cin.ignore();

    int nyawa;
    if      (pilih == 1) nyawa = 8;
    else if (pilih == 2) nyawa = 6;
    else                 nyawa = 4;

    string kata = piliKataAcak();

    KataGame game;
    inisialisasiGame(&game, kata, nyawa);

    cout << "\nPermainan dimulai!\n";

    while (game.sisaNyawa > 0 && !cekMenang(&game)) {
        tampilStatus(&game);

        char huruf;
        cout << "Tebak huruf : ";
        cin >> huruf;
        cin.ignore();
        huruf = tolower(huruf);

        if (sudahDitebak(&game, huruf)) {
            cout << "Huruf '" << huruf << "' sudah pernah ditebak! Coba huruf lain.\n";
            continue;
        }

        prosesTebakan(&game, huruf);
    }

    if (cekMenang(&game)) {
        cout << "\nSELAMAT! Kamu berhasil menebak kata: " << game.kataAsli << "\n";
    } else {
        cout << "\nGAME OVER! Kata yang benar adalah: " << game.kataAsli << "\n";
    }

    return 0;
}
