/**
 * \file game_util.c
 * \brief functions to play the game
* Created by saif on 1/18/20.
*/
///

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <limits.h>
#include "game_util.h"
#include "playing_util.h"
#include "mines_util.h"
#include "../board/board.h"
#include "../board/board_variables.h"
#include "../validators/validators.h"
#include "../player/player.h"
#include "string_util.h"
#include "../service/setget/setget.h"

char *this_file = "game_util.c";

/**
 * \brief the logic of the game is this function
 *
 * If the player has an aborted game and the player wishes to load that game then the aborted game is loaded.
 * Otherwise a new game is created for the player.
 * The game goes on until it is won or lost.
 * The player has the option to abort or exit the game or start a new game.
 * With the -help command help help.txt is opened in vim in read only mode
 *
 * @param answer    answer to the question if player wants to load an aborted game
 * @param player_file_path path to the file of the player, where his statistic and game are saved
 * @return game_result      result can be win, loss, aborted or an error occurred
 */
game_result play_game(char *answer, char *player_file_path) {
    game_result gresult = {false, false, false, false};
    bool aborted_game_loaded = false;
    cell game_brd[ROWS][COLS];
    if (answer) {
        if (strcmp(answer, "y") == 0 || strcmp(answer, "yes") == 0) {
            aborted_game_loaded = set_board(game_brd, player_file_path);
            if (!aborted_game_loaded) {
                printf("aborted game could not be loaded\n"
                       "but a new game was created for you\n");

            }
        }
    }
    GAME = fopen(player_file_path, "w");
    if (GAME) {
        /*if a game was not loaded then game_brd is empty. it need to be filled
         * in case of restart loaded has to be false. because the board need to be prepared fo a new game*/
        if (!aborted_game_loaded) {
            init_brd(game_brd);
            place_mines(game_brd);
            count_mines(game_brd);
        }
        int empty_cells = ROWS * COLS - MINES;
        check p_check = {false, false};
        move mov;
        while (p_check.game_over != true) {
            system("clear");
            print_brd(game_brd);
            print_rmaining_mines();
            show_brd(game_brd);
            mov = get_move();

            /*start a new game*/
            if (mov.restart) {
                restart_game(game_brd);
                continue;
            }

            /*abort the game*/
            if (mov.abort) {
                gresult.abort = true;
                if (!save_game(game_brd, mov.abort)) {
                    printf("Error:  %s "
                           "save_game(game_brd, mov.abort)\n", this_file);
                    gresult.error = true;
                }
                goto end;
            }
            /*win or loss*/
            p_check = execute_move(game_brd, mov);
            gresult.error = p_check.error;
            if (p_check.game_over) {
                gresult.loss = true;
                if (!save_game(game_brd, mov.abort)) {
                    printf("Error:  %s "
                           "save_game(game_brd, mov.abort)\n", this_file);
                    gresult.error = true;
                }
            } else {
                if (OPENED_CELLS == empty_cells || FLAGGED_CORRECT == MINES) {
                    gresult.win = true;
                    p_check.game_over = true;
                    print_brd(game_brd);
                    print_rmaining_mines();
                    PLAYERX.wins++;
                    PLAYERX.games++;
                    if (!save_game(game_brd, mov.abort)) {
                        printf("Error:  %s "
                               "save_game(game_brd, mov.abort)\n", this_file);
                        gresult.error = true;
                    }
                }
            }
        }
    } else {
        printf("Error:  %s "
               "GAME = fopen(player_file_path, \"w\")", this_file);
        gresult.error = true;
    }
    end :
    return gresult;
}

/**
 * \brief saves the game
 *
 * Saves the statistics of the player.
 * If game is aborted the game is saved as well
 *
 * @param game_brd
 * @param abort     was the game aborted or not
 * @return bool     saving game successful or not
 */
bool save_game(cell game_brd[ROWS][COLS], bool abort) {
    bool saved = true;
    FLAGGED_TOTAL = FLAGGED_CORRECT + FLAGGED_WRONG;
    PLAYERX.cells += (OPENED_CELLS + FLAGGED_TOTAL);
    PLAYERX.info.aborted = abort;
    if (abort) {
        PLAYERX.info.rows = ROWS;
        PLAYERX.info.cols = COLS;
        PLAYERX.info.mines = MINES;
    }
    if (fwrite(&PLAYERX, sizeof(player), 1, GAME) != 1) {
        printf("Error: %s "
               "fwrite(&PLAYERX, sizeof(player), 1, GAME)", this_file);
        saved = false;
    }
    if (abort) {
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                if (fwrite(&game_brd[i][j], sizeof(cell), 1, GAME) == 0) {
                    printf("Error: %s "
                           "fwrite(&game_brd[i][j], sizeof(cell), 1, GAME)", this_file);
                    saved = false;
                }
            }
        }
    }
    fclose(GAME);
    return saved;
}

/**
 * \brief executes the move
 *
 * execute_move flags or opens a cell
 * In case the cell is a mine then the game is over
 *
 * @param game_brd
 * @param mov   the move which is to be executed
 * @return check     is game over and did any error occur
 */
check execute_move(cell game_brd[ROWS][COLS], move mov) {
    check e_check = {false, false};
    if (game_brd[mov.row][mov.col].state == opened || game_brd[mov.row][mov.col].state == flagged) {
        printf("Cell open, try another one.\n");
    } else {
        if (mov.flag) {
            e_check.error = flag_cell(game_brd, mov);
            if (e_check.error) {
                printf("Error: %s "
                       "flag_cell(game_brd, mov)", this_file);
            }
        } else {
            e_check = open_cell(game_brd, mov);
            if (e_check.error) {
                printf("Error: %s "
                       "open_cell(game_brd, mines, mov)", this_file);
            }
        }
    }
    return e_check;
}

