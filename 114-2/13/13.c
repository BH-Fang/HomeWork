#include <stdio.h>
#include <stdlib.h>

int baseMChar2Int(char ch)
{   
    return ch >= 'A' && ch <= 'Z' ? ch - 55 : ch - '0';
}

int baseM2decimal(char *pM, int M)
{
    int result = 0;
    while (*pM != '\0')
    {   
        result *= M;
        result += baseMChar2Int(*pM);
        pM++;
    }
    return result;
}

void decimal2BaseN(char *pResult, int decimalNum, int N)
{
    if (decimalNum == 0)
    {
        *pResult = '0';
        *(pResult + 1) = '\0';
        return;
    }
    char *temp = (char*)malloc(100 * sizeof(char));
    int len = 0;
    while (decimalNum)
    {   
        int t = decimalNum % N;
        *temp = t + (t >= 10 ? 55 : '0');
        temp++;
        len++;
        decimalNum = (int)(decimalNum / N);
    }
    temp--;
    for(int i = 0; i < len; i++)
    {
        *pResult = *temp;
        *temp--;
        pResult++;
    }    
    *pResult = '\0';
}

int main()
{
    int M, N, decimalNumber;
    char baseMNumber[100], baseNNumber[100], result[100];
    char *pM = baseMNumber, *pN = baseNNumber, *pResult = result;

    scanf("%d", &M);
    scanf("%s", baseMNumber);
    scanf("%d", &N);

    decimalNumber = baseM2decimal(baseMNumber, M);
    decimal2BaseN(pResult, decimalNumber, N);
    
    printf("%s", result);
    return 0;
}