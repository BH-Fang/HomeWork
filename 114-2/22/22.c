#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
    int x, y;
} Pos;

int PosCMP(const void *a, const void *b)
{
    const Pos *posA = (const Pos *)a;
    const Pos *posB = (const Pos *)b;
    if (posA->x < posB->x) return -1;
    if (posA->x > posB->x) return 1; 
    if (posA->y < posB->y) return -1;
    if (posA->y > posB->y) return 1;

    return 0;
}

int func(Pos result[], int *blckCount, int startX, int startY, int N, char S[])
{
    if(S[0] == '0') return 1;
    else if(S[0] == '1')
    {
        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++)
                result[(*blckCount)++] = (Pos){startX + i, startY + j};
        return 1;
    }
    else if(S[0] == '2')
    {
        int i = 1, block = N / 2;
        i += func(result, blckCount, startX, startY, block, S + i);
        i += func(result, blckCount, startX, startY + block, block, S + i);
        i += func(result, blckCount, startX + block, startY, block, S + i);
        i += func(result, blckCount, startX + block, startY + block, block, S + i);
        return i;
    }
}

int main()
{
    char S[110];
    int N, blackCount = 0;
    Pos result[100];
    scanf("%s%d", S, &N);

    func(result, &blackCount, 0, 0, N, S);
    qsort(result, blackCount, sizeof(Pos), PosCMP);

    if(!blackCount) printf("all white\n");
    for(int i = 0; i < blackCount; i++)
        printf("%d,%d\n", result[i].x, result[i].y);

    return 0;
}
