
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#define BEEP_INTERVAL 5 // in seconds

int main() {
    int l1, l2, initial_level;
    float fill_rate, consumption_rate;

    // get user input for sensor heights and initial water level
    printf("Enter L1 sensor height (percentage of highest possible water level)[0-100]: ");
    scanf("%d", &l1);
    printf("Enter L2 sensor height (percentage of lowest possible water level)[0-100]: ");
    scanf("%d", &l2);
    if(l1<=l2) //Check that sensors are not switched
    {
        printf("Error: Highest possible water level needs to be higher than the lowest");
        exit(1);
    }
    printf("Enter initial water level (percentage of initial water level)[0-100]: ");
    scanf("%d", &initial_level);
    if(l1<0||l2<0||initial_level<0 || l1>100||l2>100||initial_level>100) //Check that percentage [0-100]
    {
        printf("Error: Water level should be between 0 - 100");
        exit(2);
    }
    // get user input for scaling factor and rates
    printf("Enter scaling factor for water filling\nEnter fill rate (in percentage per simulation step): ");
    scanf("%f", &fill_rate);
    printf("Enter consumption rate (in percentage per simulation step): ");
    scanf("%f", &consumption_rate);

    if(fill_rate<consumption_rate) //Check fill rate > consumption
    {
        printf("Error: Fill rate needs to be higher than the Consumption rate");
        exit(3);
    }

    // calculate sensor positions based on user input
    int max_level = 100; // highest possible water level
    int l1_pos = (max_level * l1) / 100;
    int l2_pos = (max_level * l2) / 100;

    // set initial water level
    float current_level = (max_level * initial_level) / 100;

    // initialize motor status and beep interval
    bool motor_on = false;
    int beep_countdown = BEEP_INTERVAL;

    // run simulation
    while (true) {
        // check if motor should be turned on
        if (!motor_on && current_level <= l2_pos) {
            motor_on = true;
            printf("Motor ON\n");
        }

        // check if motor should be turned off
        if (motor_on && current_level >= l1_pos) {
            motor_on = false;
            printf("Motor OFF\n");
        }

        // update water level based on motor or consumption rate
        if (motor_on) {
            current_level += (fill_rate * max_level - consumption_rate * max_level) / 100;
        } else {
            current_level -= (consumption_rate * max_level) / 100;
        }

        // check if water level has gone below minimum level (To avoid negative values)
        if (current_level < 0) {
            current_level = 0;
        }


     //  Add the beep functionality and print the current water level and motor status during each simulaion step:
        // generate beep at BEEP_INTERVAL interval
        if (--beep_countdown == 0) {
            printf("\a"); // ASCII bell character
            beep_countdown = BEEP_INTERVAL;
        }

        // print current water level and motor status
        printf("Water level: %.2f%%\tMotor status: %s\n", current_level, motor_on ? "ON" : "OFF");

        // wait for a short period to simulate simulation step
        sleep(1);
    }

    return 0;
}
