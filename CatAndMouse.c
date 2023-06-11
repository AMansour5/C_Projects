#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_ROOMS 100

int numRooms, catStart, mouseStart;

int catDoorTo[MAX_ROOMS][MAX_ROOMS];
int mouseDoorTo[MAX_ROOMS][MAX_ROOMS];

bool catChecked[MAX_ROOMS]; // If is false after search, then is not reachable
bool mouseChecked[MAX_ROOMS]; // If is false after search, then is not reachable

void CatWalk(int pos)
{
    catChecked[pos] = true;
    
    for (int i = 0; i < numRooms; ++i)
    {
        if (catDoorTo[pos][i] && !catChecked[i])
            CatWalk(i);
    }
}

bool CanFindPathHome(int pos)
{
    mouseChecked[pos] = true;
    if (catChecked[pos])
        return false;
    
    if (pos == mouseStart)
        return true;
    
    bool canMakeIt = false;
    for (int i = 0; i < numRooms; ++i)
    {
        if (mouseDoorTo[pos][i] && !mouseChecked[i])
            canMakeIt |= CanFindPathHome(i);
    }
    
    return canMakeIt;
}

int main()
{
    int T;
    scanf("%d", &T);
    getchar(); // consume newline
    
    while (T--)
    {
        scanf("%d %d %d\n", &numRooms, &catStart, &mouseStart);
        ++numRooms;
        int from, to;
        
        for (int i = 0; i < numRooms; ++i)
            for (int j = 0; j < numRooms; ++j)
                catDoorTo[i][j] = mouseDoorTo[i][j] = 0;
        
        char buffer[MAX_ROOMS];
        while (fgets(buffer, MAX_ROOMS, stdin) && buffer[0] != '\n')
        {
            sscanf(buffer, "%d %d", &from, &to);
            catDoorTo[from][to] = 1;
        }
        
        while (fgets(buffer, MAX_ROOMS, stdin) && buffer[0] != '\n')
        {
            sscanf(buffer, "%d %d", &from, &to);
            mouseDoorTo[from][to] = 1;
        }
        
        for (int i = 0; i < numRooms; ++i)
            catChecked[i] = mouseChecked[i] = false;
        CatWalk(catStart);
        
        bool possible = false;
        for (int i = 0; i < numRooms; ++i)
        {
            if (mouseDoorTo[mouseStart][i] && !mouseChecked[i])
                possible |= CanFindPathHome(i);
        }
        // Very important because if there are no valid paths, it will not be set otherwise
        mouseChecked[mouseStart] = true;
        
        bool overlap = false;
        for (int i = 0; i < numRooms; ++i)
            if (mouseChecked[i] && catChecked[i])
                overlap = true;
            
        printf("%c %c\n", overlap ? 'Y' : 'N', possible ? 'Y' : 'N');
    }
    
    return 0;
}