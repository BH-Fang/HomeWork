#include "game_logic.h"
#include <stdlib.h>
#include <time.h>

// --- 定義全域變數實體 ---
int board[ROWS][COLS];
int revealed[ROWS][COLS];
int gameState = 0;
int currentTurn = 0;
int playerFaction = -1;
int aiFaction = -1;
int playerSteps = 0;
int compSteps = 0;
int selectedR = -1;
int selectedC = -1;

void initBoard() {
    int initialPieces[32] = {
        0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 6, 6, 6,
        7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13, 13, 13, 13
    };
    int i, j, temp, r, c;
    int k = 0;
    srand(time(NULL));

    for (i = 31; i > 0; i--) {
        j = rand() % (i + 1);
        temp = initialPieces[i];
        initialPieces[i] = initialPieces[j];
        initialPieces[j] = temp;
    }

    for (r = 0; r < ROWS; r++) {
        for (c = 0; c < COLS; c++) {
            board[r][c] = initialPieces[k++];
            revealed[r][c] = 0; 
        }
    }
}

int getFaction(int piece) {
    if (piece <= 6) return 0;
    return 1;
}

bool canEat(int attacker, int defender) {
    if (getFaction(attacker) == getFaction(defender)) return false;

    int aRank = attacker % 7; 
    int dRank = defender % 7;

    if (aRank == 5) return false; 
    if (aRank == 0 && dRank == 6) return false; 
    if (aRank == 6 && dRank == 0) return true;  
    
    return aRank <= dRank; 
}