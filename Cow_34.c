#include <stdio.h>
#include <math.h>
#define pi 3.14159

int main() {
    int T; // the number of test cases
    double R, P, L, A,L2; //R=Raduis,P=Percentage of grass eated,L=Length of the rope,A=Area of the grass,L2=the length of the rope squared

    scanf("%d\n", &T);
     printf("\n");
    for(int i = 1; i <= T; i++) {
       
        scanf("%lf %lf", &R, &P);
        A= pi*R*R;
        L2=A*P/pi;
        // calculate the length of the rope
        L = sqrt(L2);

        // output the result
        printf("R = %.2f,", R);
        printf("P = %.2f,", P);
        printf("Rope = %.2f", L);
        printf("\n"); // print a blank line between the outputs of two consecutive cases
    }

    return 0;
}