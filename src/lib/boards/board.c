/**
* Created by saif on 1/10/20.
*/
///

#include "board.h"
#include "board_variables.h"
#include <stdio.h>

void init_brds(char hidden_brd[ROWS][COLS], char gaming_brd[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            gaming_brd[i][j] = hidden_brd[i][j] = '-';
        }
    }
}

void print_brd(char game_brd[ROWS][COLS]) {
    printf("    ");
    for (int i = 0; i < ROWS; i++) {
        printf("%d  ", i);
    }
    printf("\n");
    for (int i = 0; i < ROWS; i++) {
        if (i < 10) {
            printf("%d  ", i);
        } else {
            printf("%d ", i);
        }

        for (int j = 0; j < COLS; j++) {
            if (j < 10) {
                printf(" %c ", game_brd[i][j]);
            } else {
                printf("  %c ", game_brd[i][j]);
            }
        }
        printf("\n");
    }
}


/*
void generate_playing_boatd(char myBoard[ROWS][COLS])
{
    int i, j;

    printf ("    ");

    for (i=0; i<SIDE; i++)
        printf ("%d ", i);

    printf ("\n\n");

    for (i=0; i<SIDE; i++)
    {
        printf ("%d   ", i);

        for (j=0; j<SIDE; j++)
            printf ("%c ", myBoard[i][j]);
        printf ("\n");
    }
    return;

    typedef struct cell {
    char cell_char[3];
    bool state;
    bool mine;
    int neigbor_mines;

} Cell;

Cell cell00 = {"|x|", false, false, 0};
Cell cell01 = {"|x|", false, false, 0};

Cell board [10][10] = {
        {cell00, cell01}
};
for (int i = 0; i < 1; i++) {
for (int j = 0; j < 2; j++) {
printf(board[i][j].cell_char);
}
}
}
 */
