#include <stdio.h>
#include <string.h>

#define SWAP(x,y) {int t; t = x; x = y; y = t;}

int getMinIndex(const int list[], int left, int right)
{
    int minIndex = left;
    for(int i = left + 1; i < right; i++)
        if(list[i] < list[minIndex]) minIndex = i;
    return minIndex;
}

void selectionSort(int list[], int n, int *cs, int *ms)
{
    for(int i = 0; i < n - 1; i++)
    {   
        int minIndex = getMinIndex(list, i, n);
        *cs += (n - i - 1);
        if(list[minIndex] != list[i])
        {
            SWAP(list[minIndex], list[i]);
            *ms += 3;
        } 
    }
}

void insertionSort(int list[], int n, int *ci, int *mi)
{
    int target;
    for (int i = 1; i < n; i++) 
    {
        target = list[i];
        (*mi)++;
        int j = i;
        while(1)
        {   
            (*ci)++;
            if(j > 0)
            {
                (*ci)++;
                if(list[j - 1] > target)
                {
                    list[j] = list[j - 1];
                    (*mi)++;
                }
                else break;
                j--;
            }
            else break;            
        }
        list[j] = target;
        (*mi)++;
    }
}

int main()
{
    int N, list[15], cs = 0, ms = 0, ci = 0, mi = 0;

    scanf("%d", &N);
    for(int i = 0; i < N; i++) 
        scanf("%d", &list[i]);

    int t1[15], t2[15];
    memcpy(t1, list, sizeof(list));
    memcpy(t2, list, sizeof(list));
    selectionSort(t1, N, &cs, &ms);
    insertionSort(t2, N, &ci, &mi);

    printf("\n%d %d\n%d %d\n", cs, ms, ci, mi);    
    return 0;
}