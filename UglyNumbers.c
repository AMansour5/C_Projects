#include <stdio.h>

int is_ugly(int n) {
    while (n % 2 == 0) {
        n /= 2;
    }
    while (n % 3 == 0) {
        n /= 3;
    }
    while (n % 5 == 0) {
        n /= 5;
    }
    return n == 1;
}

int main() {
    int ugly_numbers[1500] = {1};
    int i = 1;
    int num = 2;
    while (i < 1500) {
        if (is_ugly(num)) {
            ugly_numbers[i] = num;
            i++;
        }
        num++;
    }
    printf("The 1500th ugly number is: %d\n", ugly_numbers[1499]);
    return 0;
}
