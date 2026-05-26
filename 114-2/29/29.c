#include <stdio.h>
#include <string.h>

#define MAXN 10
#define INF 1000000000

int n;
int dist[MAXN][MAXN];
int path[MAXN];
int bestPath[MAXN];
int bestDist;

int remain[MAXN];
int remainCnt;
int remPath[MAXN];
int remBest[MAXN];
int remBestDist;
int remStart;

void dfsRem(int pos, int remVisited, int cur, int cost)
{
    if (cost >= remBestDist)
        return;
    if (pos == remainCnt)
    {
        if (cost < remBestDist)
        {
            remBestDist = cost;
            memcpy(remBest, remPath, remainCnt * sizeof(int));
        }
        return;
    }
    for (int i = 0; i < remainCnt; i++)
    {
        if (remVisited & (1 << i))
            continue;
        int next = remain[i];
        int w = dist[cur - 1][next - 1];
        if (w == 0)
            continue;
        remPath[pos] = next;
        dfsRem(pos + 1, remVisited | (1 << i), next, cost + w);
    }
}

void tsp(int pos, int visited, int cur, int cost)
{
    if (cost >= bestDist)
        return;
    if (pos == n)
    {
        if (cost < bestDist)
        {
            bestDist = cost;
            memcpy(bestPath, path, n * sizeof(int));
        }
        return;
    }
    for (int next = 1; next <= n; next++)
    {
        if (visited & (1 << (next - 1)))
            continue;
        int w = dist[cur - 1][next - 1];
        if (w == 0)
            continue;
        path[pos] = next;
        tsp(pos + 1, visited | (1 << (next - 1)), next, cost + w);
    }
}

int prefixDist(const int *p, int len)
{
    int sum = 0;
    for (int i = 0; i < len - 1; i++)
        sum += dist[p[i] - 1][p[i + 1] - 1];
    return sum;
}

int main(void)
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &dist[i][j]);

    int c, u, v;
    scanf("%d %d %d", &c, &u, &v);

    path[0] = 1;
    bestDist = INF;
    tsp(1, 1, 1, 0);

    dist[u - 1][v - 1] = 0;
    dist[v - 1][u - 1] = 0;

    int prefix[MAXN];
    for (int i = 0; i < c; i++)
        prefix[i] = bestPath[i];

    int start = prefix[c - 1];
    int visited = 0;
    for (int i = 0; i < c; i++)
        visited |= 1 << (prefix[i] - 1);

    remainCnt = 0;
    for (int i = 1; i <= n; i++)
        if (!(visited & (1 << (i - 1))))
            remain[remainCnt++] = i;

    remBestDist = INF;
    dfsRem(0, 0, start, 0);

    int finalPath[MAXN];
    for (int i = 0; i < c; i++)
        finalPath[i] = prefix[i];
    for (int i = 0; i < remainCnt; i++)
        finalPath[c + i] = remBest[i];

    int total = prefixDist(finalPath, n);

    for (int i = 0; i < n; i++)
    {
        if (i)
            putchar(' ');
        printf("%d", finalPath[i]);
    }
    putchar('\n');
    printf("%d\n", total);

    return 0;
}
