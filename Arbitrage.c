#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
double map[21][21];
int ans[40], alen;
typedef struct Arc
{
    int to, step;
} Arc;
int spfa(int st, int n)
{
    double dis[21][21];
    int pre[21][21], used[21][21];
    memset(dis, 0, sizeof(dis));
    memset(used, 0, sizeof(used));
    int i, j;
    Arc tn, tmp;
    tn.to = st, tn.step = 0;
    struct
    {
        Arc data[2000];
        int front, rear;
    } Q;
    Q.front = 0;
    Q.rear = 0;
    Q.data[Q.rear++] = tn;
    dis[st][0] = 1;
    while (Q.front != Q.rear)
    {
        tn = Q.data[Q.front++];
        if (Q.front == 2000)
            Q.front = 0;
        used[tn.to][tn.step] = 0;
        if (tn.step > n || tn.step >= alen)
            continue;
        for (i = 1; i <= n; i++)
        {
            if (dis[tn.to][tn.step] * map[tn.to][i] > dis[i][tn.step + 1])
            {
                dis[i][tn.step + 1] = dis[tn.to][tn.step] * map[tn.to][i];
                tmp.to = i, tmp.step = tn.step + 1;
                pre[tmp.to][tmp.step] = tn.to;
                if (used[tmp.to][tmp.step] == 0)
                {
                    used[tmp.to][tmp.step] = 1;
                    Q.data[Q.rear++] = tmp;
                    if (Q.rear == 2000)
                        Q.rear = 0;
                }
            }
        }
    }
    for (i = 1; i <= n; i++)
    {
        if (dis[st][i] > 1.01)
        {
            if (i < alen)
            {
                alen = i;
                j = st;
                while (i >= 0)
                {
                    ans[i] = j;
                    j = pre[j][i];
                    i--;
                }
            }
            return 0;
        }
    }
    return -1;
}
int main()
{
    int n, i, j;
    FILE *arbitrage_file;
    arbitrage_file = fopen("arbitrage.txt", "r");
    if (arbitrage_file != NULL)
    {
        while (fscanf(arbitrage_file, "%d", &n) == 1)
        {
            for (i = 1; i <= n; i++)
            {
                for (j = 1; j <= n; j++)
                {
                    if (i == j)
                        continue;
                    fscanf(arbitrage_file, "%lf", &map[i][j]);
                }
                map[i][i] = 1;
            }
            alen = INT_MAX;
            for (i = 1; i <= n; i++)
            {
                spfa(i, n);
            }
            if (alen != INT_MAX)
            {
                for (i = 0; i <= alen; i++)
                {
                    if (i)
                        putchar(' ');
                    printf("%d", ans[i]);
                }
                puts("");
            }
            else
            {
                puts("no arbitrage sequence exists");
            }
        }
    }
    else
    {
        printf("Not able to open the file.\n");
    }
    fclose(arbitrage_file);
    return 0;
}
