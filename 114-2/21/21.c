#include <stdio.h>

typedef struct
{
    int face[6];
}Dice;

void roll(Dice *dice, char dir, int n)
{
    n = n % 4;
    for(int i = 0; i < n; i++)
    {
        int temp = dice->face[0];
        if (dir == 'F') 
        {
            dice->face[0] = dice->face[5];
            dice->face[5] = dice->face[1];
            dice->face[1] = dice->face[4];
            dice->face[4] = temp;
        } else if (dir == 'B') 
        {
            dice->face[0] = dice->face[4];
            dice->face[4] = dice->face[1];
            dice->face[1] = dice->face[5];
            dice->face[5] = temp;
        } else if (dir == 'L') 
        {
            dice->face[0] = dice->face[3];
            dice->face[3] = dice->face[1];
            dice->face[1] = dice->face[2];
            dice->face[2] = temp;
        } else if (dir == 'R') 
        {
            dice->face[0] = dice->face[2];
            dice->face[2] = dice->face[1];
            dice->face[1] = dice->face[3];
            dice->face[3] = temp;
        }
    }
}

int str2int(char t[])
{
    int i = 0, res = 0;
    while(t[i] >= '0' && t[i] <= '9')
    {
        res *= 10;
        res += t[i] - '0';
        i++;
    }
    return res;    
}

void getDots(int dots[], int N, Dice dices[])
{
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < N; j++)
        {
            char t[4];
            scanf("%s", t);
            roll(&dices[i], t[0], str2int(t + 1));
        }
        dots[i] = dices[i].face[0];
    }
}

int getScore(int dots[])
{
    if(dots[0] == dots[1] && dots[1] == dots[2]) return dots[0] * 2;
    else if(dots[0] == dots[1] && dots[1] != dots[2]) return dots[2];
    else if(dots[0] == dots[2] && dots[0] != dots[1]) return dots[1];
    else if(dots[1] == dots[2] && dots[0] != dots[1]) return dots[0];
    else return 0;
}

int main()
{
    Dice A[3], B[3];
    int N;
    int A_dots[3], B_dots[3], A_score = 0, B_score = 0;
    for(int i = 0; i < 3; i++)
    {   
        for(int j = 0; j < 6; j++)
        {
            int t;
            scanf("%d", &t);
            A[i].face[j] = t; B[i].face[j] = t;
        }
    }
    scanf("%d", &N);

    getDots(A_dots, N, A); getDots(B_dots, N, B);
    A_score = getScore(A_dots); B_score = getScore(B_dots);

    if(A_score > B_score) printf("A win\n");
    else if(A_score < B_score) printf("B win\n");
    else printf("Tie\n");
    printf("%d %d\n", A_score, B_score);

    return 0;
}