#include "ai.h"
#include "config.h"
#include "game_logic.h"
#include "raylib.h" // 需要用到 WaitTime
#include <stdlib.h>

void playAiTurn() {
    WaitTime(0.5); 

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    // 1. 保命優先
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            if (revealed[r][c] == 1 && getFaction(board[r][c]) == aiFaction) {
                for (int i = 0; i < 4; i++) {
                    int nr = r + dr[i];
                    int nc = c + dc[i];
                    if (nr >= 0 && nr < ROWS && nc >= 0 && nc < COLS && revealed[nr][nc] == 1) {
                        if (getFaction(board[nr][nc]) != aiFaction) {
                            if (canEat(board[nr][nc], board[r][c])) {
                                for (int esc = 0; esc < 4; esc++) {
                                    int er = r + dr[esc];
                                    int ec = c + dc[esc];
                                    if (er >= 0 && er < ROWS && ec >= 0 && ec < COLS && revealed[er][ec] == -1) {
                                        board[er][ec] = board[r][c];
                                        revealed[er][ec] = 1;
                                        revealed[r][c] = -1;
                                        compSteps++;
                                        currentTurn = 0;
                                        return;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    // 2. 貪吃
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            if (revealed[r][c] == 1 && getFaction(board[r][c]) == aiFaction) {
                for (int i = 0; i < 4; i++) {
                    int nr = r + dr[i];
                    int nc = c + dc[i];
                    if (nr >= 0 && nr < ROWS && nc >= 0 && nc < COLS && revealed[nr][nc] == 1) {
                        if (canEat(board[r][c], board[nr][nc])) {
                            board[nr][nc] = board[r][c];
                            revealed[r][c] = -1; 
                            compSteps++;
                            currentTurn = 0;
                            return;
                        }
                    }
                }
            }
        }
    }

    // 3. 都沒事做：隨便翻一張蓋著的牌
    while (1) {
        int compR = rand() % ROWS;
        int compC = rand() % COLS;
        if (revealed[compR][compC] == 0) { 
            revealed[compR][compC] = 1; 
            if (playerFaction == -1) {
                aiFaction = getFaction(board[compR][compC]);
                playerFaction = 1 - aiFaction;
            }
            compSteps++;
            currentTurn = 0;
            return;
        }
    }
}