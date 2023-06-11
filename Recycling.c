#include <stdio.h>
#include <string.h>

#define MAX_CITIES 100
#define MAX_ALLOCATION_LEN 25

int count, changesCount, indexResult, indexA, indexB, indexC, minChanges;
char line[MAX_ALLOCATION_LEN];
char dataset[MAX_CITIES][5][2];

int recycling() {
    indexResult = 0;
    minChanges = 0xffffff;
    changesCount = 0;

    for (indexA = 0; indexA < count; indexA++) {
        changesCount = 0;
        for (indexB = 0; indexB < count; indexB++) {
            for (indexC = 0; indexC < 5; indexC++) {
                if (strcmp(dataset[indexA][indexC], dataset[indexB][indexC]) != 0)
                    changesCount++;
            }
        }

        if (changesCount < minChanges) {
            minChanges = changesCount;
            indexResult = indexA;
        }
    }

    return indexResult + 1;
}

int main() {
    count = 0;
    int k, i;
    char c;

    while (fgets(line, MAX_ALLOCATION_LEN, stdin)) {
        if (strcmp(line, "#\n") == 0)
            break;

        if (line[0] == 'e') {
            printf("%d\n", recycling());
            count = 0;
        } else {
            for (k = 0; k < 5; k++) {
                c = line[k * 4];
                i = 0;

                if (c == 'r')
                    i = 0;
                else if (c == 'o')
                    i = 1;
                else if (c == 'y')
                    i = 2;
                else if (c == 'g')
                    i = 3;
                else if (c == 'b')
                    i = 4;

                dataset[count][i][0] = line[k * 4 + 2];
                dataset[count][i][1] = '\0';
            }
            count++;
        }
    }

    return 0;
}
