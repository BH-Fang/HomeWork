#ifndef CONFIG_H
#define CONFIG_H

#include <stdbool.h>

#define ROWS 4
#define COLS 8
#define CELL_SIZE 70
#define MARGIN 50

// --- 全域狀態宣告 (extern) ---
extern int board[ROWS][COLS];
extern int revealed[ROWS][COLS]; // 0:蓋著, 1:翻開, -1:空位

extern int gameState;     // 0:選擇先後手畫面, 1:遊戲進行中, 2:遊戲結束
extern int currentTurn;   // 0:玩家, 1:電腦
extern int playerFaction; // 0:黑方(0~6), 1:紅方(7~13), -1:未決定
extern int aiFaction;

extern int playerSteps;   // 玩家步數
extern int compSteps;     // 電腦步數

extern int selectedR;     // 玩家選取棋子用的變數
extern int selectedC;

#endif