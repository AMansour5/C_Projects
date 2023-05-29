#include <stdio.h>

/**
  Simulates a queue of students waiting to pay a fee.
  The order in which they leave the queue is printed.
 */
int main() {
    int num_students, coins_per_student, i, j, sum;
    int queue[25], order[25];

    // Loop until input of 0 0 is received
    while (1) {
        // Get input
        scanf("%d %d", &num_students, &coins_per_student);

        // Check for exit condition
        if (num_students == 0 && coins_per_student == 0) {
            break;
        }

        // Initialize queue and order arrays
        for (i = 0; i < num_students; i++) {
            queue[i] = i + 1;
            order[i] = 0;
        }

        // Initialize sum and index variables
        sum = 0;
        i = 0;
        j = 0;

        // Loop through the queue until all students have been paid
        while (j < num_students) {
            // Calculate the amount to be paid to the current student
            int amount = (sum + coins_per_student) % (num_students - j);
            if (amount == 0) {
                amount = num_students - j;
            }

            // Update the order array with the current student's position, skipping over students who have already left the queue
            for (i = 0; i < num_students; i++) {
                if (queue[i] != 0) {
                    amount--;
                    if (amount == 0) {
                        order[j] = queue[i];
                        queue[i]= 0;
                        j++;
                        break;
                    }
                }
            }

            // Move coins from the vault to the output store
            sum += coins_per_student;
            while (sum >= num_students) {
                sum -= num_students;
            }
        }

        // Print the order in which the students leave the queue
        for (i = 0; i < num_students; i++) {
            printf("%d ", order[i]);
        }
        printf("\n");
    }

    return 0;
}
