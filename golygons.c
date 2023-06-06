#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_N 64
#define MAX_M 1024
#define MAX_PATH_LEN 1024
#define MAX_GRID_SIZE 4096
#define BASE 2048

typedef struct
{
    int x, y;
} Point;

int n, m, golygons;
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
char sdir[] = "nsew";
char path[MAX_PATH_LEN];
char g[MAX_GRID_SIZE][MAX_GRID_SIZE] = {};
char g2[MAX_GRID_SIZE][MAX_GRID_SIZE];
char ban[MAX_GRID_SIZE][MAX_GRID_SIZE] = {};
char ways[MAX_M][MAX_PATH_LEN];

void dfs(int x, int y, int dir, int step)
{
    if (abs(x - 0) + abs(y - 0) > (step + n) * (n - step + 1) / 2)
    {
        return;
    }
    if (step == n + 1)
    {
        if (x == 0 && y == 0)
        {
            path[step - 1] = '\0';
            strcpy(ways[golygons], path);
            golygons++;
        }
        return;
    }
    if (dir != 0)
    {
        for (int i = 0; i < 2; i++)
        {
            int tx = x, ty = y, ok = 1;
            for (int j = 0; j < step; j++)
            {
                tx = tx + dx[i], ty = ty + dy[i];
                if (BASE + tx >= 0 && BASE + ty >= 0 && BASE + tx < MAX_GRID_SIZE && BASE + ty < MAX_GRID_SIZE)
                {
                    if (ban[BASE + tx][BASE + ty])
                    {
                        ok = 0;
                        break;
                    }
                }
                else
                {
                    ok = 0;
                    break;
                }
            }
            if (ok && g2[BASE + tx][BASE + ty] == 0)
            {
                g2[BASE + tx][BASE + ty] = 1;
                path[step - 1] = sdir[i];
                dfs(tx, ty, 0, step + 1);
                g2[BASE + tx][BASE + ty] = 0;
            }
        }
    }
    if (dir != 1)
    {
        for (int i = 2; i < 4; i++)
        {
            int tx = x, ty = y, ok = 1;
            for (int j = 0; j < step; j++)
            {
                tx = tx + dx[i], ty = ty + dy[i];
                if (BASE + tx >= 0 && BASE + ty >= 0 && BASE + tx < MAX_GRID_SIZE && BASE + ty < MAX_GRID_SIZE)
                {
                    if (ban[BASE + tx][BASE + ty])
                    {
                        ok = 0;
                        break;
                    }
                }
                else
                {
                    ok = 0;
                    break;
                }
            }
            if (ok && g2[BASE + tx][BASE + ty] == 0)
            {
                g2[BASE + tx][BASE + ty] = 1;
                path[step - 1] = sdir[i];
                dfs(tx, ty, 1, step + 1);
                g2[BASE + tx][BASE + ty] = 0;
            }
        }
    }
}

int main()
{
    int testcase, x[MAX_N], y[MAX_N];
    FILE *golygons_file;
    golygons_file = fopen("golygons.txt", "r");
    if (golygons_file != NULL)
    {
        fscanf(golygons_file, "%d", &testcase);
        while (testcase--)
        {
            fscanf(golygons_file, "%d %d", &n, &m);
            memset(ban, 0, sizeof(ban));
            for (int i = 0; i < m; i++)
            {
                fscanf(golygons_file, "%d %d", &x[i], &y[i]);
                ban[BASE + x[i]][BASE + y[i]] = 1;
                g[BASE + x[i]][BASE + y[i]] = 1;
            }
            golygons = 0;
            dfs(0, 0, -1, 1);
            qsort(ways, golygons, MAX_PATH_LEN, (int (*)(const void *, const void *))strcmp);
            for (int i = 0; i < golygons; i++)
                puts(ways[i]);
            printf("Found %d golygon(s).\n\n", golygons);
            for (int i = 0; i < m; i++)
                g[BASE + x[i]][BASE + y[i]] = 0;
        }
    }
    else
    {
        printf("Not able to open the file.\n");
    }
    fclose(golygons_file);
    return 0;
}
