#include <stdio.h>
#include <string.h>

typedef struct
{
    char str[20];
    int n;
} word_t;

void printSen(word_t sentence[], int len)
{
    for(int i = 0; i < len; i++)
    {
        printf("%s ", sentence[i].str);
    }
    printf("\n");
}

void replace(const word_t P, const word_t Q, word_t sentence[], int *len)
{
    for(int i = 0; i < *len; i++)
    {
        if(strcmp(sentence[i].str, P.str) == 0)
        {
            sentence[i] = Q;
        }
        else if(sentence[i].str[sentence[i].n - 1] == '.'
            || sentence[i].str[sentence[i].n - 1] == ','
            || sentence[i].str[sentence[i].n - 1] == '!'
            || sentence[i].str[sentence[i].n - 1] == '?'
            || sentence[i].str[sentence[i].n - 1] == ';'
            || sentence[i].str[sentence[i].n - 1] == ':')
        {
            char t[20], t1 = sentence[i].str[sentence[i].n - 1];
            strcpy(t, sentence[i].str);
            t[sentence[i].n - 1] = '\0';
            if(strcmp(t, P.str) == 0)
            {
                strcpy(t, Q.str);
                t[Q.n] = sentence[i].str[sentence[i].n - 1];
                t[Q.n + 1] = sentence[i].str[sentence[i].n] = '\0';
                strcpy(sentence[i].str, t);
                sentence[i].n = Q.n + 1;
            }
        }
    }
}

void insert(word_t w, int index, word_t sentence[], int *len)
{
    for(int i = *len - 1; i >= index; i--)
    {
        sentence[i + 1] = sentence[i];
    }
    sentence[index] = w;
    (*len)++;
}

void ins(const word_t P, const word_t Q, word_t sentence[], int *len, int isBack)
{
    for(int i = 0; i < *len; i++)
    {
        if(strcmp(sentence[i].str, P.str) == 0)
        {
            insert(Q, i + isBack, sentence, len);
            i++;
        }
        else if(sentence[i].str[sentence[i].n - 1] == '.'
            || sentence[i].str[sentence[i].n - 1] == ','
            || sentence[i].str[sentence[i].n - 1] == '!'
            || sentence[i].str[sentence[i].n - 1] == '?'
            || sentence[i].str[sentence[i].n - 1] == ';'
            || sentence[i].str[sentence[i].n - 1] == ':')
        {
            char t[20], t1 = sentence[i].str[sentence[i].n - 1];
            strcpy(t, sentence[i].str);
            t[sentence[i].n - 1] = '\0';
            if(strcmp(t, P.str) == 0)
            {
                insert(Q, i + isBack, sentence, len);
                i++;
            }
        }
    }
}

void _remove(int index, word_t sentence[], int *len)
{
    for(int i = index; i < *len - 1; i++)
    {
        sentence[i] = sentence[i + 1];
    }
    (*len)--;
}

void rem(const word_t P, word_t sentence[], int *len)
{
    for(int i = *len - 1; i >= 0; i--)
    {
        if(strcmp(sentence[i].str, P.str) == 0)
        {
            _remove(i, sentence, len);
        }
        else if(sentence[i].str[sentence[i].n - 1] == '.'
            || sentence[i].str[sentence[i].n - 1] == ','
            || sentence[i].str[sentence[i].n - 1] == '!'
            || sentence[i].str[sentence[i].n - 1] == '?'
            || sentence[i].str[sentence[i].n - 1] == ';'
            || sentence[i].str[sentence[i].n - 1] == ':')
        {
            char t[20], t1 = sentence[i].str[sentence[i].n - 1];
            strcpy(t, sentence[i].str);
            t[sentence[i].n - 1] = '\0';
            if(strcmp(t, P.str) == 0)
            {
                _remove(i, sentence, len);
            }
        }
    }
}

void reverse(word_t sentence[], int *len)
{
    word_t t[100];
    memcpy(t, sentence, sizeof(word_t) * (*len));
    for(int i = 0; i < *len; i++)
    {
        sentence[*len - i - 1] = t[i];
    }
}

int main()
{
    word_t sentence[100], sentence1[100], sentence2[100],sentence3[100], sentence4[100], sentence5[100];
    int len = 0, len1 = 0, len2 = 0, len3 = 0, len4 = 0, len5 = 0;    
    word_t P, Q;
    char In[500];
    
    fgets(In, 500, stdin);
    scanf("%s%s", P.str, Q.str);
    P.n = strlen(P.str);
    Q.n = strlen(Q.str);


    int l = 0, r = 1, i = 0;
    while(In[l] != '\0')
    {
        if(In[r] == ' ' || In[r] == '\n')
        {
            strncpy(sentence[i].str, In + l, r - l);
            sentence[i].n = r - l;
            sentence[i].str[r - l] = '\0';
            len++;
            i++;
            l = r + 1;
            r = l + 1;
        }
        else r++;
    }
    memcpy(sentence1, sentence, sizeof(sentence));
    memcpy(sentence2, sentence, sizeof(sentence));
    memcpy(sentence3, sentence, sizeof(sentence));
    memcpy(sentence4, sentence, sizeof(sentence));
    memcpy(sentence5, sentence, sizeof(sentence));
    len1 = len; len2 = len; len3 = len; len4 = len; len5 = len;

    replace(P, Q, sentence1, &len1);
    ins(P, Q, sentence2, &len2, 0);
    ins(P, Q, sentence3, &len3, 1);
    rem(P, sentence4, &len4);
    reverse(sentence5, &len5);
    printSen(sentence1, len1);
    printSen(sentence2, len2);
    printSen(sentence3, len3);
    printSen(sentence4, len4);
    printSen(sentence5, len5);
    return 0;
}