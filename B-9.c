#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Function to print the game board
void printBoard(char board[][3]) {
    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

// Function to check if a player has won
bool checkWin(char board[][3], char player) {
    int i;
    // Check diagonals
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) {
        return true;
    }
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) {
        return true;
    }
    // Check rows
    for (i = 0; i < 3; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) {
            return true;
        }
    }
    // Check columns
    for (i = 0; i < 3; i++) {
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) {
            return true;
        }
    }
    return false;
}

int main() {
    char board[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
    int i, j, k, score1 = 0, score2 = 0, draws = 0, numGames;
    char player1 = 'X', player2 = 'O', currentPlayer;
    bool win, draw;

    printf("Enter the number of games to play: ");
    scanf("%d", &numGames);

    for (k = 0; k < numGames; k++) {
        // Reset board
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 3; j++) {
                board[i][j] = ' ';
            }
        }
        // Reset variables
        win = false;
        draw = false;
        currentPlayer = player1;

        // Play game
        while (!win && !draw) {
            // Print board
            printf("Current board:\n");
            printBoard(board);
            // Get move from player
            int row, col;
            printf("Player %c, enter row and column (1-3): ", currentPlayer);
            scanf("%d %d", &row, &col);
            row--;
            col--;
            // Check if move is valid
            if (row < 0 || row > 2 || col < 0 || col > 2 || board[row][col] != ' ') {
                printf("Invalid move, try again.\n");
                continue;
            }
            // Make move
            board[row][col] = currentPlayer;
            // Check for win
            if (checkWin(board, currentPlayer)) {
                printf("Player %c wins!\n", currentPlayer);
                if (currentPlayer == player1) {
                    score1 += 3;
                } else {
                    score2 += 3;
                }
                win = true;
                break;
            }
            // Check for draw
            draw = true;
            for (i = 0; i < 3; i++) {
                for (j = 0; j < 3; j++) {
                    if (board[i][j] == ' ') {
                        draw = false;
                        break;
                    }
                }
                if (!draw) {
                    break;
                }
            }
            if (draw) {
                printf("Draw!\n");
                draws++;
                score1++;
                score2++;
                break;
            }
            // Switch players
            if (currentPlayer == player1) {
                currentPlayer = player2;
            } else {
                currentPlayer = player1;
            }
        }
        // Print final board
        printf("Final board:\n");
        printBoard(board);
    }
    // Print scores
    printf("Player %c score: %d\n", player1, score1);
    printf("Player %c score: %d\n", player2, score2);
    printf("Draws: %d\n", draws);
    if (score1 > score2) {
        printf("Player %c wins!\n", player1);
    } else if (score2 > score1) {
        printf("Player %c wins!\n", player2);
    } else {
        printf("It's a tie!\n");
    }

    return 0;
}