/**
 * \brief opens a cell
 *
 * open_cell opens a cell. If the count of neighboring mines is zero, then these neighbors are opened
 * If player steps on a mines the game is over
 *
 * @param game_brd
 * @param mov    contains the cell which is to be opened
 * @return check  game over or not and did any error occur
 */
check open_cell(cell game_brd[ROWS][COLS], move mov) {
    check o_check = {false, false};
    if (game_brd[mov.row][mov.col].ch == '*' && game_brd[mov.row][mov.col].state != flagged) {
        PLAYERX.losses++;
        PLAYERX.games++;
        game_brd[mov.row][mov.col].ch = '*';
        show_brd(game_brd);
        o_check.game_over = true;
    } else {
        int count = game_brd[mov.row][mov.col].ngh_mines;
        game_brd[mov.row][mov.col].ngh_mines = count;
        game_brd[mov.row][mov.col].state = opened;
        OPENED_CELLS++;
        if (!count) {
            o_check.error = open_ngh(game_brd, mov);
            if (o_check.error) {
                printf("Error: %s "
                       "open_ngh(game_brd, mov)", this_file);
            }
        }
    }
    return o_check;
}

/**
 * \brief flags a cell
 *
 * flag_cell flags a cell, if cell is mine it is shown otherwise it shows the count of neighbouring mines
 * If count is zero these neighboring cells are opened
 *
 * @param game_brd
 * @param mov   contains the cell to be flagged
 * @return bool     did any error occur
 */
bool flag_cell(cell game_brd[ROWS][COLS], move mov) {
    bool error = false;
    game_brd[mov.row][mov.col].state = flagged;
    if (game_brd[mov.row][mov.col].ch == '*') {
        FLAGGED_CORRECT++;
    } else {
        int count = game_brd[mov.row][mov.col].ngh_mines;
        game_brd[mov.row][mov.col].state = flagged;
        FLAGGED_WRONG++;
        if (!count) {
            error = open_ngh(game_brd, mov);
            if (error) {
                printf("Error: %s "
                       "open_ngh(game_brd, mov)", this_file);
            }
        }
    }
    return error;
}

/**
 * \brief opens neighbor cell
 *
 * opens neighbors cells if count of neighboring mines is zero
 *
 * @param game_brd
 * @param mov
 * @return bool     did any error occur
 */
bool open_ngh(cell game_brd[ROWS][COLS], move mov) {
    bool error = false;
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
        printf("Error: %s"
               "move *temp = malloc(sizeof(move))\n", this_file);
        error = true;
    } else {
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
                            error = open_ngh(game_brd, *temp);
                            if (error) {
                                printf("Error: %s"
                                       "open_ngh(game_brd, *temp)\n", this_file);
                                goto end;
                            }
                        }
                    }
                }
            }
        }
        end :
        free(temp);
    }
    return error;
}

/**
 * \brief starts a new game
 *
 * starts a new game and opens a random cell which is not a mines or the count of neighboring mines is not zero
 *
 * @param game_brd  rows and cols stay of the game from where the game  is restarted
 */
void restart_game(cell game_brd[ROWS][COLS]) {
    printf("\nnew game\n");
    init_brd(game_brd);
    place_mines(game_brd);
    count_mines(game_brd);
    open_randomcell(game_brd);
}

/**
 * \brief opens a random cell
 *
 * opens a random cell which is not a mines or  or the count of neighboring mines is not zero
 *
 * @param game_brd
 */
void open_randomcell(cell game_brd[ROWS][COLS]) {
    srand(time(NULL));
    bool opened = false;
    while (opened != true) {
        int x = rand() % ROWS;
        int y = rand() % COLS;
        move mov = {false, -1,-1, false, false};
        mov.row = x;
        mov.col = y;
        if (game_brd[x][y].ch != '*' && game_brd[x][y].ngh_mines != 0) {
            open_cell(game_brd, mov);
            PLAYERX.cells++;
            opened = true;
        }
    }
}

/**
 * \brief opens help instructions
 *
 * opens help.txt in vim in read only mode.
 */
void help() {
    printf("opening help instructions\n");
    char minespr_path[PATH_MAX + 1] = {'\0'};
    char *target = "minespr";
    char *result = realpath(target, minespr_path);
    if (!result) {
        strcpy(minespr_path, get_path(target));
    } else {
        strcat(minespr_path, "/");
    }
    char *file_name = "help.txt";
    bool existent = is_existent(minespr_path, file_name);
    if (existent) {
        char *file_path = concat_filepath(minespr_path, file_name);
        int len_file_path = strlen(file_path);

        char *chmod = "chmod 444 ";
        char chmod_buf[len_file_path + strlen(chmod)];
        strcpy(chmod_buf, chmod);
        strcat(chmod_buf, file_path);
        system(chmod_buf);

        char *vim = "vim ";
        char vim_buf[len_file_path + strlen(vim)];
        strcpy(vim_buf, vim);
        strcat(vim_buf, file_path);
        system(vim_buf);

        system("clear");
    } else {
        printf("Error: %s "
               "bool existent = is_existent(minespr_path, file_name)", this_file);
    }

}
