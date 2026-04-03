#include <stdio.h>
#include <string.h>

void strToList(int *list, char *str, int *len)
{
    for(int i = 0; str[i] != '\0'; i++)
    {
        if(str[i] >= '0' && str[i] <= '9')
        {
            list[i / 2] = str[i] -'0';
            *len++;
        }
    }
}

int main()
{
    int m, list[25], len = 0;
    char getList[50];

    scanf("%d", m);
    fgets(getList, 50, stdin);
    getList[strcspn(getList, "\n")] = '\0';
    strToList(list, getList, &len);

    return 0;
}