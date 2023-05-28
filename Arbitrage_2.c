#include <stdio.h>
#include <stdbool.h>

#define MAX_N 20
#define EPSILON 1e-9

bool hasArbitrage(int n, double table[MAX_N][MAX_N]) {
    double dp[MAX_N][MAX_N];
    
    // Initialize the base case
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                dp[i][j] = 1.0;
            } else {
                dp[i][j] = 0.0;
            }
        }
    }
    
    // Dynamic programming
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dp[i][k] * table[k][j] > dp[i][j]) {
                    dp[i][j] = dp[i][k] * table[k][j];
                }
            }
        }
    }
    
    // Check for arbitrage
    for (int i = 0; i < n; i++) {
        if (dp[i][i] > 1.0 + EPSILON) {
            return true;
        }
    }
    
    return false;
}

int main() {
    int n;
    
    while (scanf("%d", &n) == 1) {
        double table[MAX_N][MAX_N];
        
        // Read the conversion table
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) {
                    table[i][j] = 1.0;
                } else {
                    scanf("%lf", &table[i][j]);
                }
            }
        }
        
        // Check if arbitrage exists
        if (hasArbitrage(n, table)) {
            printf("Arbitrage sequence exists\n");
        } else {_
            printf("No arbitrage sequence exists\n");
        }
    }
    
     return 0;
}