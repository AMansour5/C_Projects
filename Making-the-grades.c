#include <stdio.h>
#include <math.h>

int main(void)
{
    // Read the number of test cases
    int n;
    scanf("%d", &n);

    // Print header message
    printf("MAKING THE GRADE OUTPUT\n");

    // Process each test case
    while (n--)
    {
        // Read number of people and tests
        int people;
        int testsNumber;
        scanf("%d %d", &people, &testsNumber);

        // Initialize arrays and variables
        double mean = 0.0;
        int bonus[people];
        double avg[people];
        int absences[people];
        int testResult[testsNumber];

        // Process each person
        for (int i = 0; i < people; ++i)
        {
            // Read the test scores
            for (int j = 0; j < testsNumber; ++j)
                scanf("%d", &testResult[j]);

            // Read the bonus points and absences
            scanf("%d %d", &bonus[i], &absences[i]);

            // Sort the test scores in ascending order
            for (int j = 0; j < testsNumber; ++j) {
                for (int k = j + 1; k < testsNumber; ++k) {
                    if (testResult[j] > testResult[k]) {
                        int temp = testResult[j];
                        testResult[j] = testResult[k];
                        testResult[k] = temp;
                    }
                }
            }

            // Calculate the average score
            int s = 0;
            avg[i] = 0;

            if (testsNumber > 2)
                s = 1;

            for (int j = s;j < testsNumber; ++j)
                avg[i] += testResult[j];

            avg[i] /= (testsNumber - s);
            avg[i] = floor(avg[i]);
            mean += avg[i];
        }

        // Calculate the standard deviation
        mean /= people;
        double standardDesviation = 0.0;

        for (int i = 0; i < people; ++i)
            standardDesviation += (avg[i] - mean) * (avg[i] - mean);

        standardDesviation = sqrt(standardDesviation / people);

        // Ensure that the standard deviation is at least 1.0
        if (standardDesviation < 1.0)
            standardDesviation = 1.0;

        // Apply the bonus points
        for (int i = 0; i < people; ++i)
            avg[i] += (bonus[i] / 2) * 3;

        // Calculate the final grade for each person
        int grade[people];

        for (int i = 0; i < people; ++i)
        {
              // Determine the grade based on the average score, mean, and standard deviation
        if (avg[i] >= mean + standardDesviation)
            grade[i] = 0; // Failing grade
        else if (avg[i] >= mean)
            grade[i] = 1; // Passing grade
        else if (avg[i] >= mean - standardDesviation)
            grade[i] = 2; // Average grade
        else
            grade[i] = 3; // Below average grade
    }

    // Adjust the grade based on absences and ensure it is between 0 and 4
    double avgGrade = 0.0;

    for (int i = 0; i < people; ++i)
    {
        if (!absences[i])
            --grade[i]; // Deduct one grade point for each absence
        else
            grade[i] += absences[i] / 4.0; // Add 0.25 grade points for each absence

        // Ensure that the grade is between 0 and 4
        grade[i] = fmin(fmax(grade[i], 0), 4);

        // Convert the grade to a 0-4 scale and invert it for calculating the average grade
        avgGrade += 4 - grade[i];
    }

    // Print the average grade for the test case
    printf("%.1lf\n", avgGrade /people);

}

// Print footer message
printf("END OF OUTPUT\n");

return 0;
}
