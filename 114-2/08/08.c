#include <stdio.h>
#include <string.h>

int isInt(char str[],int len)
{   
    if(!(len >= 1 && len <= 50))
        return 0;
    for(int i = 0; i < len; i++)
    {   
        if(!i && str[i] == '-' && len > 1) 
            continue;
        if((!i || (i == 1 && str[0] == '-')) && str[i] == '0')
            if(i != len - 1)
                return 0;
        if(!(str[i] >= '0' && str[i] <= '9'))
            return 0;
    }
    return 1;
}

int isFraction(char str[],int len)
{
    if(!(len >= 3 && len <= 10))
        return 0;
    int indexOfDevide = -1, numOfDevide = 0;
    for(int i = 0; i < len; i++)
    {
        if(str[i] == '/')
        {
            indexOfDevide = i;
            numOfDevide ++;
        }
    }
    if(numOfDevide != 1)
        return 0;
    int up = 0, down = 0;
    int startIndex = 0;
    if(str[0] == '-')
        startIndex = 1;
    for(int i = startIndex; i < indexOfDevide; i++)
    {
        if(i == startIndex && str[i] == '0')
            return 0;
        if(!(str[i] >= '0' && str[i] <= '9'))
            return 0;
        up *= 10;
        up += (int)(str[i] - '0');
    }
    for(int i = indexOfDevide + 1; i < len; i++)
    {
        if(i == indexOfDevide + 1 && str[i] == '0')
            return 0;
        if(!(str[i] >= '0' && str[i] <= '9'))
            return 0;
        down *= 10;
        down += (int)(str[i] - '0');
    }
    if(up == 0 || down == 0)
        return 0;
    if(up < down)
        return 1;
    else
        return 2;
}

int isMixedFraction(char str[],int len)
{
    if(!(len >= 5 && len <= 10))
        return 0;
    int indexOfSpace = -1, numOfSpace = 0, indexOfDevide = -1, numOfDevide = 0;
    for(int i = 0; i < len; i++)
    {
        if(str[i] == ' ')
        {
            indexOfSpace = i;
            numOfSpace ++;
        }
        else if(str[i] == '/')
        {
            indexOfDevide = i;
            numOfDevide ++;
        }
    }
    if(numOfDevide != 1 || numOfSpace != 1 || indexOfSpace == 0 || (indexOfSpace == 1 && str[0] == '-'))
        return 0;
    int startIndex = (str[0] == '-' ? 1 : 0);
    if(str[startIndex] == '0' && startIndex != indexOfSpace - 1)
        return 0;
    for(int i = startIndex; i < indexOfSpace; i++)
    {   
        if(!(str[i] >= '0' && str[i] <= '9'))
            return 0;
    }
    int up = 0, down = 0;
    startIndex = indexOfSpace + 1;
    if(str[startIndex] == '0' || str[indexOfDevide + 1] == '0')
        return 0;
    for(int i = startIndex; i < indexOfDevide; i++)
    {
        if(!(str[i] >= '0' && str[i] <= '9'))
            return 0;
        up *= 10;
        up += (int)(str[i] - '0');
    }
    for(int i = indexOfDevide + 1; i < len; i++)
    {
        if(!(str[i] >= '0' && str[i] <= '9'))
            return 0;
        down *= 10;
        down += (int)(str[i] - '0');
    }
    if(up == 0 || down == 0)
        return 0;
    if(up < down)
        return 1;
    else
        return 0;
}

int isFloat(char str[],int len)
{   
    if(!(len >= 3 && len <= 50))
        return 0;
    int indexOfDot = -1, numOfDot = 0;
    for(int i = 0; i < len; i++)
    {
        if(str[i] == '.')
        {
            indexOfDot = i;
            numOfDot ++;
        }
    }
    if(numOfDot != 1 || indexOfDot == 0 || indexOfDot == len - 1 || (indexOfDot == 1 && str[0] == '-'))
        return 0;
    int startIndex = (str[0] == '-' ? 1 : 0);
    if(str[startIndex] == '0' && startIndex != indexOfDot - 1)
            return 0;
    for(int i = startIndex; i < indexOfDot; i++)
    {   
        if(!(str[i] >= '0' && str[i] <= '9'))
            return 0;
    }
    for(int i = indexOfDot + 1; i < len; i++)
    {   
        if(!(str[i] >= '0' && str[i] <= '9'))
            return 0;
    }
    return 1;
}

int isVariable(char str[],int len)
{
    if(!(len >= 1 && len <= 10))
        return 0;
    for(int i = 0; i < len; i++)
    {
        if(!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= '0' && str[i] <= '9') || str[i] == '_'))
            return 0;
    }
    if((str[0] >= '0' && str[0] <= '9'))
        return 0;
    return 1;
}

int main()
{
    char In[60];
    char ans[7][20];
    int N = 0;
    scanf("%d", &N);
    while(getchar() != '\n');
    for(int i = 0; i < N; i++)
    {
        fgets(In, sizeof(In), stdin);
        int len = strlen(In);
        In[strcspn(In, "\r\n")] = '\0'; 
        len = strlen(In); 
        if(In[len - 1] == ' ')
        {
            len -= 1;
            In[len] = '\0';
        }
        if(isInt(In, len))
            strcpy(ans[i], "integer");
        else if(isFraction(In, len) == 1)
            strcpy(ans[i], "proper fraction");
        else if(isFraction(In, len) == 2)
            strcpy(ans[i], "improper fraction");
        else if(isMixedFraction(In, len))
            strcpy(ans[i], "mixed fraction");
        else if(isFloat(In, len))
            strcpy(ans[i], "float");
        else if(isVariable(In, len))
            strcpy(ans[i], "variable");
        else
            strcpy(ans[i], "string");
    }

    for(int i = 0; i < N; i++)
    {
        printf("%s\n", ans[i]);
    }
    return 0;
}