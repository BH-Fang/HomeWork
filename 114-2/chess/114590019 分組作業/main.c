#include "raylib.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define ROWS 4
#define COLS 8
#define CELL_SIZE 70
#define MARGIN 50

int board[ROWS][COLS];
int revealed[ROWS][COLS];

Texture2D pieceTextures[14];

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

void drawBoard() {
    int r, c;
    int left, top, right, bottom;

    ClearBackground(LIGHTGRAY);

    for (r = 0; r <= ROWS; r++) {
        DrawLine(MARGIN, MARGIN + r * CELL_SIZE, MARGIN + COLS * CELL_SIZE, MARGIN + r * CELL_SIZE, BLACK);
    }
    for (c = 0; c <= COLS; c++) {
        DrawLine(MARGIN + c * CELL_SIZE, MARGIN, MARGIN + c * CELL_SIZE, MARGIN + ROWS * CELL_SIZE, BLACK);
    }

    for (r = 0; r < ROWS; r++) {
        for (c = 0; c < COLS; c++) {
            left = MARGIN + c * CELL_SIZE + 5;
            top = MARGIN + r * CELL_SIZE + 5;
            right = MARGIN + (c + 1) * CELL_SIZE - 5;
            bottom = MARGIN + (r + 1) * CELL_SIZE - 5;

            if (revealed[r][c] == 0) { 
                DrawRectangle(left, top, right - left, bottom - top, GREEN);
            } else { 
                Texture2D tex = pieceTextures[board[r][c]];
                Rectangle sourceRec = { 0.0f, 0.0f, (float)tex.width, (float)tex.height }; 
                Rectangle destRec = { (float)left, (float)top, (float)(right - left), (float)(bottom - top) }; 
                Vector2 origin = { 0.0f, 0.0f };
                DrawTexturePro(tex, sourceRec, destRec, origin, 0.0f, WHITE);
            }
        }
    }
}

int main() {
    int totalPieces = 32; 
    int revealedCount = 0; 
    int x, y, c, r, compR, compC;

    int screenWidth = MARGIN * 2 + COLS * CELL_SIZE;
    int screenHeight = MARGIN * 2 + ROWS * CELL_SIZE;
    InitWindow(screenWidth, screenHeight, "chess");

    SetTargetFPS(60);

    for (int i = 0; i < 14; i++) {
        char filename[20];
        sprintf(filename, "images\\%d.png", i); 
        pieceTextures[i] = LoadTexture(filename);
    }

    initBoard();

    while (!WindowShouldClose()) {


        if (revealedCount < totalPieces) {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                x = GetMouseX();
                y = GetMouseY();
                if (x > MARGIN && x < MARGIN + COLS * CELL_SIZE &&
                    y > MARGIN && y < MARGIN + ROWS * CELL_SIZE) {

                    c = (x - MARGIN) / CELL_SIZE; 
                    r = (y - MARGIN) / CELL_SIZE; 

                    if (revealed[r][c] == 0) {
                        revealed[r][c] = 1;
                        revealedCount++;

                        if (revealedCount < totalPieces) {
                            while (1) {
                                compR = rand() % ROWS;
                                compC = rand() % COLS;

                                if (revealed[compR][compC] == 0) {
                                    revealed[compR][compC] = 1;
                                    revealedCount++;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }

        BeginDrawing();

        drawBoard();

        if (revealedCount >= totalPieces) {
            DrawText("Game Over!", MARGIN, 10, 30, RED);
        }

        EndDrawing();
    }

    for (int i = 0; i < 14; i++) {
        UnloadTexture(pieceTextures[i]);
    }

    CloseWindow();

    return 0;
}
