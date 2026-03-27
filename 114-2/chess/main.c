#include "raylib.h"

int main(void) {
    // ---------------------------------------------------------
    // 1. 定義設計參數
    // ---------------------------------------------------------
    
    // 格子大小（兩個交叉點之間的距離）
    const int gridSize = 70; 
    
    // 棋盤網格的起始座標（左上角第一個交叉點，考慮到邊界留白）
    const int startX = 60; 
    const int startY = 60; 
    
    // 下半部棋盤的線段數量
    const int numFiles = 9; // 9 條豎線
    const int numRanks = 5; // 5 條橫線
    
    // 計算網格的總寬度和總高度
    const int boardWidth = (numFiles - 1) * gridSize;
    const int boardHeight = (numRanks - 1) * gridSize;
    
    // 根據網格大小加上平均的邊界留白，計算最合適的視窗大小
    // 左右留白各 60, 上下留白各 60
    const int screenWidth = boardWidth + (startX * 2);
    const int screenHeight = boardHeight + (startY * 2);

    // 線條寬度（設為 3.0f，看起來清晰且不粗糙）
    const float lineThickness = 3.0f;

    // 定義咖啡色 (木質棋盤感)
    // R:160, G:110, B:60 是一個不錯的木頭咖啡色
    Color coffeeColor = { 160, 110, 60, 255 }; 

    // 初始化視窗
    InitWindow(screenWidth, screenHeight, "中國象棋棋盤 (下半部) - Raylib");

    SetTargetFPS(60);

    // ---------------------------------------------------------
    // 2. 遊戲主迴圈
    // ---------------------------------------------------------
    while (!WindowShouldClose()) {
        BeginDrawing();
            
            // 塗滿咖啡色底色
            ClearBackground(coffeeColor); 
            
            // --- A. 繪製所有橫線 (Horizontal Lines) ---
            for (int i = 0; i < numRanks; i++) {
                // 計算每一條橫線的 Y 座標
                int currentY = startY + (i * gridSize);
                
                // 定義線段的起點和終點 (Vector2 浮點數型態，搭配 DrawLineEx)
                Vector2 startPos = { (float)startX, (float)currentY };
                Vector2 endPos = { (float)(startX + boardWidth), (float)currentY };
                
                // 畫線
                DrawLineEx(startPos, endPos, lineThickness, BLACK);
            }
            
            // --- B. 繪製所有豎線 (Vertical Lines) ---
            for (int i = 0; i < numFiles; i++) {
                // 計算每一條豎線的 X 座標
                int currentX = startX + (i * gridSize);
                
                // 定義線段的起點和終點
                Vector2 startPos = { (float)currentX, (float)startY };
                Vector2 endPos = { (float)currentX, (float)(startY + boardHeight) };
                
                // 畫線
                DrawLineEx(startPos, endPos, lineThickness, BLACK);
            }
            
            // --- C. 繪製「九宮格」斜線 (Palace Diagonals) ---
            // 九宮格位於下半部的中間底部，即第 4 豎線到第 6 豎線，第 1 橫線到第 3 橫線。
            // 轉化為座標：(startX + 3*gridSize, startY + 2*gridSize) 到 (startX + 5*gridSize, startY + 4*gridSize)
            
            // 九宮格的四個頂點座標
            Vector2 palaceTopLeft = { (float)(startX + 3 * gridSize), (float)(startY + 2 * gridSize) };
            Vector2 palaceTopRight = { (float)(startX + 5 * gridSize), (float)(startY + 2 * gridSize) };
            Vector2 palaceBottomLeft = { (float)(startX + 3 * gridSize), (float)(startY + 4 * gridSize) };
            Vector2 palaceBottomRight = { (float)(startX + 5 * gridSize), (float)(startY + 4 * gridSize) };
            
            // 畫九宮格的兩條斜線
            DrawLineEx(palaceTopLeft, palaceBottomRight, lineThickness, BLACK);
            DrawLineEx(palaceTopRight, palaceBottomLeft, lineThickness, BLACK);
            
            // 可以在上方標示「楚河 漢界」的位置 (選擇性)
            DrawText("chu he ", startX + gridSize, startY - 40, 30, BLACK);
            DrawText("han jie", startX + 6 * gridSize, startY - 40, 30, BLACK);

        EndDrawing();
    }

    // ---------------------------------------------------------
    // 3. 收尾
    // ---------------------------------------------------------
    CloseWindow(); 

    return 0;
}