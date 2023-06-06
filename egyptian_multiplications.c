#include <stdio.h>
#include <string.h>

char* int2ch(int n) {
    static int i, flag, t;
    static int v[6] = {'|', 'n', '9', '8', 'r'};
    static char r[32] = "";
    flag = 0;
    int idx = 0;
    for(i = 0; i < 6; i++) {
        if(n%10) {
            if(flag)    r[idx++] = ' ';
            t = n%10;
            while(t)    r[idx++] = v[i], t--;
            flag = 1;
        }
        n /= 10;
    }
    r[idx] = '\0';
    return r;
}

int main() {
    int ch2int[127] = {};
    ch2int['|'] = 1;
    ch2int['n'] = 10;
    ch2int['9'] = 100;
    ch2int['8'] = 1000;
    ch2int['r'] = 10000;
    char a[200], b[200];
    int i;
    while(fgets(a, sizeof(a), stdin)) {
        fgets(b, sizeof(b), stdin);
        int na = 0, nb = 0, ans;
        for(i = 0; a[i]; i++)
            na += ch2int[a[i]];
        for(i = 0; b[i]; i++)
            nb += ch2int[b[i]];
        ans = na * nb;
        for(i = 0; (nb>>i) > 0; i++) {
            char line[64];
            char* tmp = int2ch(1<<i);
            strcpy(line, tmp);
            if((nb>>i) & 1)
                strcat(line, " *");
            while(strlen(line) < 34)
                strcat(line, " ");
            strcat(line, int2ch((1<<i) * na));
            printf("%s\n", line);
        }
        printf("The solution is: %s\n", int2ch(ans));
    }
    return 0;
}
