// This code is written in C programming language
#include <stdio.h>
#include <math.h>

// Define the function f(x) that we want to find the root of
double f(double x) {
    return x*x*x + 4.5*x*x - 0.19*x - 0.14;
}

int main() {
    // Define the initial values of a, b, and m
    double a = 0.0, b = 1.0, m, fm, fa, fb;
    int i;

    // Loop through 30 iterations to find the root of f(x)
    for (i = 1; i <= 30; i++) {
        // Calculate the midpoint m between a and b
        m = (a + b) / 2.0;
        // Calculate the value of f(m)
        fm = f(m);
        // Calculate the value of f(a)
        fa = f(a);
        // Calculate the value of f(b)
        fb = f(b);

        // Print the values of a, b, m, and f(m) for the current iteration
        printf("Iteration %d: a = %lf, b = %lf, m = %lf, f(m) = %lf\n", i, a, b, m, fm);

        // Check if the value of f(m) is close enough to zero to consider it a root
        if (fabs(fm) < 1e-6) {
            // If f(m) is close enough to zero, print the value of m as the root and exit the loop
            printf("Root found at x = %lf\n", m);
            break;
        } else if (fa * fm < 0.0) {
            // If f(a) and f(m) have opposite signs, set b to m
            b = m;
        } else {
            // If f(a) and f(m) have the same sign, set a to m
            a = m;
        }
    }

    // Return 0 to indicate successful completion of the program
    return 0;
}
