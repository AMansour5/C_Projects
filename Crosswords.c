#include <stdio.h>
#define MAX_ROWS 10
#define MAX_COLS 10

int main()
{
    int rowCount, colCount, row, col, puzzleCount = 0;

    // Read in the crossword dimensions and layout
    while (scanf("%d", &rowCount) && rowCount != 0)
    {
        scanf("%d", &colCount);
        char crossword[MAX_ROWS][MAX_COLS];
        for (row = 0; row < rowCount; row++)
        {
            scanf("%s", crossword[row]);
        }

        // Print the puzzle number
        if (puzzleCount > 0)
        {
            puts("");
        }
        printf("puzzle #%d:\n", ++puzzleCount);

        // Find the numbering for each word
        int wordNumber[MAX_ROWS][MAX_COLS] = {}, currentNumber = 0;
        for (row = 0; row < rowCount; row++)
        {
            for (col = 0; col < colCount; col++)
            {
                if (row == 0 || crossword[row - 1][col] == '*' || col == 0 || crossword[row][col - 1] == '*')
                {
                    if (crossword[row][col] != '*')
                    {
                        wordNumber[row][col] = ++currentNumber;
                    }
                }
            }
        }

        // Print the across words
        puts("Across");
        for (row = 0; row < rowCount; row++)
        {
            int inWord = 0;
            for (col = 0; col < colCount; col++)
            {
                if (crossword[row][col] != '*')
                {
                    // Start of a new word
                    if (!inWord)
                    {
                        printf("%2d.", wordNumber[row][col]);
                        inWord = 1;
                    }
                    putchar(crossword[row][col]);
                }
                else
                {
                    // End of a word
                    if (inWord)
                    {
                        putchar('\n');
                        inWord = 0;
                    }
                }
            }
            // End of a word at the end of the row
            if (inWord)
            {
                putchar('\n');
            }
        }

        // Print the down words
        puts("Down");
        for (int num = 1; num <= currentNumber; num++)
        {
            for (row = 0; row < rowCount; row++)
            {
                for (col = 0; col < colCount; col++)
                {
                    if (wordNumber[row][col] == num && (row == 0 || crossword[row - 1][col] == '*'))
                    {
                        printf("%2d.", num);
                        int tempRow = row;
                        while (tempRow < rowCount && crossword[tempRow][col] != '*')
                        {
                            putchar(crossword[tempRow][col]);
                            tempRow++;
                        }
                        putchar('\n');
                    }
                }
            }
        }
    }
    return 0;
}
