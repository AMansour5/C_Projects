#include <stdio.h>
#include <math.h>

int main()
{
    int init_height, num_workers;

    while (scanf("%d %d", &init_height, &num_workers) == 2 && (init_height != 0 || num_workers != 0)) // Check input
    {
        for (int i = 1; i < init_height - 1; i++)
        {
            // Loop through all possible numbers of cats in a hat

            int current_height = init_height, tot_height = init_height;
            int level = 1, level_cats = 1, num_not_working = 1;

            while (current_height % (i + 1) == 0)
            {
                // Loop through all levels of cats

                current_height /= (i + 1);
                level_cats = pow(i, level);
                tot_height += current_height * level_cats;
                num_not_working += level_cats;

                if (current_height == 1 && level_cats == num_workers)
                {
                    num_not_working -= num_workers;
                    printf("%d %d\n", num_not_working, tot_height);
                    // Print the result if we have found a valid solution
                }

                level++; // Goes to next level
            }
        }
    }
    return 0;
}