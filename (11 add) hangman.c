#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NUM_WORDS 10
#define MAX_WORD_LEN 20
#define MAX_WRONG_GUESSES 10

char words[NUM_WORDS][MAX_WORD_LEN+1] = {"apple", "banana", "cherry", "orange", "peach",
                                          "grape", "pear", "kiwi", "mango", "watermelon"};

int main() {
    int wordIndex = -1;
    char word[MAX_WORD_LEN+1];
    int wordLen;
    char guessedWord[MAX_WORD_LEN+1];
    int numWrongGuesses = 0;
    char wrongGuesses[MAX_WRONG_GUESSES];
    int numWrongGuessesSoFar = 0;
    char guess[2];
    guess[1] = '\0';
    int i, j;

    printf("Welcome to Hang Man!\n");

    while (wordIndex < 0 || wordIndex >= NUM_WORDS) {
        printf("Please select a word (1-%d): ", NUM_WORDS);
        scanf("%d", &wordIndex);
        wordIndex--;
    }

    strcpy(word, words[wordIndex]);
    wordLen = strlen(word);

    for (i = 0; i < wordLen; i++) {
        guessedWord[i] = '.';
    }
    guessedWord[wordLen] = '\0';

    while (numWrongGuesses < MAX_WRONG_GUESSES) {
        printf("Word: %s\n", guessedWord);
        printf("Wrong guesses: ");

        for (i = 0; i < numWrongGuessesSoFar; i++) {
            printf("%c ", wrongGuesses[i]);
        }

        printf("\nGuess a letter: ");
        scanf("%s", guess);

        if (!isalpha(guess[0])) { // check if input is a letter
            printf("Invalid input. Please enter a letter.\n");
            continue;
        }

        guess[0] = tolower(guess[0]); // convert to lowercase

        int found = 0;

        for (i = 0; i < wordLen; i++) {
            if (word[i] == guess[0]) {
                guessedWord[i] = guess[0];
                found = 1;
            }
        }

        if (found) {
            printf("Correct!\n");
            if (strcmp(word, guessedWord) == 0) {
                printf("Congratulations! You guessed the word.\n");
                break;
            }
        } else {
            printf("Wrong!\n");
            wrongGuesses[numWrongGuessesSoFar] = guess[0];
            numWrongGuessesSoFar++;
            numWrongGuesses++;
        }
    }

    if (numWrongGuesses == MAX_WRONG_GUESSES) {
        printf("Sorry, you did not guess the word. The word was %s.\n", word);
    }

    printf("Thanks for playing!\n");

    return 0;
}