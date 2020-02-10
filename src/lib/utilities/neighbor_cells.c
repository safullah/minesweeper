/**
* Created by saif on 1/14/20.
*/
///

#include "neighbor_cells.h"
#include <stdbool.h>
#include "../validators/validators.h"

int do_counting(int x_crd, int y_crd, cell hidden_brd[ROWS][COLS]) {
    int cnt_ngh_mines = 0;
    int neighbors[8][2] = {{-1, -1},
                           {-1, 0},
                           {-1, 1},
                           {0,  -1},
                           {0,  1},
                           {1,  1},
                           {1,  -1},
                           {1,  0}};
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 1; ++j) {
            if (is_cell_valid(x_crd + neighbors[i][j], y_crd + neighbors[i][j + 1]) == true) {
                if (is_mine(x_crd + neighbors[i][j], y_crd + neighbors[i][j + 1], hidden_brd) == true) {
                    cnt_ngh_mines++;
                }
            }
        }
    }
    return cnt_ngh_mines;
}