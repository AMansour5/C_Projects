/**
**********************************************************************************************************
* @file         : main.c
* @author       : Moataz Mohamed Khaled El-Walid
* @brief        : 14: City Directions
**********************************************************************************************************
*/

/* *************************************** Includes Section Start **************************************** */
#include <stdio.h>
#include <string.h>
/* *************************************** Includes Section End ****************************************** */

/* *************************************** Global Section Start **************************************** */
const char* dName[] = {"E", "NE", "N", "NW", "W", "SW", "S", "SE"}; //initializing directions (where E is east, S is south etc.)
const int dx[] = {1, 1, 0, -1, -1, -1, 0, 1};
const int dy[] = {0, 1, 1, 1, 0, -1, -1, -1, 0};
/* *************************************** Global Section End ****************************************** */

/* *************************************** Functions Section Start **************************************** */
void getInitial(char s1[], char s2[], char d1[], int* x, int* y, int* d) {
    /*
    Check if s1 or s2 is of the form "Ax or Sx" & checks if the direction is west or south.
    where if x is negative (west). etc. regarding y as well
    */
    if (sscanf(s1, "A%d", x) == 1) {
        if (*x) {
            char t = s1[strlen(s1) - 1];
            if (t == 'W') *x = -*x;
        }
    }
    if (sscanf(s2, "A%d", x) == 1) {
        if (*x) {
            char t = s2[strlen(s2) - 1];
            if (t == 'W') *x = -*x;
        }
    }
    if (sscanf(s1, "S%d", y) == 1) {
        if (*y) {
            char t = s1[strlen(s1) - 1];
            if(t == 'S') *y = -*y;
        }
    }
    if (sscanf(s2, "S%d", y) == 1) {
        if (*y) {
            char t = s2[strlen(s2) - 1];
            if (t == 'S') *y = -*y;
        }
    }
    *d = -1;
    for (int i = 0; i < 8; i++) {
        if (strcmp(dName[i], d1) == 0) {
            *d = i;
            break;
        }
    }
}

int checkFaceDirection(int x, int y, int shift) { //taking the current robot direction & face direction
    int vx = dx[shift], vy = dy[shift];
    return ((vy && !(x % 25)) || (vx && !(y % 25)) || (vx && vy && !((x + y) % 50)) || (vx && vy && !((y - x) % 50))) ? 0 : 1;
    //Returning the new direction
}

int checkAndMove(int* x, int* y, int shift) { //Checking if the robot can move one step forward without going out of bounds
    int tx = *x + dx[shift], ty = *y + dy[shift];
    *x += dx[shift];
    *y += dy[shift];
    return 1;
}
/* *************************************** Functions Section End ****************************************** */

int main() {
    FILE *directions_file; //File initializing
    directions_file = fopen("directions.txt","r");
    if(directions_file == NULL) //Checking file availability
    {
        printf("File not found.\n");
        exit(1);
    }

    char strx[128], stry[128], strd[128], cmd[128], token1[128], token2[128];
    int sx, sy, dir, n;
    while (fscanf(directions_file,"%s %s %s", strx, stry, strd) == 3) {
        getInitial(strx, stry, strd, &sx, &sy, &dir);
        int safe = 1;
        while (fgets(cmd,sizeof(cmd),directions_file) && strcmp(cmd, "STOP\n")) {
            if (sscanf(cmd, " TURN %s %s", token1, token2) == 2) {
                int vx = sx, vy = sy, vdir = dir;
                checkAndMove(&vx, &vy, vdir);
                int w, d;
                w = !strcmp(token1, "HALF") ? 1 : 3;
                d = !strcmp(token2, "LEFT") ? 1 : -1;
                vdir = (dir + w * d % 8 + 8) % 8;
                int ok = checkFaceDirection(vx, vy, vdir) && checkFaceDirection(sx, sy, dir);
                if (!strcmp(token1, "LEFT"))
                    ok = 1;
                if (dx[dir] && dy[dir])
                    ok = 0;
                if (dx[vdir] && dy[vdir])
                    ok = 0;
                if (!strcmp(token1, "SHARP") && !strcmp(token2, "LEFT")) {
                    ok = 1;
                }
                if (dx[vdir] == dy[vdir] && !((vx + vy) % 50))
                    ok = 0;
                if (dx[vdir] == -dy[vdir] && !((vx - vy) % 50))
                    ok = 0;
                if (dx[vdir] && dy[vdir] && (vx + vy) % 50 && (vx - vy) % 50)
                    ok = 0;
                if (ok)
                    sx = vx, sy = vy, dir = vdir;
            } else if (sscanf(cmd, " TURN %s", token1) == 1) {
                int vx = sx, vy = sy, vdir = dir;
                checkAndMove(&vx, &vy, vdir);
                int w = 2, d;
                d = !strcmp(token1, "LEFT") ? 1 : -1;
                vdir = (dir + w * d % 8 + 8) % 8;
                int ok = checkFaceDirection(vx, vy, vdir) && checkFaceDirection(sx, sy, dir);
                if (!strcmp(token1, "LEFT"))
                    ok = 1;
                if (dx[dir] && dy[dir])
                    ok = 0;
                if (dx[dir] && dy[dir])
                    ok = 0;
                if (dx[vdir] == dy[vdir] && !((vx + vy) % 50))
                    ok = 0;
                if (dx[vdir] == -dy[vdir] && !((vx - vy) % 50))
                    ok = 0;
                if (dx[vdir] && dy[vdir] && (vx + vy) % 50 && (vx - vy) % 50)
                    ok = 0;
                if (ok)
                    sx = vx, sy = vy, dir = vdir;
            } else if (sscanf(cmd, " GO STRAIGHT %d", &n) == 1) {
                if (n > 0) {
                    sx += dx[dir] * n;
                    sy += dy[dir] * n;
                }
            } else if (sscanf(cmd, " GO %d", &n) == 1) {
                if (n > 0) {
                    sx += dx[dir] * n;
                    sy += dy[dir] * n;
                }
            }
        }
        safe = checkFaceDirection(sx, sy, dir);
        if (!safe)
            printf("Illegal stopping place\n");
        else {
            printf("A%d%s S%d%s %s\n", abs(sx), sx < 0 ? "W" : (sx >= 0) ? "E" : "", abs(sy), sy < 0 ? "S" : (sy >= 0) ? "N" : "", dName[dir]);
        }
    }
    return 0;}
