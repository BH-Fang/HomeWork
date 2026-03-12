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
            for(int i = 0; i < M; i++)
            {
                p(M - i - 1, '#');
            }
        case 2:
    }
    return 0;
}