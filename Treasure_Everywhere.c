#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#define PI 3.14159265

void Directions(char *movements[200], int counter, int j);
void calc(float x, float y, int counter);
char *RemoveDigits(char *input);

int main(void)
{
    FILE *input;
    char read[200];
    char *movements[200];
    int i, j = 0, count = 0;
    input = fopen("inputs.txt", "r");
    if (input != NULL)
    {
        while (fgets(read, 200, input))
        {
            movements[j] = (char *)malloc(200 * sizeof(char *));

            if (strcmp(read, "END\n") != 0)
            {
                int size = strlen(read) - 2;

                if (strcmp(&read[size], ".\n") == 0)
                {
                    count++;  // Increment count for each map
                    strcpy(movements[j], read);
                    Directions(movements, count, j + 1);
                    free(*movements);
                    j = 0;  
                }
                else
                {
                    strcpy(movements[j], read);
                    j++;
                }
            }
            else
                break;
        }
    }
    else
    {
        printf("Not able to open the file.\n");
    }
    fclose(input);

    return 0;
}

void Directions(char *movements[200], int counter, int j)
{
    int num;
    float x = 0, y = 0;

    for (int i = 0; i < j; i++)
    {
        num = atoi(movements[i]);  // Convert the numerical part of the movement string to an integer
        RemoveDigits(movements[i]);  // Remove the numerical part from the movement string
        strtok(movements[i], ",\n");  // Tokenize the movement string to extract the direction
        strtok(movements[i], ".\n");  // Tokenize again to remove the period at the end of the string

        // Update the x and y coordinates based on the direction and distance
        if (strcmp(movements[i], "N") == 0)
            y += num;
        else if (strcmp(movements[i], "S") == 0)
            y -= num;
        else if (strcmp(movements[i], "W") == 0)
            x -= num;
        else if (strcmp(movements[i], "E") == 0)
            x += num;
        else if (strcmp(movements[i], "NE") == 0)
        {
            x += cos(PI / 4) * num;  // Calculate the x coordinate using cosine
            y += cos(PI / 4) * num;  // Calculate the y coordinate using cosine
        }
        else if (strcmp(movements[i], "NW") == 0)
        {
            x -= cos(PI / 4) * num;  // Calculate the x coordinate using cosine
            y += cos(PI / 4) * num;  // Calculate the y coordinate using cosine
        }
        else if (strcmp(movements[i], "SE") == 0)
        {
            x += cos(PI / 4) * num;  // Calculate the x coordinate using cosine
            y -= cos(PI / 4) * num;  // Calculate the y coordinate using cosine
        }
        else
        {
            x -= cos(PI / 4) * num;  // Calculate the x coordinate using cosine
            y += cos(PI / 4) * num;  // Calculate the y coordinate using cosine
        }
    }
    calc(x, y, counter);  // Call the calc function to calculate the distance and print the result
}

char *RemoveDigits(char *input)
{
    char *dest = input;
    char *src = input;
    // Iterate through the input string, skipping any digits
    while (*src)
    {
        if (isdigit(*src))
        {
            src++;
            continue;
        }
        *dest++ = *src++;  // Copy non-digit characters to the destination
    }
    *dest = '\0';  // Append null terminator at the end
    return input;
}

void calc(float x, float y, int counter)
{
    float distance;
    distance = (sqrt(pow(x, 2) + pow(y, 2)));  // Calculate the Euclidean distance
    printf("Map #%d\nThe treasure is located at (%.3f,%.3f)\nThe distance to the treasure is %f\n\n", counter, x, y, distance);
}
