/**
* Created by saif on 1/18/20.
*/
///

#include "game_util.h"
#include "playing_util.h"
#include "mines_util.h"
#include <stdbool.h>
#include <stdio.h>
#include "../board/board.h"
#include "../board/board_variables.h"
#include "../validators/validators.h"
#include "../player/player.h"
#include "string_util.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>

void play_game(bool restart) {
    srand(time(NULL));
    cell game_brd[ROWS][COLS];
    PLAYERX = init_player();
    char *file_path = concat_filepath(PLAYERX);
    bool loaded = false;
    if (is_existent()) {
        loaded = load_player(game_brd);
    }
    GAME = fopen(file_path, "w");
    if (GAME) {
        int mines[MINES][2];
        if (!loaded) {
            init_brd(game_brd);
            place_mines(mines, game_brd);
            count_mines(game_brd);
        }
        int empty_cells = ROWS * COLS - MINES;
        bool game_over = false;
        move mov;
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
            mov = get_move();
            if (mov.abort) {
                save_game(game_brd, mov.abort);
            }
            game_over = execute_move(game_brd, mines, mov);
            //in case of winning the game
            if (game_over == false && (OPENED_CELLS == empty_cells || FLAGGED_CORRECT == MINES)) {
                print_brd(game_brd);
                print_rmaining_mines();
                printf("You won!\n");
                PLAYERX.wins++;
                PLAYERX.games++;
                save_game(game_brd, mov.abort);
            }
        }
        //in case of losing the game
        save_game(game_brd, mov.abort);
    } else {
        fprintf(stderr, "Error, while opening file!\n");
        exit(EXIT_FAILURE);
    }
}

void restart_game(cell game_brd[ROWS][COLS], int mines[][2]) {
    //open a random cell
    int random = rand() % (ROWS * COLS) + 1;
    int x = random / ROWS;
    int y = random % COLS;
    move *mov = malloc(sizeof(move));
    if (!mov) {
        printf("Error, out of memory\n");
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

void save_game(cell game_brd[ROWS][COLS], bool abort) {
    FLAGGED_TOTAL = FLAGGED_CORRECT + FLAGGED_WRONG;
    PLAYERX.cells += (OPENED_CELLS + FLAGGED_TOTAL);
    PLAYERX.info.aborted = abort;
    if (fwrite(&PLAYERX, sizeof(player), 1, GAME) != 1) {
        printf("Error, while saving the player!");
        exit(EXIT_FAILURE);
    }
    if (abort) {
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                if (fwrite(&game_brd[i][j], sizeof(cell), 1, GAME) == 0) {
                    printf("Error, while saving the game!");
                    exit(EXIT_FAILURE);
                }
            }
        }
    }
    fclose(GAME);
    exit(EXIT_SUCCESS);
}

bool execute_move(cell game_brd[ROWS][COLS], int mines[][2], move mov) {
    bool game_over = false;
    if (game_brd[mov.row][mov.col].state == opened || game_brd[mov.row][mov.col].state == flagged) {
        printf("Already opened, try another cell\n");
    } else {
        if (mov.flag) {
            flag_cell(game_brd, mov);
        } else {
            game_over = open_cell(game_brd, mines, mov);
        }
    }
    return game_over;
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
        printf("You lost!\n");
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


