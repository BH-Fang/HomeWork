#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int r, c, lines;
} result_t;

int resultCMP(const void *a, const void *b)
{
    result_t *ra = (result_t*)a, *rb = (result_t*)b;
    int c1 = rb->lines - ra->lines;
    if(c1) return c1;
    int c2 = ra->r - rb->r;
    if(c2) return c2;
    return ra->c - rb->c;
}

int check(int i, int j)
{
    return i >= 0 && i < 10 && j >= 0 && j < 10;
}

int main()
{
    int board[10][10], resultCount = 0;
    result_t results[100];

    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            scanf("%d", &board[i][j]);
        }
    }

    int dr[] = {1, 0, 1, 1};
    int dc[] = {0, 1, 1, -1};
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {   
            if(board[i][j]) continue;
            int lineCount = 0;
            for(int k = 0; k < 4; k++)
            {
                int chessCount = 0, r = i + dr[k], c = j + dc[k];
                while(check(r, c) && board[r][c] == 1)
                {
                    chessCount++;
                    r += dr[k]; c += dc[k];
                }
                r = i - dr[k]; c = j - dc[k];
                while(check(r, c) && board[r][c] == 1)
                {
                    chessCount++;
                    r -= dr[k]; c -= dc[k];
                }
                if(chessCount == 4) lineCount++;
            }
            if(lineCount) 
            {
                results[resultCount].r = i; 
                results[resultCount].c = j;
                results[resultCount].lines = lineCount;
                resultCount++;
            }
        }
    }
    qsort(results, resultCount, sizeof(result_t), resultCMP);

    for(int i = 0; i < resultCount; i++)
    {
        printf("%d%d %d\n", results[i].r, results[i].c, results[i].lines);
    }

    return 0;
}