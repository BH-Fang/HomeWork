#include <stdio.h>

int getNextXY(int x, int y,int* nextX, int* nextY, int step, int grid[10][10], int visited[10][10], int r, int c)
{
    int nX = -1, nY = -1;
    if(step % 2 == 1)
    {
        int min = __INT32_MAX__;
        if(x - 1 >= 0 && !visited[x - 1][y] && grid[x - 1][y] < min)
        {
            min = grid[x - 1][y];
            nX = x - 1;
            nY = y;
        }
        if(y + 1 < c && !visited[x][y + 1] &&  grid[x][y + 1] < min)
        {
            min = grid[x][y + 1];
            nX = x;
            nY = y + 1;
        }
        if(x + 1 < r && !visited[x + 1][y] &&  grid[x + 1][y] < min)
        {
            min = grid[x + 1][y];
            nX = x + 1;
            nY = y;
        }
        if(y - 1 >= 0 && !visited[x][y - 1] &&  grid[x][y - 1] < min)
        {
            min = grid[x][y - 1];
            nX = x;
            nY = y - 1;
        }
    }
    else
    {
        int max = -1;
        if(x - 1 >= 0 && !visited[x - 1][y] &&  grid[x - 1][y] > max)
        {
            max = grid[x - 1][y];
            nX = x - 1;
            nY = y;
        }
        if(y + 1 < c && !visited[x][y + 1] &&  grid[x][y + 1] > max)
        {
            max = grid[x][y + 1];
            nX = x;
            nY = y + 1;
        }
        if(x + 1 < r && !visited[x + 1][y] &&  grid[x + 1][y] > max)
        {
            max = grid[x + 1][y];
            nX = x + 1;
            nY = y;
        }
        if(y - 1 >= 0 && !visited[x][y - 1] &&  grid[x][y - 1] > max)
        {
            max = grid[x][y - 1];
            nX = x;
            nY = y - 1;
        }
    }
    if(nX == -1) return 0;
    *nextX = nX;
    *nextY = nY;
    return 1;
}

void fun(int* sum, int r, int c, int x, int y, int grid[10][10], int visited[10][10], int step)
{
    *sum += grid[x][y];
    visited[x][y] = 1;
    int nextX, nextY;
    if(getNextXY(x, y, &nextX, &nextY, step + 1, grid, visited, r, c))
        fun(sum, r, c, nextX, nextY, grid, visited, step + 1);
}

int main()
{
    int r, c, grid[10][10], visited[10][10], min = __INT32_MAX__, minR = -1, minC = -1, sum = 0;

    scanf("%d%d", &r, &c);
    for(int i = 0; i < r; i++)
    {
        for(int j = 0; j < c; j++)
        {
            scanf("%d", &grid[i][j]);
            if(grid[i][j] < min)
            {
                min = grid[i][j];
                minR = i;
                minC = j;
            }
            visited[i][j] = 0;
        }
    }

    fun(&sum, r, c, minR, minC, grid, visited, 0);

    printf("%d\n", sum);

    return 0;
}