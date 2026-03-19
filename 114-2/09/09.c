#include <stdio.h>
#include <math.h>

void G(int n, int k, char result[], int pos)
{
    if(n == 1)
    {
        result[pos++] = k + '0';
        result[pos] = '\0';
    }
    else if(k < 2 << (n - 2))
    {
        result[pos++] = '0';
        G(n - 1, k, result, pos);
    }
    else
    {
        result[pos++] = '1';
        G(n - 1, (2 << (n - 1)) - 1 - k, result, pos);
    }
}

int main()
{
    int n, k;
    scanf("%d", &n);
    while (n != -1) 
    {
        scanf("%d", &k);
        char result[10];
        G(n, k, result, 0);
        printf("%s\n", result);
        scanf("%d", &n);
    }
    return 0;
}

