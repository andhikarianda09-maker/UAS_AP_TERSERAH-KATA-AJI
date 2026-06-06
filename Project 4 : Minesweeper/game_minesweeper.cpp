#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Minesweeper {
private:
    static const int MAX_SIZE = 10;

    int  board[MAX_SIZE][MAX_SIZE];
    bool revealed[MAX_SIZE][MAX_SIZE];
    bool flagged[MAX_SIZE][MAX_SIZE];

    int    N;
    int    totalBombs;
    int    flagCount;
    int    openCount;
    bool   gameOver;
    bool   won;
    time_t startTime;
    char   playerName[64];

    int countNeighborBombs(int r, int c) {
        int count = 0;
        for (int dr = -1; dr <= 1; dr++) {
            for (int dc = -1; dc <= 1; dc++) {
                if (dr == 0 && dc == 0) continue;
                int nr = r + dr, nc = c + dc;
                if (nr >= 0 && nr < N && nc >= 0 && nc < N)
                    if (board[nr][nc] == -1) count++;
            }
        }
        return count;
    }

    void plantBombs() {
        for (int r = 0; r < N; r++)
            for (int c = 0; c < N; c++)
                board[r][c] = 0;

        int placed = 0;
        while (placed < totalBombs) {
            int r = rand() % N;
            int c = rand() % N;
            if (board[r][c] != -1) {
                board[r][c] = -1;
                placed++;
            }
        }

        for (int r = 0; r < N; r++)
            for (int c = 0; c < N; c++)
                if (board[r][c] != -1)
                    board[r][c] = countNeighborBombs(r, c);
    }

    void floodFill(int r, int c) {
        if (r < 0 || r >= N || c < 0 || c >= N) return;
        if (revealed[r][c] || flagged[r][c])     return;
        if (board[r][c] == -1)                   return;

        revealed[r][c] = true;
        openCount++;

        if (board[r][c] == 0) {
            for (int dr = -1; dr <= 1; dr++)
                for (int dc = -1; dc <= 1; dc++)
                    if (!(dr == 0 && dc == 0))
                        floodFill(r + dr, c + dc);
        }
    }

    void revealAllBombs() {
        for (int r = 0; r < N; r++)
            for (int c = 0; c < N; c++)
                if (board[r][c] == -1)
                    revealed[r][c] = true;
    }

    bool checkWin() {
        for (int r = 0; r < N; r++) {
            for (int c = 0; c < N; c++) {
                if (board[r][c] == -1 && !flagged[r][c]) return false;
                if (board[r][c] != -1 &&  flagged[r][c]) return false;
            }
        }
        return true;
    }

    int elapsedSeconds() {
        return (int)difftime(time(nullptr), startTime);
    }

    void clearScreen() {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }

    void printSeparator(char ch, int len) {
        for (int i = 0; i < len; i++) cout << ch;
        cout << "\n";
    }

    void printBoard(bool showAll = false) {
        int remaining = totalBombs - flagCount;
        int elapsed   = elapsedSeconds();

        cout << "\n";
        printSeparator('=', 4 + N * 4);
        cout << "  MINESWEEPER++   |  Pemain: " << playerName << "\n";
        cout << "  Bom tersisa: " << remaining << "   |  Waktu: " << elapsed << "s\n";
        printSeparator('=', 4 + N * 4);

        cout << "     ";
        for (int c = 0; c < N; c++) {
            cout << " ";
            if (c + 1 < 10) cout << " ";
            cout << (c + 1) << " ";
        }
        cout << "\n";

        cout << "   +";
        for (int c = 0; c < N; c++) cout << "---+";
        cout << "\n";

        for (int r = 0; r < N; r++) {
            if (r + 1 < 10) cout << " ";
            cout << (r + 1) << " |";

            for (int c = 0; c < N; c++) {
                if (showAll || revealed[r][c]) {
                    if (board[r][c] == -1) {
                        if (flagged[r][c]) cout << " F |";
                        else               cout << " * |";
                    } else if (board[r][c] == 0) {
                        cout << "   |";
                    } else {
                        cout << " " << board[r][c] << " |";
                    }
                } else if (flagged[r][c]) {
                    cout << " F |";
                } else {
                    cout << " . |";
                }
            }
            cout << "\n";

            cout << "   +";
            for (int c = 0; c < N; c++) cout << "---+";
            cout << "\n";
        }

        cout << "\n  Legenda: [ . ] Belum dibuka  [ F ] Tandai bom  [ * ] Bom  [   ] Aman\n";
        cout << "  Aksi: O=Buka  T=Tandai/Hapus Tanda  K=Keluar\n";
        printSeparator('-', 4 + N * 4);
    }

    int readInt(const char* prompt, int lo, int hi) {
        int val;
        while (true) {
            cout << prompt;
            if (cin >> val && val >= lo && val <= hi) return val;
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "  [!] Input tidak valid. Masukkan angka " << lo << " - " << hi << ".\n";
        }
    }

    char readAction() {
        char act;
        while (true) {
            cout << "  Aksi (O/T/K): ";
            cin >> act;
            act = (char)toupper((unsigned char)act);
            if (act == 'O' || act == 'T' || act == 'K') return act;
            cout << "  [!] Aksi tidak valid.\n";
        }
    }

