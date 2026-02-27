#include <stdio.h>
#include <stdbool.h>
#define convert 97
int main()
{
    int S0, S1, S2;
    char e1, e2;
    int ans[5];
    scanf("%d%d %c %c", &S0, &S1, &e1, &e2);
    int e1_int = (int)e1 - convert, e2_int = (int)e2 - convert;
    bool isInputCorrect = true;

    if(S0 < 0 || S0 > 63)
    {
        printf("S0 ERROR\n");
        isInputCorrect = false;
    }
    if(S1 < 0 || S1 > 63)
    {
        printf("S1 ERROR\n");
        isInputCorrect = false;
    }
    if(e1 < 'a' || e1 > 'f')
    {
        printf("e1 ERROR\n");
        isInputCorrect = false;
    }
    if(e2 < 'a' || e2 > 'f')
    {
        printf("e2 ERROR\n");
        isInputCorrect = false;
    }
    if(!isInputCorrect) return 0;

    S2 = S1 | (1 << e1_int);
    ans[0] = S2 & (1 << e2_int);
    ans[2] = S2 & S0;
    ans[1] = ans[2] == S2;
    ans[3] = S0 | S2;
    ans[4] = S0 & ~S2;
    
    if(ans[0]) printf("Y\n"); else printf("N\n");
    if(ans[1]) printf("Y\n"); else printf("N\n");
    for(int i = 2; i < 5; i++)
    {
        printf("%d\n", ans[i]);
    }
    
    return 0;
}