#include <stdio.h>
#include <math.h>

// Define the function f(x) that we want to find the root of
double f(double x) {
    return pow(x, 3) + 4.5 * pow(x, 2) - 0.19 * x - 0.14;
}

// Define the bisection method to find the root of the function f(x) within a given interval [a, b]
double bisection(double a, double b, int n) {
    // Calculate the midpoint of the interval
    double m = (a + b) / 2;
    // Calculate the value of the function at the midpoint
    double fm = f(m);
    // Check if the function value at the midpoint is zero or if we have reached the maximum number of iterations
    if (fm == 0 || n == 0) {
        // If so, return the midpoint as the approximate root
        return m;
    } else if (f(a) * fm < 0) {
        // If the sign of the function value at the midpoint is opposite to that at the left endpoint,
        // then the root lies in the left half of the interval
        return bisection(a, m, n - 1);
    } else {
        // Otherwise, the root lies in the right half of the interval
        return bisection(m, b, n - 1);
    }
}

// Define the main function
int main() {
    // Define the interval [a, b] and the maximum number of iterations n
    double a = 0, b = 1;
    int n = 30;
    // Find the approximate root of the function f(x) within the interval [a, b] using the bisection method
    double root = bisection(a, b, n);
    // Print the approximate root
    printf("Approximate root: %f\n", root);
    // Return 0 to indicate successful execution of the program
    return 0;
}
