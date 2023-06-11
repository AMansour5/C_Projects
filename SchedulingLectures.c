#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Pair {
    int first;   //First value of the pair
    int second;  //Second value of the pair
};

int num_topics, available_time, dissatisfaction_coefficient, topic_time;
int* topic_times;
struct Pair* memoization_table;

struct Pair solve(int idx) {
    //If all topics are covered, return a pair of {0,0} representing no lectures and no dissatisfaction
    if(idx == num_topics) return (struct Pair){0,0};
    //If the subproblem has been solved before, return the value from the memoization table
    if(memoization_table[idx].first != -1) return memoization_table[idx];
    //Set the minimum number of lectures and minimum dissatisfaction to their maximum possible values 
    int min_lectures = INT_MAX;
    int min_dissatisfaction = INT_MAX;
    int available_time_left = available_time;
    //Iterate over the remaining topics
    for(int i=idx;i<num_topics;i++){
        //Subtract the time required for the current topic from the available time
        available_time_left -= topic_times[i];
        //If there is no time left, break out of the loop
        if(available_time_left < 0) break;
        int di = 0;
        //If all available time was used for the current topic, dissatisfaction is 0
        if(available_time_left == 0) di = 0;
        //If there is less than or equal to 10 minutes left, dissatisfaction is the negative of the coefficient
        else if(available_time_left <= 10) di = -dissatisfaction_coefficient;
        //Otherwise, calculate dissatisfaction using the formula given in the problem
        else di = (available_time_left - 10) * (available_time_left - 10);

        //Solve the subproblem for the next topic
        struct Pair sub_res = solve(i+1);
        //The number of lectures required is 1 more than the number of lectures required for the subproblem
        int lectures_needed = sub_res.first + 1;
        //Add the dissatisfaction from the subproblem to the current dissatisfaction
        di += sub_res.second;
        //Update the minimum number of lectures and minimum dissatisfaction if necessary
        if(lectures_needed < min_lectures) {
            min_lectures = lectures_needed;
            min_dissatisfaction = di;
        } else if(min_lectures == lectures_needed) {
            min_dissatisfaction = (di < min_dissatisfaction) ? di : min_dissatisfaction;
        }
    }
    //Store the result in the memoization table and return it
    return memoization_table[idx] = (struct Pair){min_lectures, min_dissatisfaction};
}

int main() {
    int case_num = 1;
    while(scanf("%d",&num_topics),num_topics){
        //Print a blank line between test cases
        if(case_num > 1) printf("\n");
        scanf("%d %d",&available_time,&dissatisfaction_coefficient);
        memoization_table = (struct Pair*) malloc(num_topics * sizeof(struct Pair));
        for (int i = 0; i < num_topics; i++) {
            memoization_table[i].first = -1;
            memoization_table[i].second = -1;
        }
        topic_times = (int*) malloc(num_topics * sizeof(int));
        for(int i=0;i<num_topics;i++){
            scanf("%d",&topic_time);
            topic_times[i] = topic_time;
        }
        //Solve the problem for the first topic
        struct Pair result = solve(0);
        printf("Case %d:\n",case_num++);
        printf("Minimum number of lectures: %d\n", result.first);
        printf("Total dissatisfaction index: %d\n", result.second);
        //Free the dynamically allocated memory
        free(topic_times);
        free(memoization_table);
    }
    return 0;
}