#include <stdio.h>
#define COIN_COUNT 6
const int coins[COIN_COUNT] = {5, 10, 20, 50, 100, 200}; // Available coin values in cents
const int MAX_AMOUNT = 30000;                            // Maximum amount in cents

// Counting the number of ways to make change
// for the given amount using the given coins
int count_ways(int amount, const int *coins, int coin_count)
{
    int ways[amount + 1];
    for (int i = 0; i <= amount; i++)
    {
        ways[i] = 0;
    }
    ways[0] = 1;
    for (int i = 0; i < coin_count; i++)
    {
        for (int j = coins[i]; j <= amount; j++)
        {
            ways[j] += ways[j - coins[i]];
        }
    }
    return ways[amount];
}

int main()
{
    double amount;
    int cents, ways;
    while (scanf("%lf", &amount))
    {
        cents = (int)(amount * 100); // convert amount to cents
        if (cents > MAX_AMOUNT)
        {
            printf("Amount too large: %.2f\n", amount);
            continue;
        }
        ways = count_ways(cents, coins, COIN_COUNT);
        printf("%6.2f%17d\n", amount, ways);
    }
    return 0;
}