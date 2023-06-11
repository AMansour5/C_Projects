#include <stdio.h>
#include <math.h>

#define BOARD_SIZE 8

void place_queen(int row, int* board, int first_row, int first_col);
int is_valid_move(int* board, int row, int col);
void print_board(int* board);

int board[BOARD_SIZE], found_solution = 0;

int main()
{
    // Ask the user to enter the placement of the first queen
    int first_row, first_col, input_success = 0;
    do {
        printf("Enter the row and column of the first queen (separated by a space): ");
        input_success = scanf("%d %d", &first_row, &first_col);
    } while (input_success != 2 || first_row > BOARD_SIZE || first_col > BOARD_SIZE);

    place_queen(1, board, first_row, first_col);

    return 0;
}

void place_queen(int row, int* board, int first_row, int first_col)
{
    for (int col = 1; col <= BOARD_SIZE; ++col) {
        int is_valid = 1;
        if (!is_valid_move(board, row, col)) {
            is_valid = 0;
        }
        if (is_valid) {
            board[row] = col;
            if (row == BOARD_SIZE) { // Base case
                if (board[first_row] == first_col && found_solution == 0) { // Check first queen position and terminate after first solution
                    print_board(board);
                    found_solution = 1;
                    return;
                }
            } else {
                place_queen(row + 1, board, first_row, first_col); // Recursive call
            }
        }
    }
}

int is_valid_move(int* board, int row, int col)
{
    for (int i = 1; i <= row - 1; ++i) {
        if (board[i] == col) { // Check vertical axis
            return 0;
        } else if (abs(board[i] - col) == abs(i - row)) { // Check diagonal axis
            return 0;
        }
    }
    return 1;
}

void print_board(int* board)
{
    for (int i = 1; i <= BOARD_SIZE; ++i) {
        for (int j = 1; j <= BOARD_SIZE; ++j) {
            if (board[i] == j) {
                printf("Q ");
            } else {
                printf("- ");
            }
        }
        printf("\n");
    }
    printf("Q represents a queen position.\n");
}
