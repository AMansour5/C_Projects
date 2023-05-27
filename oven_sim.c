#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void ON(float set_temp, float current_temp);
void OFF(float set_temp, float current_temp);

int main(void)
{
    char status[50];
    float set_temp, current_temp;
    printf("Enter the set tempreature and the door status = ");
    scanf("%f %s", &set_temp, status);
    printf("Enter the current tempreature = ");
    scanf("%f", &current_temp);
    if(strcmp(status, "closed") == 0)
    ON(set_temp, current_temp);
    return 0;
}

void ON(float set_temp, float current_temp)
{
    float highest_limit = set_temp * 1.10;
    float increment = 0.001;
    while (current_temp < highest_limit)
    {
            current_temp += increment;
            printf("OVEN ON  %f\n", current_temp);
    }
    OFF(set_temp, current_temp);
}

void OFF(float set_temp, float current_temp)
{
    float lowest_limit = set_temp * 0.9;
    float decrement = 0.0001;
    while (current_temp > lowest_limit)
    {
            current_temp -= decrement;
            printf("OVEN OFF  %f\n", current_temp);
    }
    ON(set_temp, current_temp);
}

