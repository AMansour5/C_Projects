#include <stdio.h>
#include <string.h>

struct Dice {
    char p[6];
};

int cmp(struct Dice x, struct Dice y) {
    static int i;
    for(i = 0; i < 6; i++)
        if(x.p[i] != y.p[i])
            return x.p[i] - y.p[i];
    return 0;
}

struct Dice MinExp(struct Dice x) {
    struct Dice y = x;
    int i, j, t;
    for(i = 0; i < 4; i++) { //x rotate
        for(j = 0; j < 4; j++) { //y rotate
            t = x.p[2], x.p[2] = x.p[0], x.p[0] = x.p[3];
            x.p[3] = x.p[5], x.p[5] = t;
            // Compare y and x, and update y if x is smaller
            if(cmp(y, x) > 0)   y = x;
        }
        // Rotate x four times along its z-axis
        for(j = 0; j < 4; j++) { //z rotate
            t = x.p[0], x.p[0] = x.p[1], x.p[1] = x.p[5];
            x.p[5] = x.p[4], x.p[4]  = t;
            // Compare y and x, and update y if x is smaller
            if(cmp(y, x) > 0)   y = x;
        }
        // Swap two elements in x and rotate it once along its y-axis
        t = x.p[1], x.p[1] = x.p[3], x.p[3] = x.p[4];
        x.p[4] = x.p[2], x.p[2] = t;
        // Compare y and x, and update y if x is smaller
            if(cmp(y, x) > 0)   y = x;
    }
    return y;
}

int main() {
    char s[50], i;
    struct Dice a, b;
    while(gets(s)) {
        for(i = 0; i < 6; i++)
            a.p[i] = s[i], b.p[i] = s[i+6];
        a = MinExp(a);
        b = MinExp(b);
        if(!memcmp(a.p, b.p, 6))
            puts("TRUE");
        else
            puts("FALSE");
    }
    return 0;
}
