/**
* Created by saif on 1/14/20.
*/
///

#include "neighbor_cells.h"
#include "../validators/validators.h"
#include <stdbool.h>
#include "../playing_board/board.h"

int count_mines(int row, int col, char hidden_brd[][MAXSIDE]) {

    int cnt_ngh_mines = 0;
    /*
     * neighbors
     {-1,-1}, {-1, 0}, {-1, 1},
        { 0,-1}, home { 0, 1},
     { 1,-1}, { 1, 0}, { 1, 1}
    */
    //{-1, 0}
    if (is_cell_valid(row - 1, col) == true) {
        if (is_mine(row - 1, col, hidden_brd) == true) {
            cnt_ngh_mines++;
        }
    }
    //{ 1, 0}
    if (is_cell_valid(row + 1, col) == true) {
        if (is_mine(row + 1, col, hidden_brd) == true) {
            cnt_ngh_mines++;
        }
    }
    //{ 0, 1}
    if (is_cell_valid(row, col + 1) == true) {
        if (is_mine(row, col + 1, hidden_brd) == true) {
            cnt_ngh_mines++;
        }
    }
    //{ 0,-1}
    if (is_cell_valid(row, col - 1) == true) {
        if (is_mine(row, col - 1, hidden_brd) == true) {
            cnt_ngh_mines++;
        }
    }
    //{-1, 1}
    if (is_cell_valid(row - 1, col + 1) == true) {
        if (is_mine(row - 1, col + 1, hidden_brd) == true) {
            cnt_ngh_mines++;
        }
    }
    //{-1,-1}
    if (is_cell_valid(row - 1, col - 1) == true) {
        if (is_mine(row - 1, col - 1, hidden_brd) == true) {
            cnt_ngh_mines++;
        }
    }
    //{ 1, 1}
    if (is_cell_valid(row + 1, col + 1) == true) {
        if (is_mine(row + 1, col + 1, hidden_brd) == true) {
            cnt_ngh_mines++;
        }
    }
    //{ 1,-1}
    if (is_cell_valid(row + 1, col - 1) == true) {
        if (is_mine(row + 1, col - 1, hidden_brd) == true) {
            cnt_ngh_mines++;
        }
    }

    return (cnt_ngh_mines);
}