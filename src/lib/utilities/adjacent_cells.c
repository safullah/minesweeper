/**
* Created by saif on 1/14/20.
*/
///

#include "adjacent_cells.h"
#include "../validators/validators.h"
#include <stdbool.h>
#include "../playing_board/board.h"
// A Function to count the number of
// mines in the adjacent cells
int countAdjacentMines(int row, int col, int mines[][2],
                       char realBoard[][MAXSIDE])
{

    int i;
    int count = 0;

    /*
        Count all the mines in the 8 adjacent
        cells

            N.W N N.E
            \ | /
            \ | /
            W----Cell----E
                / | \
            / | \
            S.W S S.E

        Cell-->Current Cell (row, col)
        N --> North	 (row-1, col)
        S --> South	 (row+1, col)
        E --> East		 (row, col+1)
        W --> West		 (row, col-1)
        N.E--> North-East (row-1, col+1)
        N.W--> North-West (row-1, col-1)
        S.E--> South-East (row+1, col+1)
        S.W--> South-West (row+1, col-1)
    */

    //----------- 1st Neighbour (North) ------------

    // Only process this cell if this is a valid one
    if (isValid (row-1, col) == true)
    {
        if (isMine (row-1, col, realBoard) == true){

            count++;
        }
    }

    //----------- 2nd Neighbour (South) ------------

    // Only process this cell if this is a valid one
    if (isValid (row+1, col) == true)
    {
        if (isMine (row+1, col, realBoard) == true){

            count++;
        }
    }

    //----------- 3rd Neighbour (East) ------------

    // Only process this cell if this is a valid one
    if (isValid (row, col+1) == true)
    {
        if (isMine (row, col+1, realBoard) == true){

            count++;
        }
    }

    //----------- 4th Neighbour (West) ------------

    // Only process this cell if this is a valid one
    if (isValid (row, col-1) == true)
    {
        if (isMine (row, col-1, realBoard) == true){

            count++;
        }
    }

    //----------- 5th Neighbour (North-East) ------------

    // Only process this cell if this is a valid one
    if (isValid (row-1, col+1) == true)
    {
        if (isMine (row-1, col+1, realBoard) == true){

            count++;
        }
    }

    //----------- 6th Neighbour (North-West) ------------

    // Only process this cell if this is a valid one
    if (isValid (row-1, col-1) == true)
    {
        if (isMine (row-1, col-1, realBoard) == true){

            count++;
        }
    }

    //----------- 7th Neighbour (South-East) ------------

    // Only process this cell if this is a valid one
    if (isValid (row+1, col+1) == true)
    {
        if (isMine (row+1, col+1, realBoard) == true){

            count++;
        }
    }

    //----------- 8th Neighbour (South-West) ------------

    // Only process this cell if this is a valid one
    if (isValid (row+1, col-1) == true)
    {
        if (isMine (row+1, col-1, realBoard) == true){

            count++;
        }
    }

    return (count);
}