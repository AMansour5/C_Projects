#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int counter = 0, x, y;

void solution(int k, int cx, int cy)
{
    if ((x >= cx - k) && (x <= cx + k) && (y >= cy - k) && (y <= cy + k))
        counter++;
    if (k <= 1 || cx > 2048 || cy > 2048 || cx < 0 || cy < 0)
        return;
    solution(k / 2, cx + k, cy + k);
    solution(k / 2, cx - k, cy - k);
    solution(k / 2, cx + k, cy - k);
    solution(k / 2, cx - k, cy + k);
}

int main()
{
    int k, cx = 1024, cy = 1024;
    while (true)
    {
        scanf("%d %d %d", &k, &x, &y);
        if (k == 0 && x == 0 && y == 0)
            break;
        else
            solution(k, cx, cy);
            printf("%3d\n", counter);
    }
    return 0;
}