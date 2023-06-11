#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int counter = 0, x, y;

// Recursive function to count points within a square
void solution(int k, int center_x, int center_y)
{
    // Check if the point (x, y) is within the square defined by center (center_x, center_y) and side length k
    if ((x >= center_x - k) && (x <= center_x + k) && (y >= center_y - k) && (y <= center_y + k))
        counter++;

    // Base case: If the side length is less than or equal to 1, or the center (center_x, center_y) is out of bounds,
    // return without further recursion
    if (k <= 1 || center_x > 2048 || center_y > 2048 || center_x < 0 || center_y < 0)
        return;

    // Recursively check the four quadrants formed by dividing the square into halves
    solution(k / 2, center_x + k, center_y + k); // Top-right quadrant
    solution(k / 2, center_x - k, center_y - k); // Bottom-left quadrant
    solution(k / 2, center_x + k, center_y - k); // Top-left quadrant
    solution(k / 2, center_x - k, center_y + k); // Bottom-right quadrant
}

int main()
{
    FILE *input;
    int k, center_x = 1024, center_y = 1024;
    input = fopen("square.txt", "r");
    if (input != NULL)
    {
        while (true)
        {
            fscanf(input, "%d %d %d", &k, &x, &y);
            if (k == 0 && x == 0 && y == 0)
                break;
            else
                solution(k, center_x, center_y);
            printf("%3d\n", counter);
        }
    }
    else
    {
        printf("Not able to open the file.\n");
    }
    fclose(input);
    return 0;
}
