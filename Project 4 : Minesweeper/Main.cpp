#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Minesweeper {
private:
    int size;
    int bombs;

    char board[10][10];
    bool opened[10][10];
    bool flagged[10][10];

    time_t startTime;

public:
    Minesweeper() {
        size = 0;
        bombs = 0;
    }

    bool valid(int r, int c) {
        return r >= 0 && r < size && c >= 0 && c < size;
    }

    void setup() {
        do {
            cout << "Ukuran papan (4 - 10): ";
            cin >> size;
        } while (size < 4 || size > 10);

        int maxBombs = size * size - 1;

        do {
            cout << "Jumlah bom (1 - " << maxBombs << "): ";
            cin >> bombs;
        } while (bombs < 1 || bombs > maxBombs);

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                board[i][j] = '0';
                opened[i][j] = false;
                flagged[i][j] = false;
            }
        }

        placeBombs();
        calculateNumbers();

        startTime = time(NULL);
    }

    void placeBombs() {
        int placed = 0;

        while (placed < bombs) {
            int r = rand() % size;
            int c = rand() % size;

            if (board[r][c] != '*') {
                board[r][c] = '*';
                placed++;
            }
        }
    }

    void calculateNumbers() {
        int dr[8] = {-1,-1,-1,0,0,1,1,1};
        int dc[8] = {-1,0,1,-1,1,-1,0,1};

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {

                if (board[i][j] == '*')
                    continue;

                int count = 0;

                for (int k = 0; k < 8; k++) {
                    int nr = i + dr[k];
                    int nc = j + dc[k];

                    if (valid(nr, nc) && board[nr][nc] == '*')
                        count++;
                }

                board[i][j] = char(count + '0');
            }
        }
    }

    void display(bool reveal = false) {
        cout << "\n";

        cout << "    ";
        for (int i = 1; i <= size; i++)
            cout << i << " ";
        cout << "\n";

        int flagsUsed = countFlags();

        cout << "Bom belum ditandai: "
             << bombs - flagsUsed
             << "\n";

        cout << "Waktu: "
             << (int)(time(NULL) - startTime)
             << " detik\n\n";

        for (int i = 0; i < size; i++) {

            cout << i + 1 << "   ";

            for (int j = 0; j < size; j++) {

                if (reveal) {

                    if (board[i][j] == '*')
                        cout << "* ";
                    else
                        cout << board[i][j] << " ";
                }
                else {

                    if (flagged[i][j])
                        cout << "F ";

                    else if (!opened[i][j])
                        cout << "# ";

                    else
                        cout << board[i][j] << " ";
                }
            }

            cout << "\n";
        }
    }

    void floodFill(int r, int c) {

        if (!valid(r, c))
            return;

        if (opened[r][c])
            return;

        if (flagged[r][c])
            return;

        opened[r][c] = true;

        if (board[r][c] != '0')
            return;

        for (int dr = -1; dr <= 1; dr++) {
            for (int dc = -1; dc <= 1; dc++) {

                if (dr == 0 && dc == 0)
                    continue;

                floodFill(r + dr, c + dc);
            }
        }
    }

    bool openCell(int r, int c) {

        if (!valid(r, c))
            return true;

        if (flagged[r][c])
            return true;

        if (board[r][c] == '*')
            return false;

        floodFill(r, c);

        return true;
    }

    void toggleFlag(int r, int c) {

        if (!valid(r, c))
            return;

        if (opened[r][c])
            return;

        flagged[r][c] = !flagged[r][c];
    }

    int countFlags() {
        int total = 0;

        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                if (flagged[i][j])
                    total++;

        return total;
    }

    bool checkWin() {

        int correct = 0;
        int totalFlags = 0;

        for (int i = 0; i < size; i++) {

            for (int j = 0; j < size; j++) {

                if (flagged[i][j]) {
                    totalFlags++;

                    if (board[i][j] == '*')
                        correct++;
                }
            }
        }

        return (correct == bombs && totalFlags == bombs);
    }

    void gameLoop() {

        bool running = true;

        while (running) {

            display();

            if (checkWin()) {

                cout << "\n=== SELAMAT! ANDA MENANG ===\n";
                cout << "Waktu: "
                     << (int)(time(NULL) - startTime)
                     << " detik\n";

                display(true);
                return;
            }

            cout << "\nAksi:\n";
            cout << "1. Buka Kotak\n";
            cout << "2. Tandai/Hapus Tanda\n";
            cout << "Pilihan: ";

            int choice;
            cin >> choice;

            int r, c;

            cout << "Baris : ";
            cin >> r;

            cout << "Kolom : ";
            cin >> c;

            r--;
            c--;

            if (!valid(r, c)) {
                cout << "Koordinat tidak valid!\n";
                continue;
            }

            if (choice == 1) {

                if (!openCell(r, c)) {

                    cout << "\n=== GAME OVER ===\n";
                    cout << "Anda menginjak bom!\n";

                    cout << "Waktu: "
                         << (int)(time(NULL) - startTime)
                         << " detik\n";

                    display(true);
                    return;
                }
            }
            else if (choice == 2) {
                toggleFlag(r, c);
            }
            else {
                cout << "Pilihan tidak valid!\n";
            }
        }
    }
};

int main() {

    srand(time(NULL));

    int menu;

    do {

        cout << "\n========================\n";
        cout << "      MINESWEEPER\n";
        cout << "========================\n";
        cout << "1. Mulai Permainan Baru\n";
        cout << "2. Keluar\n";
        cout << "Pilihan: ";

        cin >> menu;

        switch (menu) {

        case 1: {
            Minesweeper game;
            game.setup();
            game.gameLoop();
            break;
        }

        case 2:
            cout << "Terima kasih telah bermain.\n";
            break;

        default:
            cout << "Menu tidak valid!\n";
        }

    } while (menu != 2);

    return 0;
}
