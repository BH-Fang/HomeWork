#include "renderer.h"
#include "config.h"
#include "raylib.h"
#include <stdio.h>

Texture2D pieceTextures[14];

void loadTextures() {
    for (int i = 0; i < 14; i++) {
        char filename[20];
        sprintf(filename, "images\\%d.png", i); 
        pieceTextures[i] = LoadTexture(filename);
    }
}

void unloadTextures() {
    for (int i = 0; i < 14; i++) {
        UnloadTexture(pieceTextures[i]);
    }
}

void drawBoard() {
    ClearBackground(RAYWHITE);

    if (gameState == 0) {
        DrawText("Who goes first?", 150, 100, 30, BLACK);
        DrawText("Press 'P' for Player", 150, 160, 20, DARKBLUE);
        DrawText("Press 'C' for Computer", 150, 200, 20, DARKBLUE);
        return;
    }

    for (int r = 0; r <= ROWS; r++) DrawLine(MARGIN, MARGIN + r * CELL_SIZE, MARGIN + COLS * CELL_SIZE, MARGIN + r * CELL_SIZE, BLACK);
    for (int c = 0; c <= COLS; c++) DrawLine(MARGIN + c * CELL_SIZE, MARGIN, MARGIN + c * CELL_SIZE, MARGIN + ROWS * CELL_SIZE, BLACK);

    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            int left = MARGIN + c * CELL_SIZE + 5;
            int top = MARGIN + r * CELL_SIZE + 5;
            int right = MARGIN + (c + 1) * CELL_SIZE - 5;
            int bottom = MARGIN + (r + 1) * CELL_SIZE - 5;

            if (revealed[r][c] == 0) { 
                DrawRectangle(left, top, right - left, bottom - top, GREEN);
            } else if (revealed[r][c] == 1) { 
                Texture2D tex = pieceTextures[board[r][c]];
                Rectangle sourceRec = { 0.0f, 0.0f, (float)tex.width, (float)tex.height };
                Rectangle destRec = { (float)left, (float)top, (float)(right - left), (float)(bottom - top) };
                Vector2 origin = { 0.0f, 0.0f };
                DrawTexturePro(tex, sourceRec, destRec, origin, 0.0f, WHITE);
            }
            
            if (r == selectedR && c == selectedC) {
                DrawRectangleLines(left-2, top-2, (right-left)+4, (bottom-top)+4, RED);
            }
        }
    }

    DrawText(TextFormat("Player Steps: %d / 10", playerSteps), MARGIN, 10, 20, DARKBLUE);
    DrawText(TextFormat("PC Steps: %d / 10", compSteps), MARGIN + 250, 10, 20, MAROON);
    
    if (gameState == 2) {
        DrawText("Game Over! (10 Steps)", MARGIN, MARGIN + ROWS * CELL_SIZE + 20, 30, RED);
    } else {
        if (currentTurn == 0) DrawText("Player's Turn...", MARGIN, MARGIN + ROWS * CELL_SIZE + 20, 20, DARKGREEN);
        else DrawText("PC thinking...", MARGIN, MARGIN + ROWS * CELL_SIZE + 20, 20, ORANGE);
    }
}