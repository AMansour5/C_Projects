#include <stdio.h>
#include <math.h>

// This function calculates the equation of the circle given three points
void circle_equation(double ax, double ay, double bx, double by, double cx, double cy) {
    double a = bx - ax, b = by - ay, c = cx - ax, d = cy - ay;
    double e = a * (ax + bx) + b * (ay + by);
    double f = c * (ax + cx) + d * (ay + cy);
    double g = 2 * (a * (cy - by) - b * (cx - bx));
    double h, k, r;

    // Calculate center and radius of circle
    if (g == 0) {
        h = k = r = INFINITY;
    } else {
        h = (d * e - b * f) / g;
        k = (a * f - c * e) / g;
        r = sqrt(pow(ax - h, 2) + pow(ay - k, 2));
    }

    // Print circle equation in standard form
    if (h == INFINITY) {
        printf("x^2 + y^2 = infinity\n");
    } else {
        printf("(x %c %.3lf)^2 + (y %c %.3lf)^2 = %.3lf^2\n",
               (h < 0) ? '+' : '-', fabs(h), (k < 0) ? '+' : '-', fabs(k), r);
               printf("\n");
                    double m = 0.00;
    printf("x^2 + y^2 - %.3lf x  %.3lf y  %.3lf = %.3lf ",2*h , 2*k , pow(h,2) + pow(k,2)- pow(r,2) , m );
    }
}

int main() {
    double ax, ay, bx, by, cx, cy;

    // Read input points until end of file
    printf("Enter the coordinates of the first point (ax ay): ");
    scanf("%lf %lf", &ax, &ay);
    printf("Enter the coordinates of the second point (bx by): ");
    scanf("%lf %lf", &bx, &by);
    printf("Enter the coordinates of the third point (cx cy): ");
    scanf("%lf %lf", &cx, &cy);
        circle_equation(ax, ay, bx, by, cx, cy);
        printf("\n");

    return 0;
}