public:
    Minesweeper() {
        srand((unsigned int)time(nullptr));
    }

    void setup() {
        clearScreen();
        printSeparator('*', 40);
        cout << "        MINESWEEPER++  \n";
        printSeparator('*', 40);

        cout << "\n  Masukkan nama pemain: ";
        cin.ignore();
        cin.getline(playerName, 64);
        if (playerName[0] == '\0') {
            playerName[0] = 'P'; playerName[1] = 'e';
            playerName[2] = 'm'; playerName[3] = 'a';
            playerName[4] = 'i'; playerName[5] = 'n';
            playerName[6] = '\0';
        }

        cout << "\n  === Pengaturan Papan ===\n";
        N = readInt("  Ukuran papan N (4-10): ", 4, 10);

        int maxBombs = N * N - 1;
        int minBombs = 1;
        cout << "  Jumlah bom (" << minBombs << "-" << maxBombs << "): ";
        totalBombs = readInt("", minBombs, maxBombs);
    }

    void resetGame() {
        flagCount = 0;
        openCount = 0;
        gameOver  = false;
        won       = false;

        for (int r = 0; r < N; r++)
            for (int c = 0; c < N; c++) {
                revealed[r][c] = false;
                flagged[r][c]  = false;
            }

        plantBombs();
        startTime = time(nullptr);
    }

    void openCell(int r, int c) {
        if (revealed[r][c]) {
            cout << "  [!] Kotak sudah dibuka.\n";
            return;
        }
        if (flagged[r][c]) {
            cout << "  [!] Kotak bertanda F. Hapus tanda dulu.\n";
            return;
        }

        if (board[r][c] == -1) {
            revealed[r][c] = true;
            revealAllBombs();
            gameOver = true;
            won      = false;
        } else {
            floodFill(r, c);
        }
    }

    void toggleFlag(int r, int c) {
        if (revealed[r][c]) {
            cout << "  [!] Kotak sudah terbuka, tidak bisa ditandai.\n";
            return;
        }
        if (!flagged[r][c]) {
            flagged[r][c] = true;
            flagCount++;
        } else {
            flagged[r][c] = false;
            flagCount--;
        }

        if (checkWin()) {
            gameOver = true;
            won      = true;
        }
    }

    void play() {
        resetGame();

        while (!gameOver) {
            clearScreen();
            printBoard();

            char action = readAction();
            if (action == 'K') {
                gameOver = true;
                won      = false;
                cout << "\n  Kamu menyerah.\n";
                break;
            }

            cout << "  Baris (1-" << N << "): ";
            int row = readInt("", 1, N) - 1;
            cout << "  Kolom (1-" << N << "): ";
            int col = readInt("", 1, N) - 1;

            if (action == 'O') openCell(row, col);
            else               toggleFlag(row, col);
        }

        clearScreen();
        printBoard(true);

        int elapsed = elapsedSeconds();
        printSeparator('=', 40);
        if (won) {
            cout << "\n  *** SELAMAT, " << playerName << "! Kamu menang! ***\n";
        } else {
            cout << "\n  *** BOOM! Game Over, " << playerName << ". ***\n";
        }
        cout << "  Waktu bermain: " << elapsed << " detik\n";
        cout << "  Ukuran papan : " << N << "x" << N << "\n";
        cout << "  Jumlah bom   : " << totalBombs << "\n";
        printSeparator('=', 40);
    }
};

int main() {
    Minesweeper game;

    while (true) {
        cout << "\n";
        cout << "  ==============================\n";
        cout << "       MINESWEEPER++\n";
        cout << "  ==============================\n";
        cout << "  1. Mulai Permainan Baru\n";
        cout << "  2. Keluar\n";
        cout << "  ==============================\n";
        cout << "  Pilihan (1/2): ";

        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        if (choice == 1) {
            game.setup();
            game.play();
            cout << "\n  Tekan Enter untuk kembali ke menu...";
            cin.ignore(1000, '\n');
            cin.get();
        } else if (choice == 2) {
            cout << "\n  Sampai jumpa!\n\n";
            break;
        } else {
            cout << "  [!] Pilihan tidak valid.\n";
        }
    }

    return 0;
}