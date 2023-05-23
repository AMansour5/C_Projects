#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void upper(char *word)
{
    int word_len = strlen(word);

    for (int a = 0; a < word_len; a++)
    {
        word[a] = toupper(word[a]);
    }
}

void lower(char *word)
{
    int word_len = strlen(word);

    for (int a = 0; a < word_len; a++)
    {
        word[a] = tolower(word[a]);
    }
}

void KWIC_indix(char *titles[200], char *words_ignore[50], int num_ignore, int num_titles)
{
    char *words_seperate[200];
    int num_words_titles = 0;
    for (int h = 0; h < num_titles; h++)
    {
        char *token = strtok(titles[h], " \n"); // Tokenize the title
        while (token != NULL)
        {
            words_seperate[num_words_titles] = token;
            lower(words_seperate[num_words_titles]);
            num_words_titles++;
            token = strtok(NULL, " \n");
        }

        for (int k = 0; k < num_words_titles; k++)
        {
            int ignore_match = 0;
            for (int i = 0; i < num_ignore; i++)
            {
                if (strcmp(words_seperate[k], words_ignore[i]) == 0)
                {
                    ignore_match = 1;
                    break;
                }
            }

            if (!ignore_match)
            {
                upper(words_seperate[k]);

                for (int j = 0; j < num_words_titles; j++)
                {
                    printf("%s ", words_seperate[j]);
                }
                printf("\n");

                lower(words_seperate[k]);
            }
        }
        num_words_titles = 0;
    }
}

int main()
{
    char *titles[200];
    char *words_ignore[50];
    char scan_words[50];
    char scan_titles[200];
    int num_ignore = 0, num_titles = 0;
    printf("Enter words to ignore:\n");
    for (num_ignore = 0; num_ignore < 50; num_ignore++)
    {
        words_ignore[num_ignore] = (char *)malloc(50 * sizeof(char));
        scanf("%s", scan_words);
        if (strcmp(scan_words, "::") != 0)
        {
            strcpy(words_ignore[num_ignore], scan_words);
        }
        else
            break;
    }

    printf("Enter the titles:\n");
    for (num_titles = 0; num_titles < 200; num_titles++)
    {
        titles[num_titles] = (char *)malloc(200 * sizeof(char));
        fgets(scan_titles, sizeof(scan_titles), stdin);
        if (strcmp(scan_titles, "stop\n") != 0)
        {
            strcpy(titles[num_titles], scan_titles);
        }
        else
            break;
    }

    KWIC_indix(titles, words_ignore, num_ignore, num_titles);
}