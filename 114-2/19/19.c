#include <stdio.h>
#include <string.h>

int compare(char *A, char *B) 
{
    int lenA = strlen(A);
    int lenB = strlen(B);
    
    if (lenA > lenB) 
        return 1;
    if (lenA < lenB) 
        return -1;
    return strcmp(A, B); 
}

void subtract(char *A, char *B) 
{
    char temp[110];
    int lenA = strlen(A);
    int lenB = strlen(B);
    int borrow = 0;
    int i = lenA - 1, j = lenB - 1;
    
    while(j >= 0)
    {
        int n = A[i] - B[j] - borrow;
        if(n >= 0)
        {
            A[i] = n + '0';
            borrow = 0;
        }   
        else
        {
            n += 10;
            A[i] = n + '0';
            borrow = 1;
        }
        i--; j--;
    }
    while(borrow)
    {
        if(A[i] == '0')
        {
            A[i] = '9';
            i--;
        }
        else
        {
            A[i] -= 1;
            borrow = 0;
        }
    }
    int start = 0;
    while(A[start] == '0' && start < lenA - 1)
    {
        start++;
    }
    if(start) 
    {
        int k = 0;
        while(A[start + k] != '\0') 
        {
            A[k] = A[start + k];
            k++;
        }
        A[k] = '\0';
    }
}   

void appendChar(char *str, char c) 
{
    int len = strlen(str);
    if(len == 1 && str[0] == '0') 
    {
        str[0] = c;
        str[1] = '\0';
    } 
    else 
    {
        str[len] = c;
        str[len + 1] = '\0';
    }
}

int devide(char *result, char *A, char *B, int len1, int len2)
{
    char current[300] = "0";
    int result_idx = 0;

    for (int i = 0; i < len1; i++) 
    {
        appendChar(current, A[i]);
        int q = 0;
        while(compare(current, B) >= 0) 
        { 
            subtract(current, B);
            q++;            
        }
        result[result_idx] = q + '0'; 
        result_idx++;
    }
    result[result_idx] = '\0'; 
    int start = 0;
    while(result[start] == '0' && start < result_idx - 1)
    {
        start++;
    }
    if(start) 
    {
        int k = 0;
        while(result[start + k] != '\0') 
        {
            result[k] = result[start + k];
            k++;
        }
        result[k] = '\0';
    }
    result_idx = strlen(result);
    if (strcmp(current, "0") == 0) {
        return result_idx;
    }
    result[result_idx] = '.';
    result_idx++;
    
    for (int i = 0; i < 100; i++) {
        appendChar(current, '0');
        int q = 0;
        while(compare(current, B) >= 0) 
        { 
            subtract(current, B);
            q++;            
        }
        result[result_idx] = q + '0';
        result_idx++;
        if (strcmp(current, "0") == 0) 
        {
            break;
        }
    }
    result[result_idx] = '\0';
    result_idx -= 1;
    while(result[result_idx] == '0')
    {
        result[result_idx] = '\0';
        result_idx--;
    }

    return strlen(result); 
}

int main()
{
    char num1[110], num2[110], result[300];
    int len1, len2, lenResult;
    int isNum1Neg = 0, isNum2Neg = 0, isResultNeg = 0;

    scanf("%s%s", num1, num2);

    len1 = strlen(num1);
    len2 = strlen(num2);
    if(num1[0] == '-')
        isNum1Neg = 1;
    if(num2[0] == '-')
        isNum2Neg = 1;
    isResultNeg = isNum1Neg ^ isNum2Neg;
    lenResult = devide(result, num1 + isNum1Neg, num2 + isNum2Neg, len1 - isNum1Neg, len2 - isNum2Neg);
    
    if (strcmp(result, "0") == 0) 
        printf("0\n");
    else 
    {
        if (isResultNeg) 
            printf("-");
        printf("%s\n", result);
    }

    return 0;
}