#include <stdio.h>
#include <string.h>

int isUpper(char c)
{
    return c >= 'A' && c <= 'Z';
}

int main()
{
    int N, k;
    char S[51];

    scanf("%d", &N);
    for(int i = 0; i < N; i++)
    {
        scanf("%s%d", S, &k);

        int max_blocks = 0, len = strlen(S), L[50], dp[50];
        for(int j = 0; j < len; j++)
        {
            if (j > 0 && isUpper(S[j]) == isUpper(S[j-1])) 
                L[j] = L[j-1] + 1;
            else 
                L[j] = 1;
            if (L[j] == k) 
                if (j - k >= 0) 
                    dp[j] = dp[j-k] + 1;
                else 
                    dp[j] = 1;
            else if (L[j] > k) 
                dp[j] = 1;
            else 
                dp[j] = 0;  
            if(dp[j] > max_blocks)  
                max_blocks = dp[j];
        }
        if(max_blocks >= 2)
            printf("%d\n", max_blocks * k);
        else
            printf("0\n");
    }
    return 0;
}