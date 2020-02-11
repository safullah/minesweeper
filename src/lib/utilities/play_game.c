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
#include <stdlib.h>
#include <time.h>

void play_game(bool restart) {
    srand(time(NULL));
    bool game_over = false;
    //two boards
    cell hidden_brd[ROWS][COLS], game_brd[ROWS][COLS];
    int remaining_moves = ROWS * COLS - MINES;
    int mines[MINES][2];
    init_brds(hidden_brd, game_brd);
    place_mines(mines, hidden_brd);
    count_mines(hidden_brd);

    int executed_moves = 0;
    while (game_over == false) {
        print_brd(game_brd);
        print_hbrd(hidden_brd);
        if (restart) {
            restart_game(game_brd, hidden_brd, mines, &remaining_moves);
            print_brd(game_brd);
            print_hbrd(hidden_brd);
        }
        move mov = get_move();
        executed_moves++;
        game_over = execute_move(game_brd, hidden_brd, mines, mov, &remaining_moves);
        if ((game_over == false) && (remaining_moves == 0)) {
            //TODO it prints you won when aborting the game
            printf("\nYou won !\n");
            game_over = true;
        }
    }
}

void restart_game(cell game_brd[ROWS][COLS], cell hidden_brd[ROWS][COLS], int mines[][2], int *remaining_moves) {
    //open a random cell
    int random = rand() % (ROWS * COLS) + 1;
    int x = random / ROWS;
    int y = random % COLS;
    move *mov = malloc(sizeof(move));
    if (!mov) {
        printf("ERROR: Out of memory\n");
        exit(EXIT_FAILURE);
    }
    mov->row = x;
    mov->col = y;
    if (game_brd[x][y].ch != '*' && hidden_brd[x][y].ngh_mines != 0) {
        open_cell(game_brd, hidden_brd, mines, *mov, remaining_moves);
    } else {
        restart_game(game_brd, hidden_brd, mines, remaining_moves);
    }
    free(mov);
}

bool execute_move(cell game_brd[ROWS][COLS], cell hidden_brd[ROWS][COLS],
                  int mines[][2], move mov, int *remaining_moves) {
    /*
    if (game_brd[mov.row][mov.col].s == opened) {
        printf("Already opened, try another cell\n");
        return false;
    }
    if (game_brd[mov.row][mov.col].s == flagged) {
        printf("Already opened, try another cell\n");
        return false;
    }
    */
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
    if (hidden_brd[mov.row][mov.col].ch == '*' && hidden_brd[mov.row][mov.col].state != flagged) {
        game_brd[mov.row][mov.col].ch = '*';
        for (int i = 0; i < MINES; i++) {
            game_brd[mines[i][0]][mines[i][1]].ch = '*';
        }
        print_brd(game_brd);
        printf("\nYou lost!\n");
        game_over = true;
    } else {
        (*remaining_moves)--;
        int count = hidden_brd[mov.row][mov.col].ngh_mines;
        game_brd[mov.row][mov.col].ngh_mines = count;
        game_brd[mov.row][mov.col].state = opened;
        if (!count) {
            open_ngh(game_brd, hidden_brd, mov, remaining_moves);
        }
    }
    return game_over;
}

void do_flagging(cell game_brd[ROWS][COLS], cell hidden_brd[ROWS][COLS],
                 int mines[][2], move mov, int *remaining_moves) {
    hidden_brd[mov.row][mov.col].state = flagged;
    if (hidden_brd[mov.row][mov.col].ch == '*') {
        game_brd[mov.row][mov.col].ch = '*';
    } else {
        (*remaining_moves)--;
        int count = hidden_brd[mov.row][mov.col].ngh_mines;
        game_brd[mov.row][mov.col].ngh_mines = count;
        game_brd[mov.row][mov.col].state = opened;
        if (!count) {
            open_ngh(game_brd, hidden_brd, mov, remaining_moves);
        }
    }
}

void open_ngh(cell game_brd[ROWS][COLS], cell hidden_brd[ROWS][COLS], move mov, int *remaining_moves) {
    int neighbors[8][2] = {{-1, -1},
                           {-1, 0},
                           {-1, 1},
                           {0,  -1},
                           {0,  1},
                           {1,  1},
                           {1,  -1},
                           {1,  0}};
    move *temp = malloc(sizeof(move));
    if (!temp) {
        printf("ERROR: Out of memory\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 1; ++j) {
            temp->row = mov.row + neighbors[i][j];
            temp->col = mov.col + neighbors[i][j + 1];
            if (is_cell_valid(temp->row, temp->col)) {
                if (game_brd[temp->row][temp->col].state == hidden) {
                    (*remaining_moves)--;
                    int count = hidden_brd[temp->row][temp->col].ngh_mines;
                    game_brd[temp->row][temp->col].ngh_mines = count;
                    game_brd[temp->row][temp->col].state = opened;
                    if (!count) {
                        open_ngh(game_brd, hidden_brd, *temp, remaining_moves);
                    }
                }
            }
        }
    }
    free(temp);
}


