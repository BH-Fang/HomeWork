#include "raylib.h"
#include "config.h"
#include "game_logic.h"
#include "renderer.h"
#include "ai.h"
#include <stdlib.h> // 需要 abs()

int main() {
    int screenWidth = MARGIN * 2 + COLS * CELL_SIZE;
    int screenHeight = MARGIN * 2 + ROWS * CELL_SIZE + 80;
    
    InitWindow(screenWidth, screenHeight, "Dark Chess");
    SetTargetFPS(60);

    // 從 renderer 模組載入圖片
    loadTextures();
    // 從 game_logic 模組初始化棋盤
    initBoard();

    while (!WindowShouldClose()) {
        // --- 狀態0：選先後手 ---
        if (gameState == 0) {
            if (IsKeyPressed(KEY_P)) { currentTurn = 0; gameState = 1; }
            if (IsKeyPressed(KEY_C)) { currentTurn = 1; gameState = 1; }
        }

        // --- 檢查遊戲結束 (各走10步) ---
        if (gameState == 1 && playerSteps >= 10 && compSteps >= 10) {
            gameState = 2;
        }

        // --- 狀態1：遊戲進行中 (玩家回合) ---
        if (gameState == 1 && currentTurn == 0 && playerSteps < 10) {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                int x = GetMouseX();
                int y = GetMouseY();

                if (x > MARGIN && x < MARGIN + COLS * CELL_SIZE && y > MARGIN && y < MARGIN + ROWS * CELL_SIZE) {
                    int c = (x - MARGIN) / CELL_SIZE;
                    int r = (y - MARGIN) / CELL_SIZE;

                    if (revealed[r][c] == 0 && selectedR == -1) {
                        revealed[r][c] = 1;
                        if (playerFaction == -1) {
                            playerFaction = getFaction(board[r][c]);
                            aiFaction = 1 - playerFaction;
                        }
                        playerSteps++;
                        currentTurn = 1;
                    }
                    else if (revealed[r][c] == 1 && getFaction(board[r][c]) == playerFaction) {
                        selectedR = r;
                        selectedC = c;
                    }
                    else if (selectedR != -1) {
                        if (abs(r - selectedR) + abs(c - selectedC) == 1) {
                            if (revealed[r][c] == -1) {
                                board[r][c] = board[selectedR][selectedC];
                                revealed[r][c] = 1;
                                revealed[selectedR][selectedC] = -1;
                                selectedR = -1;
                                playerSteps++;
                                currentTurn = 1;
                            }
                            else if (revealed[r][c] == 1 && getFaction(board[r][c]) != playerFaction) {
                                if (canEat(board[selectedR][selectedC], board[r][c])) {
                                    board[r][c] = board[selectedR][selectedC];
                                    revealed[selectedR][selectedC] = -1;
                                    selectedR = -1;
                                    playerSteps++;
                                    currentTurn = 1;
                                }
                            }
                        } else {
                            selectedR = -1;
                        }
                    }
                }
            }
        }

        // --- 狀態1：遊戲進行中 (電腦回合) ---
        if (gameState == 1 && currentTurn == 1 && compSteps < 10) {
            playAiTurn();
            if (playerSteps >= 10 && compSteps >= 10) gameState = 2;
        }

        // --- 繪圖區 ---
        BeginDrawing();
        drawBoard();
        EndDrawing();
    }

    // 釋放記憶體並關閉
    unloadTextures();
    CloseWindow();
    
    return 0;
}