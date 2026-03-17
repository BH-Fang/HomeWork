#include <stdio.h>
#include <string.h>

int binary2int(char binary[])
{
    int len = strlen(binary);
    int result = 0;
    for(int i = 0; i < len; i++)
    {
        result = result << 1;
        result += binary[i] - '0';
    }
    return result;
}

void int2binary(int n, char result[])
{
    for(int i = 3; i >= 0; i--)
    {
        result[i] = (n % 2 ? '1' : '0');
        n = n >> 1;
    }
    result[4] = '\0';   
}

void C(int M, int *count)
{   
    if(!M || M == 1)
        return;
    if(M % 2)
    {
        (*count)++;
        return C((M + 1) / 2, count);
    }
    else
    {
        (*count)++;
        C(M / 2, count);
    }
}

int main()
{
    while(1)
    {
        int count = 0;
        char input[9], result[5];
        scanf("%s", input);
        if(input[0] == '-' && input[1] == '1')
            return 0;
        C(binary2int(input), &count);
        int2binary(count, result);
        printf("%s\n", result);
    }
    return 0;
}
