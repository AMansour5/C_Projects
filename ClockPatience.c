#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Pile
{
    char card[4];
    char suit[4];
    int pos;
};

int main()
{
    int cardPos[128] = {0};
    cardPos['A'] = 0; cardPos['2'] = 1; cardPos['3'] = 2;
    cardPos['4'] = 3; cardPos['5'] = 4; cardPos['6'] = 5;
    cardPos['7'] = 6; cardPos['8'] = 7; cardPos['9'] = 8;
    cardPos['T'] = 9; cardPos['J'] = 10; cardPos['Q'] = 11;
    cardPos['K'] = 12;

    struct Pile allPiles[13];

    char card, suit;
    while (scanf("%c%c", &card, &suit) == 2 && card != '#')
    {
        allPiles[12].card[0] = card;
        allPiles[12].suit[0] = suit;

        int loadCount = 0;

        for (int cPos = 0; cPos < 4; ++cPos)
        {
            int pile = (cPos) ? 12 : 11;

            for (; pile >= 0; --pile)
            {
                scanf(" %c%c", &card, &suit);
                allPiles[pile].card[cPos] = card;
                allPiles[pile].suit[cPos] = suit;
                ++loadCount;
            }
        }

        for (int i = 0; i < 13; ++i)
            allPiles[i].pos = 0;

        int pile = 12;
        int previous;

        int count = 0;

        while (allPiles[pile].pos < 4)
        {
            ++count;
            previous = pile;
            pile = cardPos[(int)allPiles[pile].card[allPiles[pile].pos++]];

        }

        int pos = allPiles[previous].pos - 1;
        struct Pile printedPile = allPiles[previous];
        if (count < 10)
            printf("0%d,%c%c\n", count, printedPile.card[pos], printedPile.suit[pos]);
        else
            printf("%d,%c%c\n", count, printedPile.card[pos], printedPile.suit[pos]);
    }

    return 0;
}
