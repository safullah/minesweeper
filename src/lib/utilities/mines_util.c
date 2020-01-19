/**
* Created by saif on 1/14/20.
*/
///

#include "mines_util.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "../playing_board/board.h"

// A Function to place the mines randomly
// on the board
void place_mines(int mines[][2], char hidden_board[][MAXSIDE])
{
    bool mark[MAXSIDE*MAXSIDE];

    memset (mark, false, sizeof (mark));

    // Continue until all random mines have been created.
    for (int i=0; i<MINES; )
    {
        int random = rand() % (SIDE*SIDE);
        int x = random / SIDE;
        int y = random % SIDE;

        // Add the mine if no mine is placed at this
        // position on the board
        if (mark[random] == false)
        {
            // Row Index of the Mine
            mines[i][0]= x;
            // Column Index of the Mine
            mines[i][1] = y;

            // Place the mine
            hidden_board[mines[i][0]][mines[i][1]] = '*';
            mark[random] = true;
            i++;
        }
    }

    return;
}

// A function to replace the mine from (row, col) and put
// it to a vacant space
void replace_mine (int row, int col, char board[][MAXSIDE])
{
    for (int i=0; i<SIDE; i++)
    {
        for (int j=0; j<SIDE; j++)
        {
            // Find the first location in the board
            // which is not having a mine and put a mine
            // there.
            if (board[i][j] != '*')
            {
                board[i][j] = '*';
                board[row][col] = '-';
                return;
            }
        }
    }
    return;
}