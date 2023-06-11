#include <stdio.h>

#define MAX_N 30

int main()
{
    int Case = 0, n;
    while (scanf("%d", &n) == 1)
    {
        int streets[MAX_N][MAX_N] = {{0}};
        int N = 0;

        for (int i = 1; i <= n; ++i)
        {
            int u, v;
            scanf("%d %d", &u, &v);
            streets[u][v] = 1;
            N = (u > N) ? u : N;
            N = (v > N) ? v : N;
        }

        for (int k = 0; k <= N; ++k)
        {
            for (int i = 0; i <= N; ++i)
            {
                for (int j = 0; j <= N; ++j)
                {
                    if (streets[i][k] && streets[k][j])
                    {
                        streets[i][j] += streets[i][k] * streets[k][j];
                    }
                }
            }
        }

        for (int k = 0; k <= N; ++k)
        {
            if (streets[k][k])
            {
                for (int i = 0; i <= N; ++i)
                {
                    for (int j = 0; j <= N; ++j)
                    {
                        if (streets[i][k] && streets[k][j])
                        {
                            streets[i][j] = -1;
                        }
                    }
                }
            }
        }

        printf("matrix for city %d\n", Case++);
        for (int i = 0; i <= N; ++i)
        {
            for (int j = 0; j <= N; ++j)
            {
                printf("%s%d", (j > 0 ? " " : ""), streets[i][j]);
            }
            printf("\n");
        }
    }
    return 0;
}


