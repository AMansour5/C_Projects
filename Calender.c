#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 1024

// Arrays to store the number of days in each month
int aDays[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};
int aLeapDays[] = {0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366};

// Struct to store information about a single event
typedef struct Event {
    int y, m, d, p, in;
    char title[MAX_LINE_LENGTH];
} Event;

// Function to determine if a given year is a leap year
int isLeapYear(int y, int old) {
    if (old) {
        return y % 4 == 0;
    }
    return (y % 4 == 0 && y % 100 != 0) || y % 400 == 0;
}

// Function to convert a date to the number of days since the start of the year
int toDays(int y, int m, int d, int old) {
    y--;
    int days = y * 365 + y / 4 +(old ? 0 : (y / 400 - y/100));
    days += m > 2 ? isLeapYear(y+1, old) : 0;
    return days + aDays[m - 1] + d - 1- (old * 2);
}

// Comparison function to sort events by date and then by input order
int orderCmp(const void* a, const void* b) {
    Event* eventA = (Event*)a;
    Event* eventB = (Event*)b;
    if (toDays(eventA->y, eventA->m, eventA->d, 0) != toDays(eventB->y, eventB->m, eventB->d, 0)) {
        return toDays(eventA->y, eventA->m, eventA->d, 0) - toDays(eventB->y, eventB->m, eventB->d, 0);
    }
    return eventA->in - eventB->in;
}

int main() {
    char line[MAX_LINE_LENGTH];
    int year, d, m, y, p, cases = 0, in = 0;
    Event events[MAX_LINE_LENGTH];

    // Read in the first line of input to get the starting year
    gets(line);
    sscanf(line, "%d", &year), y = year;

    while (gets(line) && strcmp(line, "#")) {
Continuation:

        // If the line starts with 'A', it is an event entry
        if (line[0] == 'A') {
            sscanf(line+1, "%d %d %d", &d, &m, &p);
            in++;
            int j = 1;
            for(int i = 0; i < 3; i++) {
                // Skip the day, month, and priority fields
                while(isspace(line[j]))
                    j++;
                while(isdigit(line[j]))
                    j++;
           }
            while(isspace(line[j])) {
                j++;
            }
            // Create a new Event struct and store it in the events array
            Event e;
            e.y = y;
            e.m = m;
            e.d = d;
            e.p = p;
            e.in = in;
            strcpy(e.title, line + j);
            events[in - 1] = e;
            // Create a copy of the event for the next year if it is not a leap year
            e.y++;
            events[in] = e;
        } else {
            sscanf(line+1, "%d %d", &d, &m);
            // If this is not the first set of events, print a newline to separate output
            if(cases++) {
                puts("");
            }
            // Print the current date
            printf("Today is:%3d%3d\n", d, m);

            // Sort the events array by date and input order
            qsort(events, in, sizeof(Event), orderCmp);

            // Loop over each event and print it if it occurs today
            for(int i = 0; i < in; i++) {
                if(toDays(year, m, d, 0) >= toDays(events[i].y, events[i].m, events[i].d, 0) - events[i].p &&
                    toDays(year, m, d, 0) == toDays(events[i].y, events[i].m, events[i].d, 0)) {
                    printf("%3d%3d *TODAY* %s\n", d, m, events[i].title);
                }
            }

            // Sort the events array again by date and input order
            qsort(events, in, sizeof(Event), orderCmp);

            // Loop over each event and print it if it occurs in the future
            for(int i = 0; i < in; i++) {
                if(toDays(year, m, d, 0) >= toDays(events[i].y, events[i].m, events[i].d, 0) - events[i].p &&
                    toDays(year, m, d, 0) < toDays(events[i].y, events[i].m, events[i].d, 0)) {
                    // Determine how many stars to print basedon the number of days until the event
                    int starsCount = toDays(year, m, d, 0) - toDays(events[i].y, events[i].m, events[i].d, 0) + events[i].p + 1;
                    char stars[MAX_LINE_LENGTH];
                    memset(stars, '*', starsCount);
                    stars[starsCount] = '\0';
                    printf("%3d%3d %-7s %s\n", events[i].d, events[i].m, stars, events[i].title);
                }
            }
        }
    }

    // Return 0 to indicate successful termination of the program
    return 0;
}