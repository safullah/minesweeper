/**
* Created by saif on 1/14/20.
*/
///

#include "neighbor_util.h"
#include "../validators/validators.h"

int do_counting(int row, int col, cell game_brd[ROWS][COLS]) {
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
            int r = row + neighbors[i][j];
            int c = col + neighbors[i][j + 1];
            if (is_cell_valid(r, c)) {
                if (is_mine(r, c, game_brd)) {
                    cnt_ngh_mines++;
                }
            }
        }
    }
    return cnt_ngh_mines;
}
