/**
* Created by saif on 1/14/20.
*/
///

#include "playing_util.h"
#include "../validators/validators.h"

#include <stdbool.h>
#include "neighbor_cells.h"
#include "../boards/board.h"
#include "../boards/board_variables.h"
#include <stdio.h>
#include "mines_util.h"
#include "play_game.h"
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//flag or not
//seperate alp from num

input_of_move separate_str(char str[]) {

    input_of_move mov = {'\0', {'\0'}};
    char digit[2] = {'\0'};
    //do uppercase first
    if (isalpha(str[0])) {
        mov.alpha = toupper(str[0]);
    } else {
        printf("Error, please enter coordinates in the following format:\n"
               "  enter column row : A5\n");
        return mov;
    }

    if (isdigit(str[1])) {
        digit[0] = str[1];
        //start concat
        strcat(mov.num, &digit[0]);

        if (isdigit(str[2])) {
            digit[1] = str[2];
            //last concat
            strcat(mov.num, &digit[1]);

        } else {
            if ('\0' != str[2]) {
                printf("Error, please enter coordinates in the following format:\n"
                       "  enter column row : A5\n");
                return mov;
            }
        }
    } else {
        printf("Error, please enter coordinates in the following format:\n"
               "  enter column row : A5\n");
        return mov;
    }
    return mov;
}

move get_move(char str[]) {
    move mov = {false, -1, -1};

    //check if I lang here when typing exit or rest
    if (strcmp(&str[0], "exit") == 0) {
        printf("Exit Game!\n");
        exit(1);
    } else if (strcmp(&str[0], "restart") == 0) {
        play_game();
        exit(1);
    } else {
        if (str[0] == '?') {
            mov.flag = true;
        }
        char copy[4] = {'\0'};
        if (mov.flag) {
            memcpy(copy, str + 2, strlen(str) + 1);
        } else {
            memcpy(copy, str, strlen(str) + 1);
        }

        //return a struct with alpha and num
        input_of_move result;
        result = separate_str(copy);
        mov.col = (int) result.alpha - 'A';
        if (result.alpha != '\0' && result.num[0] != '\0') {
            char *rest_of_char = "\0";
            errno = 0; // always reset errno
            double integer = strtod(result.num, &rest_of_char);
            if (rest_of_char == result.num) {
                printf("Error, please enter coordinates in the following format:\n"
                       "  enter column row : A5\n");
                return mov;
            } else if (*rest_of_char != '\0') {
                printf("Error, please enter coordinates in the following format:\n"
                       "  enter column row : A5\n");
                return mov;
            } else {
                if (errno) {
                    printf("Error, please enter coordinates in the following format:\n"
                           "  enter column row : A5\n");
                    return mov;
                } else {
                    if (integer >= 0) {
                        mov.row = (int) integer;
                    } else {
                        printf("Error, please enter coordinates in the following format:\n"
                               "  enter column row : A5\n");
                        return mov;
                    }
                }
            }
        } else {
            printf("Error, please enter coordinates in the following format:\n"
                   "  enter column row : A5\n");
            return mov;
        }
    }

    return mov;
}

move make_move() {
    bool input_correct = false;
    char input[10] = "\0";
    move crds = {NULL, -1, -1};

    while (input_correct != true) {
        printf("Enter <row> <column>: ");
        char *fgets_result = fgets(input, sizeof(input) / sizeof(char), stdin);
        while (fgets_result == NULL) {
            printf("Enter row column in the following format: \n"
                   "  enter column row :A5\n");
            fgets_result = fgets(input, sizeof(input) / sizeof(char), stdin);
        }
        //cut out "\n"
        int size = strcspn(input, "\n");
        char copy_of_input[size];
        memset(copy_of_input, '\0', size);
        for (int j = 0; j < size; j++) {
            copy_of_input[j] = input[j];
        }
        crds = get_move(copy_of_input);
        if (crds.col != -1 && crds.row != -1) {
            if (is_crd_valid(crds.col, crds.row) == true) {
                input_correct = true;
            } else {
                input_correct = false;
            }
        } else {
            input_correct = false;
        }
    }
    return crds;
}

bool play_recursive(cell game_brd[ROWS][COLS], cell hidden_brd[ROWS][COLS],
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
        hidden_brd[mov.row][mov.col].s = flagged;
        if (hidden_brd[mov.row][mov.col].ch == '*') {
            game_brd[mov.row][mov.col].ch = '*';
        } else {
            int cnt_of_mines = count_mines(mov.row, mov.col, hidden_brd);
            (*remaining_moves)--;
            game_brd[mov.row][mov.col].ngh_mines = cnt_of_mines;
            game_brd[mov.row][mov.col].s = opened;
            if (!cnt_of_mines) {
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
                                play_recursive(game_brd, hidden_brd, mines, mov, remaining_moves);
                            }
                        }
                    }
                }
            }
        }

    } else {
        if (hidden_brd[mov.row][mov.col].ch == '*' && hidden_brd[mov.row][mov.col].s != flagged) {
            game_brd[mov.row][mov.col].ch = '*';
            for (int i = 0; i < MINES; i++) {
                game_brd[mines[i][0]][mines[i][1]].ch = '*';
            }
            print_brd(game_brd);
            printf("\nYou lost!\n");
            return (true);
        } else {
            int cnt_of_mines = count_mines(mov.row, mov.col, hidden_brd);
            (*remaining_moves)--;
            game_brd[mov.row][mov.col].ngh_mines = cnt_of_mines;
            game_brd[mov.row][mov.col].s = opened;
            if (!cnt_of_mines) {
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
                                play_recursive(game_brd, hidden_brd, mines, mov, remaining_moves);
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}

