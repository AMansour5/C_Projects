// This program validates ISBN-10 numbers entered via standard input.
// It removes hyphens from input, checks length, and computes check digit.
// It outputs whether input is correct or incorrect.

#include <stdio.h>
#include <string.h>

int main() {
    char line[81];
    while (fgets(line, 81, stdin) != NULL) {
        // Remove hyphens from the input
        char isbn[11];
        int n = 0;
        for (int i = 0; line[i] != '\0'; i++) {
            if (line[i] >= '0' && line[i] <= '9') {
                isbn[n++] = line[i];
            } else if (line[i] == 'X') {
                isbn[n++] = 'X';
            }
        }
        isbn[n] = '\0';

        // Check if the input has the right length
        if (n != 10) {
            printf("%s is incorrect.\n", line);
            continue;
        }

        // Compute s1 and s2
        int s1 = 0, s2 = 0;
        for (int i = 0; i < 10; i++) {
            int digit;
            if (isbn[i] == 'X') {
                digit = 10;
            } else {
                digit = isbn[i] - '0';
            }
            s1 += digit;
            s2 += s1;
        }

        // Check if s2 is divisible by 11
        if (s2 % 11 == 0) {
            printf("%s is correct.\n", line);
        } else {
            printf("%s is incorrect.\n", line);
        }
    }
    return 0;
}
