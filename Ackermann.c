#include <stdio.h>

// Function to compute the length of the Ackermann sequence starting from n
int ackermann_sequence_length(long long n) {
    long long length = 1; 
    while (n != 1) { // Loop until n becomes 1
        if (n % 2 == 0) { // If n is even
            n = n / 2; // Apply the even case
        } else { // If n is odd
            n = 3 * n + 1; // Apply the odd case
        }
        length += 1;
    }
    return length; // Return the length of the sequence
}

// Function to find the value with the longest Ackermann sequence in the range [L, H]
void longest_sequence(long long  L, long long H, long long *max_value, long long *max_length) {
    *max_length = 0;
    *max_value = L;
    for (long long n = L; n <= H; n++) {
        long long length = ackermann_sequence_length(n); // Compute the length of the sequence for n
        if (length > *max_length) {
            *max_length = length;
            *max_value = n;
        }
    }
}

int main() {
    long long L, H; //L = the lower boundary value in the sequence, H = the upper boundary value in the sequence 
    while (1) { 
        printf("Enter the lower boundary and the higher boundary in the sequence \n");
        scanf("%lld %lld", &L, &H); 
        if (L == 0 && H == 0) { // If input pair is (0, 0)
            break; // Exit loop
        }
        long long V, S; //V = the first value that generates the longest sequence , S = the length of the generated sequence. 
        longest_sequence(L, H, &V, &S); // Find the value with the longest sequence in the range [L, H]
        printf("Between %lld and %lld, %lld generates the longest sequence of %lld values.\n", L, H, V, S); 
    }
    return 0; 
}
