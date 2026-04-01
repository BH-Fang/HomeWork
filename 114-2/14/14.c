#include <stdio.h>
#include <math.h>
#include <string.h>

int gcd(int n,int m)
{
    return  m == 0 ? n : gcd(m, n % m);
}

void getM(char *m, int x1,int y1,int x2,int y2)
{
    int up = y1 - y2, down = x1 - x2, g;
    int isNagitive;
    if(!(up % down))
    {
        snprintf(m, 50, "%d", up / down);
        return;
    }
    isNagitive = (up < 0) ^ (down < 0);
    up = abs(up);
    down = abs(down);
    g = gcd(up, down);
    up = up / g;
    down = down / g;
    if(isNagitive)
        snprintf(m, 50, "-%d/%d", up, down);
    else
        snprintf(m, 50, "%d/%d", up, down);
}

int getB(char *b, int x1,int y1,int x2,int y2)
{
    int up = (x2 * y1 - x1 * y2), down = (x2 - x1), g;
    int isNagitive = (up < 0) ^ (down < 0);
    up = abs(up);
    down = abs(down);
    if(!(up % down))
    {
        snprintf(b, 50, "%d", up / down);
        return isNagitive;
    }
    g = gcd(up, down);
    up = up / g;
    down = down / g;
    snprintf(b, 50, "%d/%d", up, down);
    return isNagitive;
}

int main()
{
    int N, x1, x2, y1, y2;
    char m[50], b[50];

    scanf("%d", &N);
    for(int i = 0; i < N; i++)
    {
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        getM(m, x1, y1, x2, y2);
        int bIsNegitive = getB(b, x1, y1, x2, y2);
        
        if(!strcmp(m, "1"))
            printf("y = x ");
        else if(!strcmp(m, "-1"))
            printf("y = -x ");
        else if(!strcmp(m, "0"))
            printf("y = ");
        else
            printf("y = %sx ", m);
        
        if(!strcmp(m, "0"))
        {
            if(bIsNegitive)
                printf("-%s\n", b);
            else
                printf("%s\n", b);
        }
        else if(strcmp(b, "0"))
        {
            if(bIsNegitive)
                printf("- %s\n", b);
            else
                printf("+ %s\n", b);
        }
        else
            printf("\n");
    }

    return 0;
}