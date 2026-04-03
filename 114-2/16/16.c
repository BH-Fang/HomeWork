#include <stdio.h>
#include <string.h>

int getResult(int m, int len, int *list, int result[][10])
{
    int count = 0;
    for(int i = 0; i < len - m + 1; i++)
    {
        int S = 0, isValid = 1, t[10] = {0};
        for(int j = 0; j < m; j++)
        {
            int n = list[i + j];
            if(S & (1 << n))
            {
                isValid = 0;
                break;
            }
            else
            {
                t[j] = n;
                S = S | (1 << n);
            }
        }
        if(isValid)
        {
            for(int j = 0; j < m; j++)
            {
                result[count][j] = t[j];
            }
            count++;
        }
    }
    return count;
}

void swapList(int m, int list2d[][10], int ind1, int ind2)
{
    int temp[10];
    for(int i = 0; i < m; i++)
    {
        temp[i] = list2d[ind1][i];
        list2d[ind1][i] = list2d[ind2][i];
        list2d[ind2][i] = temp[i];        
    }
}

int isList1BiggerThanList2(int m, int *list1, int *list2)
{
    for(int i = 0; i < m; i++)
    {
        if(list1[i] > list2[i]) 
            return 1;
        if(list1[i] < list2[i]) 
            return 0;
    }
    return 2;
}

void sortResult(int m, int count, int result[][10])
{   
    for(int i = count - 1; i >= 0; i--)
    {   
        int has_sorted = 0;
        for(int j = 0; j < i; j++)
        if(isList1BiggerThanList2(m, result[j], result[j + 1]))
        {
            swapList(m, result, j, j+1);
            has_sorted = 1;
        }
        if(!has_sorted)
            break;   
    }
}

int main()
{
    int m, len = 0, list[30], result[100][10], count = 0;

    scanf("%d", &m);
    while(scanf("%d", &list[len]) == 1)
    {
        len++;
        if(getchar() == '\n')
            break;
    }
    
    count = getResult(m, len, list, result);
    sortResult(m, count, result);

    printf("%d\n", count);
    for(int i = 0; i < count; i++)
    {
        if(i != 0 && isList1BiggerThanList2(m, result[i], result[i - 1]) == 2)
                continue; 
        for(int j = 0; j < m; j++)
        {    
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }

    return 0;
}