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
#include "../player/player.h"
#include "string_util.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <dirent.h>

void play_game(bool restart) {
    srand(time(NULL));
    PLAYERX = init_player();
    load_player();
    //change this if to check playerx
    char *file_path = concat_filepath(PLAYERX);
    GAME = fopen(file_path, "w");
    if (GAME) {
        bool game_over = false;
        //two boards
        cell game_brd[ROWS][COLS];
        int mines[MINES][2];
        init_brd(game_brd);
        place_mines(mines, game_brd);
        count_mines(game_brd);
        int empty_cells = ROWS * COLS - MINES;
        while (game_over == false) {
            print_brd(game_brd);
            print_rmaining_mines();
            print_mbrd(game_brd);
            if (restart) {
                restart_game(game_brd, mines);
                print_brd(game_brd);
                print_rmaining_mines();
                print_mbrd(game_brd);
            }
            move mov = get_move();
            game_over = execute_move(game_brd, mines, mov);
            if (game_over == false && (OPENED_CELLS == empty_cells || FLAGGED_CORRECT == MINES)) {
                printf("\nYou won !\n");
                PLAYERX.wins++;
                FLAGGED_TOTAL = FLAGGED_CORRECT + FLAGGED_WRONG;
                PLAYERX.cells += (OPENED_CELLS + FLAGGED_TOTAL);
                PLAYERX.games++;
                fwrite(&PLAYERX, sizeof(player), 1, GAME);
                fclose(GAME);
                game_over = true;
            }
        }
    } else {
        //call the function again
        fprintf(stderr, "Error, while opening file!\n");
    }
}

void restart_game(cell game_brd[ROWS][COLS], int mines[][2]) {
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
    if (game_brd[x][y].ch != '*' && game_brd[x][y].ngh_mines != 0) {
        open_cell(game_brd, mines, *mov);
        PLAYERX.cells++;
    } else {
        restart_game(game_brd, mines);
    }
    free(mov);
}

bool execute_move(cell game_brd[ROWS][COLS], int mines[][2], move mov) {
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
        flag_cell(game_brd, mov);
    } else {
        bool game_over = open_cell(game_brd, mines, mov);
        return game_over;
    }
    return false;
}

bool open_cell(cell game_brd[ROWS][COLS], int mines[][2], move mov) {
    bool game_over = false;
    if (game_brd[mov.row][mov.col].ch == '*' && game_brd[mov.row][mov.col].state != flagged) {
        PLAYERX.losses++;
        PLAYERX.games++;
        game_brd[mov.row][mov.col].ch = '*';
        for (int i = 0; i < MINES; i++) {
            game_brd[mines[i][0]][mines[i][1]].ch = '*';
        }
        print_brd(game_brd);
        printf("\nYou lost!\n");
        game_over = true;
    } else {
        int count = game_brd[mov.row][mov.col].ngh_mines;
        game_brd[mov.row][mov.col].ngh_mines = count;
        game_brd[mov.row][mov.col].state = opened;
        OPENED_CELLS++;
        if (!count) {
            open_ngh(game_brd, mov);
        }
    }
    return game_over;
}

void flag_cell(cell game_brd[ROWS][COLS], move mov) {
    game_brd[mov.row][mov.col].state = flagged;
    if (game_brd[mov.row][mov.col].ch == '*') {
        FLAGGED_CORRECT++;
        game_brd[mov.row][mov.col].ch = '*';
    } else {
        int count = game_brd[mov.row][mov.col].ngh_mines;
        game_brd[mov.row][mov.col].state = flagged;
        FLAGGED_WRONG++;
        if (!count) {
            open_ngh(game_brd, mov);
        }
    }
}

void open_ngh(cell game_brd[ROWS][COLS], move mov) {
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
                    int count = game_brd[temp->row][temp->col].ngh_mines;
                    game_brd[temp->row][temp->col].state = opened;
                    OPENED_CELLS++;
                    if (!count) {
                        open_ngh(game_brd, *temp);
                    }
                }
            }
        }
    }
    free(temp);
}


