#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
    char str[15];
    int n;
} Word;

typedef struct 
{
    Word Words[15];
    int n;
} Sentence;

void strToSentence(char *str, Sentence *S)
{
    char delim[] = " ";
    char *token = strtok(str, delim);
    int i = 0;
    while(token != NULL)
    {
        strcpy(S->Words[i].str, token);
        S->Words[i].n = strlen(S->Words[i].str);
        token = strtok(NULL, delim);
        i++;
    }
    S->n = i;    
}

int haveSame(Sentence S1, Sentence S2)
{
    for(int i = 0; i < S1.n; i++)
    {
        for(int j = 0; j < S2.n; j++)
        {
            if(strcmp(S1.Words[i].str, S2.Words[j].str) == 0)
                return 1;
        }
    }
    return 0;
}

int WordCmp(const void *a, const void *b)
{
    Word *_a = (Word*)a, *_b = (Word*)b;
    return strcmp(_a->str, _b->str);
}

int isOK(Sentence S, Sentence S1, Sentence S2)
{
    if(haveSame(S1, S2))
        return 0;
    qsort(S.Words, S.n, sizeof(Word), WordCmp); 
    qsort(S1.Words, S1.n, sizeof(Word), WordCmp);
    qsort(S2.Words, S2.n, sizeof(Word), WordCmp);   
    int i = 0, j = 0, k = 0;
    while(i < S.n)
    {
        if(j < S1.n && strcmp(S.Words[i].str, S1.Words[j].str) == 0)
        {
            do 
                i++;
            while (i < S.n && strcmp(S.Words[i].str, S.Words[i - 1].str) == 0);
            do 
                j++;
            while (j < S1.n && strcmp(S1.Words[j].str, S1.Words[j - 1].str) == 0);
        }
        else if(k < S2.n && strcmp(S.Words[i].str, S2.Words[k].str) == 0)
        {
            do 
                i++;
            while (i < S.n && strcmp(S.Words[i].str, S.Words[i - 1].str) == 0);
            do 
                k++;
            while (k < S2.n && strcmp(S2.Words[k].str, S2.Words[k - 1].str) == 0);
        }
        else return 0;
    }
    return 1;
}

int main()
{   
    Sentence S, Sn[15];
    char str[110];
    int n, ans = 0;

    fgets(str, 110, stdin);
    str[(int)strcspn(str, "\n")] = '\0';
    strToSentence(str, &S);
    scanf("%d", &n);
    getchar();
    for(int i = 0; i < n; i++)
    {
        fgets(str, 110, stdin);
        str[(int)strcspn(str, "\n")] = '\0';
        strToSentence(str, Sn + i);
    }

    for(int i = 0; i < n; i++)
    {
        for(int j = i + 1; j < n; j++)
        {
            if(isOK(S, Sn[i], Sn[j]))
                ans++;
        }
    }

    printf("%d\n", ans);

    return 0;
}