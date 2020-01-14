/**
* Created by saif on 1/10/20.
*/
///

#include "board.h"
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>


// A Function to choose the difficulty level
// of the game
void chooseDifficultyLevel ()
{
    /*
    --> BEGINNER = 9 * 9 Cells and 10 Mines
    --> INTERMEDIATE = 16 * 16 Cells and 40 Mines
    --> ADVANCED = 24 * 24 Cells and 99 Mines
    */

    int level = 0;
/*
    printf ("Enter the Difficulty Level\n");
    printf ("Press 0 for BEGINNER (9 * 9 Cells and 10 Mines)\n");
    printf ("Press 1 for INTERMEDIATE (16 * 16 Cells and 40 Mines)\n");
    printf ("Press 2 for ADVANCED (24 * 24 Cells and 99 Mines)\n");
*/
    //scanf ("%d", &level);

    if (level == BEGINNER)
    {
        SIDE = 10;
        MINES = 10;
    }

    if (level == INTERMEDIATE)
    {
        SIDE = 16;
        MINES = 40;
    }

    if (level == ADVANCED)
    {
        SIDE = 24;
        MINES = 99;
    }

    return;
}

// A Function to init_boards the game
void init_boards(char hidden_board[][MAXSIDE], char gaming_board[][MAXSIDE])
{
    // Initiate the random number generator so that
    // the same configuration doesn't arises
    srand(time (NULL));

    // Assign all the cells as mine-free
    for (int i=0; i<SIDE; i++)
    {
        for (int j=0; j<SIDE; j++)
        {
            gaming_board[i][j] = hidden_board[i][j] = '-';
        }
    }

    return;
}

// A Function to print the current gameplay board
void printBoard(char myBoard[][MAXSIDE])
{
    int i, j;

    printf ("   ");

    for (i=0; i<SIDE; i++) {
        printf ("%d  ", i);
    }

    printf ("\n");

    for (i=0; i<SIDE; i++)
    {
        printf ("%d ", i);

        for (j=0; j<SIDE; j++){
            printf (" %c ", myBoard[i][j]);
        }
        printf ("\n");
    }
    return;
}


/*
void generate_playing_boatd(char myBoard[][MAXSIDE])
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
