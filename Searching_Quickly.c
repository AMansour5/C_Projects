#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    char *titles[200];
    char *words[100];
    char *words_ignore[50];
    char scan_words[50];
    char scan_titles[200];
    int num_errors = 0, i = 0, j, k, h;
    printf("Enter words to ignore:\n");
    for (i = 0; i < 50; i++)
    {
        words_ignore[i] = (char *)malloc(50 * sizeof(char));
        scanf("%s", scan_words);
        if (strcmp(scan_words, "::") != 0)
        {
            strcpy(words_ignore[i], scan_words);
        }
        else
            break;
    }
    for (h = 0; h < i; h++)
        printf("%s\n", words_ignore[h]);

    printf("Enter the titles to ignore:\n");
    for (j = 0; j < 200; j++)
    {
        titles[j] = (char *)malloc(200 * sizeof(char));
        fgets(scan_titles, sizeof(scan_titles), stdin);
        if (strcmp(scan_titles, "stop\n") != 0)
        {
            strcpy(titles[j], scan_titles);
        }
        else
            break;
    }
    for (k = 0; k < j; k++)
        printf("%s", titles[k]);
}