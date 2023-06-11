#include <stdio.h>
#include <math.h>

int main() {
    int num_vars, num_input_combinations, num_output_combinations, row, col, term;
    printf("Enter the number of inputs of the digital circuit: ");
    scanf("%d", &num_vars);
    num_input_combinations = pow(2, num_vars);
    num_output_combinations = 1;
    // Calculate the number of input and output combinations
    int input_combinations[num_input_combinations][num_vars];
    int output_combinations[num_input_combinations];

    // Read input-output combinations
    for (row = 0; row < num_input_combinations; row++) {
        for (col = 0; col < num_vars; col++) {
            input_combinations[row][col] = (row >> col) & 1;
        }
        printf("Enter the output for input combination ");
        for (col = num_vars - 1; col >= 0; col--) {
            printf("%d", input_combinations[row][col]);
        }
        printf(": ");
        scanf("%d", &output_combinations[row]);
    }

    // Print truth table
    printf("\nTruth table:\n");
    for (row = 0; row < num_input_combinations; row++) {
        for (col = 0; col < num_vars; col++) {
            printf("%d ", input_combinations[row][col]);
        }
        printf("%d\n", output_combinations[row]);
    }

    // Generate Karnaugh map
    printf("\nKarnaugh map:\n");
    int num_rows, num_cols;
    if (num_vars == 1) {
        num_rows = 2;
        num_cols = 1;
    } else if (num_vars == 2) {
        num_rows = 2;
        num_cols = 2;
    } else if (num_vars == 3) {
        num_rows = 2;
        num_cols = 4;
    } else {
        num_rows = pow(2, num_vars / 2);
        num_cols = pow(2, (num_vars + 1) / 2);
    }
    int k_map[num_rows][num_cols];
    for (row = 0; row < num_rows; row++) {
        for (col = 0; col < num_cols; col++) {
            k_map[row][col] = output_combinations[row * num_cols + col];
        }
    }
    for (row = 0; row < num_rows; row++) {
        for (col = 0; col < num_cols; col++) {
            printf("%d ", k_map[row][col]);
        }
        printf("\n");
    }

    // Simplify output equation
    printf("\nSimplified output equation: ");
    int num_terms = 0;
    for (row = 0; row < num_rows; row++) {
        for (col = 0; col < num_cols; col++) {
            if (k_map[row][col] == 1) {
                num_terms++;
            }
        }
    }
    if (num_terms == 0) {
        printf("0");
    } else if (num_terms == num_input_combinations) {
        printf("1");
    } else {
          // Declare 2D array to store terms
        int terms[num_terms][num_vars];
        int count = 0;
           // Populate terms array with corresponding input combinations for each 1 in k_map
        for (row = 0; row < num_rows; row++) {
            for (col = 0; col < num_cols; col++) {
                if (k_map[row][col] == 1) {
                    for (term = 0; term < num_vars; term++) {
                        if (term < (num_vars + 1) / 2) {
                            terms[count][term] = (row >> term) & 1;
                        } else {
                            terms[count][term] = (col << (num_vars / 2)) | ((row >> term) & 1);
                        }
                    }
                    count++;
                }
            }
        }
         // Output simplified equation
        for (row = 0; row < num_terms; row++) {
            printf("(");
            for (col = num_vars - 1; col >= 0; col--) {
                if (terms[row][col] == 0) {
                    printf("A%d'", col);
                } else {
                    printf("A%d", col);
                }
                if (col > 0) {
                    printf("*");
                }
            }
            printf(")");
            if (row < num_terms - 1) {
                printf("+");
            }
        }
    }
    return 0;
}
