#include <stdio.h>
#include <string.h>

void ON(float set_temp, float current_temp);
void OFF(float set_temp, float current_temp);

int main(void)
{
    char status[50];
    float set_temp, current_temp;

    printf("Enter the set temperature and the door status = ");
    scanf("%f %s", &set_temp, status);
    printf("Enter the current temperature = ");
    scanf("%f", &current_temp);
    // Check door status and call the appropriate function
    if (strcmp(status, "closed") == 0)
        ON(set_temp, current_temp);
    return 0;
}

// Function to turn ON the oven and increase temperature
void ON(float set_temp, float current_temp)
{
    // Calculate the highest temperature limit as 10% above the set temperature
    float highest_limit = set_temp * 1.10;
    float increment = 0.001;
    // Increase temperature until the current temperature reaches the highest limit
    while (current_temp < highest_limit)
    {
        current_temp += increment;
        printf("OVEN ON  %f\n", current_temp);
    }
    // Call the OFF function to turn OFF the oven
    OFF(set_temp, current_temp);
}
// Function to turn OFF the oven and decrease temperature
void OFF(float set_temp, float current_temp)
{
    // Calculate the lowest temperature limit as 10% below the set temperature
    float lowest_limit = set_temp * 0.9;
    float decrement = 0.0001;
    // Decrease temperature until the current temperature reaches the lowest limit
    while (current_temp > lowest_limit)
    {
        current_temp -= decrement;
        printf("OVEN OFF  %f\n", current_temp);
    }
    // Call the ON function to turn ON the oven again
    ON(set_temp, current_temp);
}
