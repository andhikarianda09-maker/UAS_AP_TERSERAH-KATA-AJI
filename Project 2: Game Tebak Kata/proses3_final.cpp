#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cctype>
using namespace std;

struct KataGame {
    string kataAsli;
    string statusTebak;
    int sisaNyawa;
    char tebakanSalah[26];
    int jumlahSalah;
};

struct Skor {
    string nama;
    int nilai;
};

string bankKata[] = {
    "apel", "buku", "meja", "kursi", "lampu",
    "pintu", "jendela", "komputer", "telepon", "kamera",
    "sepatu", "bantal", "cermin", "piring", "sendok",
    "garpu", "gelas", "botol", "ember", "gayung"
};

int totalKata = 20;
Skor leaderboard[5];
int jumlahSkor = 0;

string piliKataAcak() {
    return bankKata[rand() % totalKata];
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
    for (int i = 0; i < (int)game->statusTebak.length(); i++)
        cout << game->statusTebak[i] << " ";
    cout << "\nNyawa : " << game->sisaNyawa;
    cout << "\nSalah : ";
    for (int i = 0; i < game->jumlahSalah; i++) cout << game->tebakanSalah[i] << " ";
    cout << "\n";
}

bool sudahDitebak(KataGame* game, char huruf) {
    for (int i = 0; i < game->jumlahSalah; i++)
        if (game->tebakanSalah[i] == huruf) return true;
    for (int i = 0; i < (int)game->kataAsli.length(); i++)
        if (game->kataAsli[i] == huruf && game->statusTebak[i] == huruf) return true;
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

void gunakanHint(KataGame* game) {
    if (game->sisaNyawa <= 1) {
        cout << "Nyawa tidak cukup untuk hint!\n";
        return;
    }
    for (int i = 0; i < (int)game->kataAsli.length(); i++) {
        if (game->statusTebak[i] == '_') {
            game->statusTebak[i] = game->kataAsli[i];
            game->sisaNyawa--;
            cout << "Hint: huruf '" << game->kataAsli[i] << "' dibuka. Nyawa -1.\n";
            return;
        }
    }
}

int hitungSkor(int sisaNyawa, int tingkat) {
    return sisaNyawa * 100 * tingkat;
}

void simpanSkor(string nama, int nilai) {
    if (jumlahSkor < 5) {
        leaderboard[jumlahSkor].nama  = nama;
        leaderboard[jumlahSkor].nilai = nilai;
        jumlahSkor++;
    } else {
        int minIdx = 0;
        for (int i = 1; i < 5; i++)
            if (leaderboard[i].nilai < leaderboard[minIdx].nilai) minIdx = i;
        if (nilai > leaderboard[minIdx].nilai) {
            leaderboard[minIdx].nama  = nama;
            leaderboard[minIdx].nilai = nilai;
        }
    }
}

void tampilLeaderboard() {
    cout << "\n=== LEADERBOARD ===\n";
    if (jumlahSkor == 0) {
        cout << "Belum ada skor.\n";
        return;
    }
    for (int i = 0; i < jumlahSkor; i++)
        cout << i+1 << ". " << leaderboard[i].nama << " - " << leaderboard[i].nilai << "\n";
    cout << "===================\n";
}

int main() {
    srand(time(0));
    string namaPemain;

    cout << "==============================\n";
    cout << "       GAME TEBAK KATA\n";
    cout << "==============================\n";
    cout << "Masukkan nama : ";
    getline(cin, namaPemain);

    char ulang = 'Y';
    while (ulang == 'Y' || ulang == 'y') {
        cout << "\nPilih tingkat kesulitan:\n";
        cout << "1. Easy   (8 nyawa)\n";
        cout << "2. Medium (6 nyawa)\n";
        cout << "3. Hard   (4 nyawa)\n";
        cout << "Pilihan : ";

        int pilih;
        cin >> pilih;
        cin.ignore();

        int nyawa, tingkat;
        if      (pilih == 1) { nyawa = 8; tingkat = 1; }
        else if (pilih == 2) { nyawa = 6; tingkat = 2; }
        else                 { nyawa = 4; tingkat = 3; }

        string kata = piliKataAcak();
        KataGame game;
        inisialisasiGame(&game, kata, nyawa);

        cout << "\nPermainan dimulai! (ketik '?' untuk hint -1 nyawa)\n";

        while (game.sisaNyawa > 0 && !cekMenang(&game)) {
            tampilStatus(&game);

            string input;
            cout << "Tebak huruf : ";
            getline(cin, input);

            if (input.empty()) continue;

            if (input[0] == '?') {
                gunakanHint(&game);
                continue;
            }

            char huruf = tolower(input[0]);

            if (sudahDitebak(&game, huruf)) {
                cout << "Huruf '" << huruf << "' sudah pernah ditebak! Coba huruf lain.\n";
                continue;
            }

            prosesTebakan(&game, huruf);
        }

        if (cekMenang(&game)) {
            int skor = hitungSkor(game.sisaNyawa, tingkat);
            cout << "\nSELAMAT! Kamu berhasil menebak kata: " << game.kataAsli << "\n";
            cout << "Skor kamu : " << skor << "\n";
            simpanSkor(namaPemain, skor);
        } else {
            tampilStatus(&game);
            cout << "\nGAME OVER! Kata yang benar adalah: " << game.kataAsli << "\n";
        }

        tampilLeaderboard();

        cout << "\nApakah Anda ingin bermain lagi? (Y/N) : ";
        string pil;
        getline(cin, pil);
        ulang = pil.empty() ? 'N' : toupper(pil[0]);
    }

    cout << "\nTerima kasih sudah bermain!\n";
    return 0;
}
