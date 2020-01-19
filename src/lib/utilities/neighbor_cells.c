/**
* Created by saif on 1/14/20.
*/
///

#include "neighbor_cells.h"
#include "../validators/validators.h"
#include <stdbool.h>
#include "../boards/board.h"

int count_mines(int x_crd, int y_crd, char hidden_brd[ROWS][COLS]) {
    int cnt_ngh_mines = 0;
    /*
     * neighbors
     {-1,-1}, {-1, 0}, {-1, 1},
        { 0,-1}, home { 0, 1},
     { 1,-1}, { 1, 0}, { 1, 1}
    */
    //{-1, 0}
    if (is_cell_valid(x_crd - 1, y_crd) == true) {
        if (is_mine(x_crd - 1, y_crd, hidden_brd) == true) {
            cnt_ngh_mines++;
        }
    }
    //{ 1, 0}
    if (is_cell_valid(x_crd + 1, y_crd) == true) {
        if (is_mine(x_crd + 1, y_crd, hidden_brd) == true) {
            cnt_ngh_mines++;
        }
    }
    //{ 0, 1}
    if (is_cell_valid(x_crd, y_crd + 1) == true) {
        if (is_mine(x_crd, y_crd + 1, hidden_brd) == true) {
            cnt_ngh_mines++;
        }
    }
    //{ 0,-1}
    if (is_cell_valid(x_crd, y_crd - 1) == true) {
        if (is_mine(x_crd, y_crd - 1, hidden_brd) == true) {
            cnt_ngh_mines++;
        }
    }
    //{-1, 1}
    if (is_cell_valid(x_crd - 1, y_crd + 1) == true) {
        if (is_mine(x_crd - 1, y_crd + 1, hidden_brd) == true) {
            cnt_ngh_mines++;
        }
    }
    //{-1,-1}
    if (is_cell_valid(x_crd - 1, y_crd - 1) == true) {
        if (is_mine(x_crd - 1, y_crd - 1, hidden_brd) == true) {
            cnt_ngh_mines++;
        }
    }
    //{ 1, 1}
    if (is_cell_valid(x_crd + 1, y_crd + 1) == true) {
        if (is_mine(x_crd + 1, y_crd + 1, hidden_brd) == true) {
            cnt_ngh_mines++;
        }
    }
    //{ 1,-1}
    if (is_cell_valid(x_crd + 1, y_crd - 1) == true) {
        if (is_mine(x_crd + 1, y_crd - 1, hidden_brd) == true) {
            cnt_ngh_mines++;
        }
    }

    return cnt_ngh_mines;
}