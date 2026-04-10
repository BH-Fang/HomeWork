#include <stdio.h>
#include <string.h>

void bigIntMinus(char *result, char *bigInt1, char *bigInt2, int len1, int len2);
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
        for(int i = pr; i < 110; i++)
        {
            result[i - pr] = result_t[i];
        }
        result[110 - pr] = '\0';
    }
    else if(bigInt1[0] != '-' && bigInt2[0] == '-')
        bigIntMinus(result, bigInt1, bigInt2 + 1, len1, len2 - 1);
    else if(bigInt1[0] == '-' && bigInt2[0] != '-')
        bigIntPlus(result, bigInt2, bigInt1, len2, len1);
    else
    {
        bigIntPlus(result_t, bigInt1 + 1, bigInt2 + 1, len1 - 1, len2 - 1);
        result[0] = '-';
        strcpy(result + 1, result_t);
    }
    
}

void bigIntMinus(char *result, char *bigInt1, char *bigInt2, int len1, int len2)
{
    char result_t[110];
    if(bigInt1[0] != '-' && bigInt2[0] != '-')
    {
        int cmp = 0;
        if(len1 > len2)
            cmp = 1;
        else if(len1 < len2)
            cmp = -1;
        else 
            cmp = strcmp(bigInt1, bigInt2);

        if(!cmp)
            strcpy(result, "0");
        else if(cmp > 0)
        {
            int p1 = len1 - 1, p2 = len2 - 1, pr = 109, borrow = 0, diff;
            while(p1 >= 0)
            {
                diff = (bigInt1[p1] - '0') - ((p2 >= 0) ? (bigInt2[p2] - '0') : 0) - borrow;
                if(diff < 0) 
                {
                    diff += 10;
                    borrow = 1;
                } 
                else 
                    borrow = 0;
                result_t[pr] = diff + '0';
                p1--;
                p2--;
                pr--;
            }
            pr++;
            while(pr < 109 && result_t[pr] == '0') 
            {
                pr++;
            }
            for(int i = pr; i <= 109; i++) 
            {
                result[i - pr] = result_t[i];
            }
            result[110 - pr] = '\0';
        }
        else
        {
            bigIntMinus(result_t, bigInt2, bigInt1, len2, len1);
            result[0] = '-';
            strcpy(result + 1, result_t);
        }
    }
    else if(bigInt1[0] != '-' && bigInt2[0] == '-')
        bigIntPlus(result, bigInt1, bigInt2 + 1, len1, len2 - 1);
    else if(bigInt1[0] == '-' && bigInt2[0] != '-')
    {
        bigIntPlus(result_t, bigInt1 + 1, bigInt2, len1 - 1, len2);
        result[0] = '-';
        strcpy(result + 1, result_t);
    }
    else
    {
        bigIntMinus(result, bigInt2 + 1, bigInt1 + 1, len2 - 1, len1 - 1);
    }
}

void bigIntTimes(char *result, char *bigInt1, char *bigInt2, int len1, int len2)
{   
    int sign = 1;
    char *num1 = bigInt1;
    char *num2 = bigInt2;
    int l1 = len1, l2 = len2;
    if (num1[0] == '-') 
    { 
        sign *= -1; 
        num1++; 
        l1--; 
    }
    if (num2[0] == '-') 
    { 
        sign *= -1; 
        num2++; 
        l2--; 
    }
    if ((l1 == 1 && num1[0] == '0') || (l2 == 1 && num2[0] == '0')) {
        strcpy(result, "0");
        return;
    }
    int temp[210] = {0};
    for (int i = l1 - 1; i >= 0; i--) 
    {
        for (int j = l2 - 1; j >= 0; j--) 
        {
            int mul = (num1[i] - '0') * (num2[j] - '0');
            int sum = mul + temp[i + j + 1];
            temp[i + j + 1] = sum % 10;
            temp[i + j] += sum / 10;
        }
    }
    int pr = 0;
    if (sign == -1) 
    {
        result[pr++] = '-';
    }
    int start = 0;
    while (start < l1 + l2 && temp[start] == 0)
    {
        start++;
    }
    for (int i = start; i < l1 + l2; i++)
    {
        result[pr++] = temp[i] + '0';
    }
    result[pr] = '\0';
}

int main()
{
    char bigInt1[110], bigInt2[110], plusResult[110], minusResult[110], timesResult[210];
    int len1, len2;

    scanf("%s%s", bigInt1, bigInt2);
    len1 = strlen(bigInt1);
    len2 = strlen(bigInt2);

    bigIntPlus(plusResult, bigInt1, bigInt2, len1, len2);
    bigIntMinus(minusResult, bigInt1, bigInt2, len1, len2);
    bigIntTimes(timesResult, bigInt1, bigInt2, len1, len2);

    printf("%s\n%s\n%s\n", plusResult, minusResult, timesResult);
    return 0;
}