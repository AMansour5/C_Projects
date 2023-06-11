#include <stdio.h>
#include <string.h>
 
#define MAXN 25

// Define a data structure called "TABLE" to store information about blocks
struct TABLE {
    int LEN; // Length of the table
    int WHERE; // Location of the table
    int POS; // Position of block within the table
    int LIST[MAXN]; // List of blocks in the table
} BLOCK[MAXN]; // Declare an array of "MAXN" TABLEs called BLOCK

// Function to move a block and any blocks on top of it to its original position
void move_block(int B){
    int I, A, P, L;
    A = BLOCK[B].WHERE;
    P = BLOCK[B].POS+1;
    L = BLOCK[A].LEN;
    for(I = P; I < L; I++){
        B = BLOCK[A].LIST[I];
        BLOCK[B].WHERE = B;
        BLOCK[B].POS = BLOCK[B].LEN;
        BLOCK[B].LIST[BLOCK[B].LEN++] = B;               
    }
    BLOCK[A].LEN = P;
}

// Function to move a block and any blocks on top of it to a new pile
void move(int B1, int B2){
        int I, A, B, P, L, T;
        A = BLOCK[B1].WHERE;
        B = BLOCK[B2].WHERE;
        P = BLOCK[B1].POS;
        L = BLOCK[A].LEN;
        for(I = P; I < L; I++){
                T = BLOCK[A].LIST[I];
                BLOCK[T].WHERE = B;
                BLOCK[T].POS = BLOCK[B].LEN;
                BLOCK[B].LIST[BLOCK[B].LEN++] = T;               
        }
        BLOCK[A].LEN = P;
}

int main(){
    int N, I, A, B;
    char AC[5], WH[5];
    scanf("%d", &N); // Read the number of blocks as input from the user
    for(I = 0; I < N; I++){
        BLOCK[I].LEN = 1;
        BLOCK[I].WHERE = I;
        BLOCK[I].POS = 0;
        BLOCK[I].LIST[0] = I;
    } // Initialize the TABLE data structure for each pile
   
    while(scanf("%s", AC)){
        if(strcmp(AC, "quit") == 0)
            break; // If the user enters "quit" as input, break out of the loop
        scanf("%d%s%d", &A, WH, &B); // Read two block numbers and a command from the user

        if(A < 0 || A >= N || B < 0 || B >= N)
            continue; // If the block numbers are invalid, skip to the next iteration of the loop
        if(BLOCK[A].WHERE ==BLOCK[B].WHERE)
            continue; // If the blocks are already in the same pile, skip to the next iteration of the loop
                   
        if(strcmp(AC, "move") == 0)
            move_block(A); // If the command is "move", move block A and any blocks on top of it to its original position
       
        if(strcmp(WH, "onto") == 0)
            move_block(B); // If the command is "move onto", move block B and any blocks on top of it to its original position
           
        move(A, B); // Move block A and any blocks on top of it to block B's pile               

    }
   
    for(I = 0; I < N; I++){
        printf("%d:", I); // Print the pile number followed by a colon
        for(A = 0; A < BLOCK[I].LEN; A++)
            printf(" %d", BLOCK[I].LIST[A]); // Print the list of blocks in the pile
        printf("\n"); // Move to the next line
    }
   
    return 0;
}
