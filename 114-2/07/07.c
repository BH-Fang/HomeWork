#include <stdio.h>
void p(int n, char c)
{
    for(int i = 0; i < n; i++)
    {
        printf("%c", c);
    }
}
int main()
{
    int N, M;
    scanf("%d%d", &N, &M);
    if(!(N >= 1 && N <= 2) || !(M >= 2 && M <= 9))
    {
        printf("error");
        return 0;
    }
    switch(N)
    {
        case 1:
            int eng = 64;
            for(int i = 0; i < M; i++)
            {
                p(M - i - 1, '#');
                printf("*");
                for(int j = 0; j < i; j++)
                    printf("%c*", (char)eng);
                p(M - i - 1, '#');
                if(eng != 67) eng += 1;
                else eng = 65;
                printf("\n");
            }
            break;
        case 2:
            for(int i = 0; i < M; i++)
            {   
                for(int j = i + 1; j > 0; j--) printf("%d", j);
                p((M - i) * 2, '*');
                for(int j = 1; j < i + 2; j++) printf("%d", j);
                printf("\n");
            }
            break;
    }
    return 0;
}