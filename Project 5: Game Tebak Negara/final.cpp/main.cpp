int main() {
    system("cls");
    srand(time(0));

    vector<string> daftarNegara = {
        "indonesia", "malaysia", "singapore", "thailand", "vietnam",
        "philippines", "myanmar", "cambodia", "laos", "brunei",
        "japan", "china", "korea", "india", "pakistan",
        "bangladesh", "nepal", "srilanka", "afghanistan", "iran",
        "iraq", "saudi arabia", "egypt", "turkey", "israel",
        "jordan", "kuwait", "qatar", "bahrain", "oman",
        "germany", "france", "italy", "spain", "portugal",
        "netherlands", "belgium", "switzerland", "austria", "sweden",
        "norway", "denmark", "finland", "poland", "ukraine",
        "russia", "greece", "romania", "hungary", "czech",
        "usa", "canada", "mexico", "brazil", "argentina",
        "colombia", "peru", "chile", "venezuela", "cuba",
        "australia", "newzealand", "fiji", "nigeria", "kenya",
        "ethiopia", "ghana", "tanzania", "uganda", "morocco"
    };

    int skor = 0;
    char ulang;

    do {
        int indeksAcak = rand() % daftarNegara.size();
        string negara = daftarNegara[indeksAcak];
        string soal = sembunyikanHuruf(negara);

        cout << "Tebak negara: " << soal << endl;
        cout << "Negara apakah yang dimaksud? ";

        string jawaban;
        cin >> jawaban;

        // Ubah jawaban ke huruf kecil
        for (char& c : jawaban) c = tolower(c);

        if (jawaban == negara) {
            skor++;
            cout << "Selamat! Anda benar." << endl;
        } else {
            cout << "Maaf, jawaban Anda salah. Coba lagi." << endl;
        }

        cout << "Skor Anda: " << skor << endl;
        cout << "Ingin bermain lagi? (y/n): ";
        cin >> ulang;
        cout << endl;

    } while (ulang == 'y' || ulang == 'Y');

    cout << "Game Selesai :D" << endl;

    return 0;
}
