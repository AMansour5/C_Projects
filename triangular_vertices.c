#include <stdio.h>
#include <stdlib.h>

// Define a function to check if a set of points forms a triangle
int is_triangle(int *points) {
    int a = points[0], b = points[1], c = points[2];
    return (b-a == 1 && c-b == 1) || (b-a == 7 && c-b == 1) || (b-a == 8 && c-b == 8);
}

// Define a function to check if a set of points forms a parallelogram
int is_parallelogram(int *points) {
    int a = points[0], b = points[1], c = points[2], d = points[3];
    return (b-a == c-d && c-b == d-a) || (b-a == c-d-4 && c-b == a-d);
}

// Define a function to check if a set of points forms a hexagon
int is_hexagon(int *points) {
    int a = points[0], b = points[1], c = points[2], d = points[3], e = points[4], f = points[5];
   return (b-a == c-b-3 && c-b == d-c && d-c == e-d+5 && e-d == f-e+4 && b-a == 1);
}
int main() {
    int points[6];
    int n;

    // Read input from standard input
    while (scanf("%d", &n) == 1) {
        for (int i = 0; i < n; i++) {
            scanf("%d", &points[i]);
        }

        // Determine the type of figure based on the number of points
        if (n == 3 && is_triangle(points)) {
            printf("%d %d %d are the vertices of a triangle\n", points[0], points[1], points[2]);
        } else if (n == 4 && is_parallelogram(points)) {
            printf("%d %d %d %d are the vertices of a parallelogram\n", points[0], points[1], points[2], points[3]);
        } else if (n == 6 && is_hexagon(points)) {
            printf("%d %d %d %d %d %d are the vertices of a hexagon\n", points[0], points[1], points[2], points[3], points[4], points[5]);
        } else {
            printf("%d", points[0]);
            for (int i = 1; i < n; i++) {
                printf(" %d", points[i]);
            }
            printf(" are not the vertices of an acceptable figure\n");
        }
    }

    return 0;
}