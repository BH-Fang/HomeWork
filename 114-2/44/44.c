#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SPACE " "

typedef struct
{
    int visited;
    int to[20];
    int toCount;
} city;

int main()
{
    int N, X, Z, Y, haveY = 0;
    char str[20];
    city cities[100];
    for(int i = 0; i < 100; i++)
    {
        cities[i].toCount = 0;
        cities[i].visited = 0;
    }
    
    fgets(str, 20, stdin);
    str[strcspn(str, "\n")] = '\0';
    if(strlen(str) == 7)
        haveY = 1;
    char *token = strtok(str, SPACE);
    N = atoi(token);
    token = strtok(NULL, SPACE);
    X = atoi(token);
    token = strtok(NULL, SPACE);
    Z = atoi(token);
    if(haveY)
    {
        token = strtok(NULL, SPACE);
        Y = atoi(token);
    }
    for(int i = 0; i < N; i++)
    {
        int cityA, cityB;
        scanf("%d%d", &cityA, &cityB);
        cities[cityA].to[cities[cityA].toCount++] = cityB;
        cities[cityB].to[cities[cityB].toCount++] = cityA;
    }

    return 0;
}