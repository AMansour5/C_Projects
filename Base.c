// This program takes two numbers in different bases and finds the base in which they are equal.
// It uses two helper functions to_base_10  to convert the numbers to base 10 and max_digit find the maximum digit 

#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Convert a number from base 'base' to base 10.
int to_base_10(char* num, int base) {
    int result = 0;
    int len = strlen(num);
    for (int i = 0; i < len; i++) {
        int digit;
        if (isdigit(num[i])) {
            digit = num[i] - '0';
        } else {
            digit = num[i] - 'A' + 10;
        }
        result = result * base + digit;
    }
    return result;
}

// Find the maximum digit in a number.
int max_digit(char* num) {
    int max = 0;
    int len = strlen(num);
    for (int i = 0; i < len; i++) {
        int digit;
        if (isdigit(num[i])) {
            digit = num[i] - '0';
        } else {
            digit = num[i] - 'A' + 10;
        }
        if (digit > max) {
            max = digit;
        }
    }
    return max;
}

// Main function
int main() {
    char x[100], y[100];
    // Loop through input pairs until end of input
    while (scanf("%s %s", x, y) == 2) {
        int max_x = max_digit(x);
        int max_y = max_digit(y);
        int found = 0;
        // Loop through possible bases for X
        for (int base_x = max_x + 1; base_x <= 36; base_x++) {
            // Loop through possible bases for Y
            for (int base_y = max_y + 1; base_y <= 36; base_y++) {
                int x_base_10 = to_base_10(x, base_x);
                int y_base_10 = to_base_10(y, base_y);
                // If the numbers are equal in base 10, print the result and break out of the loops
                if (x_base_10 == y_base_10) {
                    printf("%s (base %d) = %s (base %d)\n", x, base_x, y, base_y);
                    found = 1;
                    break;
                }
            }
            if (found) {
                break;
            }
        }
        // If the numbers are not equal in any base, print the result
        if (!found) {
            printf("%s is not equal to %s in any base 2..36\n", x, y);
        }
    }
    return 0;
}