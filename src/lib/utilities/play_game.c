/**
* Created by saif on 1/18/20.
*/
///

#include "play_game.h"
#include "playing_util.h"
#include "mines_util.h"
#include <stdbool.h>
#include <stdio.h>
#include "../boards/board.h"
#include "../boards/board_variables.h"
#include "../validators/validators.h"
#include "neighbor_cells.h"

void play_game() {
    bool game_over = false;
    //two boards
    cell hidden_brd[ROWS][COLS], game_brd[ROWS][COLS];
    int remaining_moves = ROWS * COLS - MINES;
    int mines[MINES][2];
    init_brds(hidden_brd, game_brd);
    place_mines(mines, hidden_brd);

    int executed_moves = 0;
    while (game_over == false) {
        print_brd(game_brd);
        move mov = make_move();
        executed_moves++;
        game_over = execute_move(game_brd, hidden_brd, mines, mov, &remaining_moves);
        if ((game_over == false) && (remaining_moves == 0)) {
            //TODO it prints you won when aborting the game
            printf("\nYou won !\n");
            game_over = true;
        }
    }
}

bool execute_move(cell game_brd[ROWS][COLS], cell hidden_brd[ROWS][COLS],
                  int mines[][2], move mov, int *remaining_moves) {

    if (game_brd[mov.row][mov.col].s == opened) {
        printf("Already opened, try another cell\n");
        return false;
    }
    if (game_brd[mov.row][mov.col].s == flagged) {
        printf("Already opened, try another cell\n");
        return false;
    }

    if (mov.flag) {
        do_flagging(game_brd, hidden_brd, mines, mov, remaining_moves);
    } else {
        bool game_over = open_cell(game_brd, hidden_brd, mines, mov, remaining_moves);
        return game_over;
    }
    return false;
}

bool open_cell(cell game_brd[ROWS][COLS], cell hidden_brd[ROWS][COLS],
               int mines[][2], move mov, int *remaining_moves) {
    bool game_over = false;
    if (hidden_brd[mov.row][mov.col].ch == '*' && hidden_brd[mov.row][mov.col].s != flagged) {
        game_brd[mov.row][mov.col].ch = '*';
        for (int i = 0; i < MINES; i++) {
            game_brd[mines[i][0]][mines[i][1]].ch = '*';
        }
        print_brd(game_brd);
        printf("\nYou lost!\n");
        game_over = true;
    } else {
        int count = count_mines(mov.row, mov.col, hidden_brd);
        (*remaining_moves)--;
        game_brd[mov.row][mov.col].ngh_mines = count;
        game_brd[mov.row][mov.col].s = opened;
        if (!count) {
            do_recursion(game_brd, hidden_brd, mines, mov, remaining_moves);
        }
    }
    return game_over;
}
void do_flagging(cell game_brd[ROWS][COLS], cell hidden_brd[ROWS][COLS],
                 int mines[][2], move mov, int *remaining_moves) {
    hidden_brd[mov.row][mov.col].s = flagged;
    if (hidden_brd[mov.row][mov.col].ch == '*') {
        game_brd[mov.row][mov.col].ch = '*';
    } else {
        int count = count_mines(mov.row, mov.col, hidden_brd);
        (*remaining_moves)--;
        game_brd[mov.row][mov.col].ngh_mines = count;
        game_brd[mov.row][mov.col].s = opened;
        if (!count) {
            do_recursion(game_brd, hidden_brd, mines, mov, remaining_moves);
        }
    }
}
void do_recursion(cell game_brd[ROWS][COLS], cell hidden_brd[ROWS][COLS],
                  int mines[][2], move mov, int *remaining_moves) {
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
            if (is_cell_valid(mov.row + neighbors[i][j], mov.col + neighbors[i][j + 1]) == true) {
                if (is_mine(mov.row + neighbors[i][j], mov.col + neighbors[i][j + 1], hidden_brd) ==
                    false) {
                    mov.row = mov.row + neighbors[i][j + 1];
                    mov.col = mov.col + neighbors[i][j];
                    execute_move(game_brd, hidden_brd, mines, mov, remaining_moves);
                }
            }
        }
    }
}


