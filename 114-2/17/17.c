#include <stdio.h>
#include <string.h>
void bigIntPlus(char *result, char *bigInt1, char *bigInt2, int len1, int len2)
{   
    char result_t[110];
    int p1 = len1 - 1, p2 = len2 - 1, pr = 109, carry = 0, sum;
    if(bigInt1[0] != '-' && bigInt2[0] != '-')
    {
        while(p1 >= 0 || p2 >= 0 || carry > 0)
        {   

            sum =  (p1 >= 0 ? bigInt1[p1] - '0' : 0) + (p2 >= 0 ? bigInt2[p2] - '0' : 0) + carry;
            carry = 0;
            if(sum >= 10)
            {
                carry = 1;
                sum -= 10;
            }
            result_t[pr] = sum + '0';
            p1--;
            p2--;
            pr--;
        }
        pr++;
    }
    else if(bigInt1[0] != '-' && bigInt2[0] == '-')
    {
        int is1biggerthan2 = 1;
        if()
    }
    else if(bigInt1[0] == '-' && bigInt2[0] != '-')
    {
        bigIntPlus(result, bigInt2, bigInt1, len2, len1);
        return;
    }
    for(int i = pr; i < 110; i++)
    {
        result[i - pr] = result_t[i];
    }
    result[110 - pr] = '\0';
}

void bigIntMinus(char *result, char *bigInt1, char *bigInt2)
{

}

void bigIntTimes(char *result, char *bigInt1, char *bigInt2)
{

}

int main()
{
    char bigInt1[110], bigInt2[110], plusResult[110], minusResult[110], timesResult[210];
    int len1, len2;

    scanf("%s%s", bigInt1, bigInt2);
    len1 = strlen(bigInt1);
    len2 = strlen(bigInt2);

    bigIntPlus(plusResult, bigInt1, bigInt2, len1, len2);

    printf("%s\n", plusResult);
    return 0;
}