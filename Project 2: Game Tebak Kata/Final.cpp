#ifndef TEBAKKATA_H
#define TEBAKKATA_H

#include <string>
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

extern string bankKata[];
extern int totalKata;
extern Skor leaderboard[5];
extern int jumlahSkor;

string piliKataAcak();
void inisialisasiGame(KataGame* game, string kata, int nyawa);
void tampilStatus(KataGame* game);
bool sudahDitebak(KataGame* game, char huruf);
void prosesTebakan(KataGame* game, char huruf);
bool cekMenang(KataGame* game);
void gunakanHint(KataGame* game);
void simpanSkor(string nama, int nilai);
void tampilLeaderboard();
int hitungSkor(int sisaNyawa, int tingkat);

#endif
