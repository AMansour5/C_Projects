#include <stdio.h> 
#include <math.h> s

#define eps 1e-8 // Define a small value for precision

int main() {
    int testcase; // Declare a variable to hold the number of testcases
    double R, P; // Declare variables to hold the radius and length of rope
    const double pi = 3.14159265358979323846; 
    scanf("%d", &testcase); 

    while (testcase--) { 
        scanf("%lf %lf", &R, &P); 
        double l = 0, r = pi, mid, ret = 0; // Initialize variables to hold left, right, middle points and rope length
        double A = R * R * pi; // Calculate the area of the circle

        // Perform binary search to find the angle at which the rope touches the circle
        while (fabs(l - r) > eps) { 
            mid = (l + r)/2; // Calculate the middle point
            ret = hypot(R * cos(mid) - R, R * sin(mid)); // Calculate the length of rope from the center to the point of contact
            double theta = (pi - mid)/2; // Calculate the angle between the center, point of contact and x-axis
            double area = (ret * ret * theta/2 + (R * R * mid/2 - R * R * sin(mid)/2))*2; // Calculate the area of the segment of the circle formed by the rope
            if (area < A * P) // If the area of the segment is less than the required area
                l = mid; // Move the left point to the middle
            else
                r = mid; // Otherwise move the right point to the middle
        }
        printf("R = %.0lf, P = %.2lf, Rope = %.2lf\n", R, P, ret); 
        if(testcase)
            puts(""); 
    }
    return 0; 
}
