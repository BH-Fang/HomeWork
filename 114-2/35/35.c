#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int cmp(const void* a, const void* b)
{
    return (int)(*(char*)a - *(char*)b);
}

void set(char *result, char *input)
{
    int lenI = strlen(input), lenO = 0;

    for(int i = 0; i < lenI; i++)
    {
        int f = 0;
        for(int j = 0; j < lenO; j++)
        {
            if(result[j] == input[i])
            {
                f = 1;
                break;
            }
        }
        if(!f)
        {
            result[lenO] = input[i];
            lenO++;
        }
    }
    result[lenO] = '\0';
    qsort(result, lenO, sizeof(char), cmp);
}

void Intersection(char *result, char *a, char *b)
{
    int lenA = strlen(a), lenB = strlen(b), lenRes = 0;
    
    for(int i = 0; i < lenA; i++)
    {
        for(int j = 0; j < lenB; j++)
        {
            if(a[i] == b[j])
            {
                result[lenRes++] = a[i];
                break;
            }
        }
    }
    result[lenRes] = '\0';
}

int main()
{
    char S[101], P[101], setS[101], Pn[50][51], setPn[50][51];
    int n, count = 0;
    
    scanf("%s%d%s", S, &n, P);
    int lenP = strlen(P), lenPn = lenP / n;
    for(int i = 0; i < lenPn; i++)
    {
        strncpy(Pn[i], P + i * n, n);
        Pn[i][n] = '\0';
    }
    set(setS, S);
    for(int i = 0; i < lenPn; i++)
    {
        set(setPn[i], Pn[i]);
    }
    for(int i = 0; i < lenPn; i++)
    {       
        for(int j = i + 1; j < lenPn; j++)
        {
            char res[50];
            Intersection(res, setPn[i], setPn[j]);
            if(strcmp(res, setS) == 0) count++;
        }
    }

    printf("%d\n", count);

    return 0;
}