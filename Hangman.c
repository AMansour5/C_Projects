/* Dedicated to my love*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NUM_WORDS 10 // Define the number of words to guess
#define MAX_WORD_LEN 20 // Define the maximum length of a word
#define MAX_WRONG_GUESSES 10 // Define the maximum number of wrong guesses allowed

char words[NUM_WORDS][MAX_WORD_LEN+1] = {"apple", "banana", "cherry", "orange", "peach",
                                          "grape", "pear", "kiwi", "mango", "watermelon"}; // Declare an array of words to guess

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

    while (wordIndex < 0 || wordIndex >= NUM_WORDS) { // Ask the user to select a word until a valid word is selected
        printf("Please select a word (1-%d): ", NUM_WORDS);
        scanf("%d", &wordIndex);
        wordIndex--;
    }

    strcpy(word, words[wordIndex]); // Copy the selected word into the "word" variable
    wordLen = strlen(word); // Get the length of the selected word

    for (i = 0; i < wordLen; i++) {
        guessedWord[i] = '.'; // Initialize the guessed word with dots to represent unguessed letters
    }
    guessedWord[wordLen] = '\0';

    while (numWrongGuesses < MAX_WRONG_GUESSES) { // Loop until the maximum number of wrong guesses is reached
        printf("Word: %s\n", guessedWord);
        printf("Wrong guesses: ");

        for (i = 0; i < numWrongGuessesSoFar; i++) {
            printf("%c ", wrongGuesses[i]); // Print the list of wrong guesses so far
        }

        printf("\nGuess a letter: ");
        scanf("%s", guess);

        if (!isalpha(guess[0])) { // Check if input is a letter
            printf("Invalid input. Please enter a letter.\n");
            continue;
        }

        guess[0] = tolower(guess[0]); // Convert the guess to lowercase

        int found = 0;

        for (i = 0; i < wordLen; i++) {
            if (word[i] == guess[0]) { // If the guessed letter is found in the word
                guessedWord[i] = guess[0]; // Update the guessed word with the correct letter
                found = 1;
            }
        }

        if (found) { // If the guess is correct
            printf("Correct!\n");
            if (strcmp(word, guessedWord) == 0) { // If the guessed word matches the actual word
                printf("Congratulations! You guessed the word.\n");
                break;
            }
        } else { // If the guess is incorrect
            printf("Wrong!\n");
            wrongGuesses[numWrongGuessesSoFar] = guess[0]; // Add the guess to the list of wrong guesses
            numWrongGuessesSoFar++;
            numWrongGuesses++;
        }
    }

    if (numWrongGuesses == MAX_WRONG_GUESSES) { // If the maximum number of wrong guesses is reached
        printf("Sorry, you did not guess the word. The word was %s.\n", word); // Print the actual word
    }

    printf("Thanks for playing!\n");

    return 0;
}
   
