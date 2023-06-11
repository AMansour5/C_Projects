#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void KWIC_indix(char *titles[200], char *words_ignore[50], int num_ignore, int num_titles);
void upper(char *word);
void lower(char *word);

int main()
{
    char *titles[200];
    char *words_ignore[50];
    char scan_words[50];
    char scan_titles[200];
    int num_ignore = 0, num_titles = 0;

    printf("Enter words to ignore:\n");

    // Input the words to ignore
    for (num_ignore = 0; num_ignore < 50; num_ignore++)
    {
        words_ignore[num_ignore] = (char *)malloc(50 * sizeof(char));
        scanf("%s", scan_words);
        // Check for termination condition
        if (strcmp(scan_words, "::") != 0)
        {
            strcpy(words_ignore[num_ignore], scan_words);
        }
        else
        {
            break;
        }
    }
    printf("Enter the titles:\n");
    // Input the titles
    for (num_titles = 0; num_titles < 200; num_titles++)
    {
        titles[num_titles] = (char *)malloc(200 * sizeof(char));
        fgets(scan_titles, sizeof(scan_titles), stdin);
        // Check for termination condition
        if (strcmp(scan_titles, "stop\n") != 0)
        {
            strcpy(titles[num_titles], scan_titles);
        }
        else
        {
            break;
        }
    }
    KWIC_indix(titles, words_ignore, num_ignore, num_titles);
    return 0;
}

// Function to perform Keyword in Context (KWIC) indexing
void KWIC_indix(char *titles[200], char *words_ignore[50], int num_ignore, int num_titles)
{
    char *words_separate[200];
    int num_words_titles = 0;
    // Process each title
    for (int h = 0; h < num_titles; h++)
    {
        char *token = strtok(titles[h], " \n"); // Tokenize the title
        // Separate words and convert to lowercase
        while (token != NULL)
        {
            words_separate[num_words_titles] = token;
            lower(words_separate[num_words_titles]);
            num_words_titles++;
            token = strtok(NULL, " \n");
        }
        // Perform KWIC indexing
        for (int k = 0; k < num_words_titles; k++)
        {
            int ignore_match = 0;
            // Check if the word matches any ignored words
            for (int i = 0; i < num_ignore; i++)
            {
                if (strcmp(words_separate[k], words_ignore[i]) == 0)
                {
                    ignore_match = 1;
                    break;
                }
            }
            if (!ignore_match)
            {
                // Convert the word to uppercase for indexing
                upper(words_separate[k]);
                // Print the KWIC index
                for (int j = 0; j < num_words_titles; j++)
                {
                    printf("%s ", words_separate[j]);
                }
                printf("\n");
                // Convert the word back to lowercase for further processing
                lower(words_separate[k]);
            }
        }
        num_words_titles = 0; // Reset the word count for the next title
    }
}
// Function to convert word to uppercase
void upper(char *word)
{
    int word_len = strlen(word);

    for (int a = 0; a < word_len; a++)
    {
        word[a] = toupper(word[a]);
    }
}
// Function to convert word to lowercase
void lower(char *word)
{
    int word_len = strlen(word);

    for (int a = 0; a < word_len; a++)
    {
        word[a] = tolower(word[a]);
    }
}
