#include <stdio.h>
#include <string.h>

typedef struct
{
    char str[20];
    int n;
} word_t;

word_t sentance[100];
int len;

void printSen()
{
    for(int i = 0; i < len; i++)
    {
        printf("%s ", sentance[i].str);
    }
    printf("\n");
}

int main()
{
    word_t P, Q;
    char In[500];
    
    fgets(In, 500, stdin);
    scanf("%s%s", P.str, Q.str);

    int l = 0, r = 1, i = 0;
    while(In[l] != '\0')
    {
        if(In[r] == ' ' || In[r] == '\n')
        {
            strncpy(sentance[i].str, In + l, r - l);
            sentance[i].n = r - l;
            sentance[i].str[r - l] = '\0';
            len++;
            i++;
            l = r + 1;
            r = l + 1;
        }
        else r++;
    }

    printSen();
    return 0;
}