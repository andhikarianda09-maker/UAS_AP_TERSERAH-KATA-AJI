string sembunyikanHuruf(string negara) {
    string hasil = negara;
    int panjang = negara.length();
    int jumlahSembunyi = panjang / 2;

    vector<int> indeks;
    for (int i = 0; i < panjang; i++) {
        if (negara[i] != ' ') {
            indeks.push_back(i);
        }
    }

    // Acak indeks
    for (int i = indeks.size() - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap(indeks[i], indeks[j]);
    }

    for (int i = 0; i < jumlahSembunyi && i < (int)indeks.size(); i++) {
        hasil[indeks[i]] = '_';
    }

    return hasil;
}
