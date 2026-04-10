#include <stdio.h>

typedef struct
{
  int first, second;
} pair;

int pairCmp(pair p1, pair p2)
{
    if(p1.first > p2.first)
        return 1;
    if(p1.first < p2.first)
        return 0;
    if(p1.second > p2.second)
        return 1;
    if(p1.second < p2.second)
        return 0;
    return 2;
}

void pairSwap(pair *p1, pair *p2)
{
    pair t = {.first = p1->first, .second = p1->second};
    p1->first = p2->first; p1->second = p2->second;
    p2->first = t.first; p2->second = t.second;
}

void pairSort(pair pairs[], int count)
{
    for(int i = count - 1; i > 0; i--)
    {
        for(int j = 0; j < i; j++)
        {
            if(pairCmp(pairs[j], pairs[j + 1]) == 1)
                pairSwap(&pairs[j], &pairs[j + 1]);
        }
    }
}

int main()
{
    int N, list[110], count = 0;
    pair pairs[12100];

    scanf("%d", &N);
    for(int i = 0; i < N; i++)
    {
        scanf("%d", &list[i]);
    }

    for(int i = 0; i < N; i++)
    {
        for(int j = i + 1; j < N; j++)
        {
            if(list[i] > list[j])
            {
                pairs[count].first = list[i];
                pairs[count].second = list[j];
                count++;
            }
        }
    }
    pairSort(pairs, count);

    if(!count)
    {
        printf("0\n");
        return 0;
    }
    for(int i = 0; i < count; i++)
    {   
        if(i && (pairCmp(pairs[i], pairs[i - 1])  == 2))
            continue;
        printf("(%d,%d)\n", pairs[i].first, pairs[i].second);
    }
    return 0;
}
