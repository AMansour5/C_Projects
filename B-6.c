#include <stdio.h>

#define MAX_SIZE 100

int max(int a, int b) {
    return (a > b) ? a : b;
}

void findMaxPath(int grid[MAX_SIZE][MAX_SIZE], int N, int M) {
    int dp[MAX_SIZE][MAX_SIZE];

    // Initialize the bottom-right corner
    dp[N-1][M-1] = grid[N-1][M-1];

    // Fill the last row
    for (int j = M - 2; j >= 0; j--) {
        dp[N-1][j] = dp[N-1][j+1] + grid[N-1][j];
    }

    // Fill the last column
    for (int i = N - 2; i >= 0; i--) {
        dp[i][M-1] = dp[i+1][M-1] + grid[i][M-1];
    }

    // Fill the remaining cells
    for (int i = N - 2; i >= 0; i--) {
        for (int j = M - 2; j >= 0; j--) {
            dp[i][j] = max(max(dp[i+1][j], dp[i][j+1]), dp[i+1][j+1]) + grid[i][j];
        }
    }

    // Print the maximum gain
    printf("Maximum Gain: %d\n", dp[0][0]);

    // Print the path
    printf("Path: ");
    int i = 0, j = 0;
    while (i < N - 1 || j < M - 1) {
        printf("%c%d ", 'A' + i, j + 1);
        if (i == N - 1)
            j++;
        else if (j == M - 1)
            i++;
        else if (dp[i+1][j] > dp[i][j+1] && dp[i+1][j] > dp[i+1][j+1])
            i++;
        else if (dp[i][j+1] > dp[i+1][j] && dp[i][j+1] > dp[i+1][j+1])
            j++;
        else {
            i++;
            j++;
        }
    }
    printf("%c%d\n", 'A' + i, j + 1);
}

int main() {
    int N, M;
    int grid[MAX_SIZE][MAX_SIZE];

    // Read the dimensions N and M
    printf("Enter the number of rows (N): ");
    scanf("%d", &N);
    printf("Enter the number of columns (M): ");
    scanf("%d", &M);

    // Read the weights of each node
    printf("Enter the weights of each node:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("Node %c%d: ", 'A' + i, j + 1);
            scanf("%d", &grid[i][j]);
        }
    }

    // Find the maximum path and print the result
    findMaxPath(grid, N, M);

    return 0;
}
