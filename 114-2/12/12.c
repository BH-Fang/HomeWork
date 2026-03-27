#include <stdio.h>
#include <string.h>

int isStrVailible(char str[], int len)
{
    if(((str[0] >= 'a' && str[0] <= 'z') || (str[0] >= 'A' && str[0] <= 'Z') || str[0] == '_') &&
      ((str[len - 1] >= 'a' && str[len - 1] <= 'z') || (str[len - 1] >= 'A' && str[len - 1] <= 'Z') || str[len - 1] == '_'))
        return 1;
    return 0;
}

void printInverse(char str[], int len)
{
    for(int i = len - 1; i >= 0; i--)
    {
        printf("%c", str[i]);
    }
    printf("\n");
}

int getRealLen(char str[], int originLen)
{   
    int spaceCount = 0;
    for(int i = 0; i < originLen; i++)
    {
        if(str[i] == ' ')
            spaceCount++;
    }
    return originLen - spaceCount;
}

int main()
{
    char str1[100], str2[100];
    int len1, len2;
    
    fgets(str1, sizeof(str1), stdin);
    fgets(str2, sizeof(str2), stdin);
    str1[strcspn(str1, "\n")] = '\0';
    str2[strcspn(str2, "\n")] = '\0';
    len1 = strlen(str1);
    len2 = strlen(str2);
    
    if(!isStrVailible(str1, len1) || !isStrVailible(str2, len2)) 
    {
        printf("Error");
        return 0;
    }
    printInverse(str1, len1);
    printInverse(str2, len2);
    if(getRealLen(str1, len1) >= getRealLen(str2, len2))
        printf("%s\n", str1);
    else
        printf("%s\n", str2);
    
    return 0;
}