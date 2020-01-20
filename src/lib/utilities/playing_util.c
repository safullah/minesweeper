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
    }
    return mov;
}

move get_move(char str[]) {
    move mov = {false, '\0', -1};
    char *split = strtok(str, " ");
    char *flag = "?";
    if (strcmp(split, flag) == 0) {
        mov.flag = true;
    } else {
        //check if I lang here when typing exit or rest
        if (strcmp(split, "exit") == 0) {
            printf("Exit Game!\n");
            exit(1);
        } else if (strcmp(split, "restart") == 0) {
            //TODO restart game
            exit(1);
        } else {
            //return a struct with alpha and num
            input_of_move result;
            result = separate_str(str);
            mov.col = result.alpha;
            if (result.alpha != '\0' && result.num[0] != '\0') {
                char *rest_of_char;
                errno = 0; // always reset errno
                double integer = strtod(result.num, &rest_of_char);
                if (rest_of_char == result.num) {
                    printf("Error, please enter coordinates in the following format:\n"
                           "  enter row column: 1 5\n");
                    return mov;
                } else if (*rest_of_char != '\0') {
                    printf("Error, please enter coordinates in the following format:\n"
                           "  enter row column: 1 5\n");
                    return mov;
                } else {
                    if (errno) {
                        printf("Error, please enter coordinates in the following format:\n"
                               "  enter row column: 1 5\n");
                        return mov;
                    } else {
                        if (integer >= 0) {
                            mov.row = (int) integer;
                        } else {
                            printf("Error, enter positive coordinates in the following format:\n"
                                   "  enter row column: 1 5\n");
                            return mov;
                        }
                    }
                }
            } else {
                printf("Error, please enter coordinates in the following format:\n"
                       "  enter row col: 1 5\n");
                return mov;
            }
        }

    }
    return mov;
}

int *make_move() {
    bool input_correct = false;
    char input[10] = "\0";
    move crds = {NULL, '\0', -1};
    int col = -1;

    while (input_correct != true) {
        printf("Enter <row> <column>: ");
        char *fgets_result = fgets(input, sizeof(input) / sizeof(char), stdin);
        while (fgets_result == NULL) {
            printf(" you land here Enter row column in the following format: \n"
                   "  enter row column: 1 5\n");
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
        if (crds.col != '\0' && crds.row != -1) {
            col = (int) crds.col - 'A';
            if (is_crd_valid(col, crds.row) == true) {
                input_correct = true;
            } else {
                input_correct = false;
            }
        } else {
            input_correct = false;
        }
    }

    static int coordinates[2] = {0};
    coordinates[0] = crds.row;
    coordinates[1] = col;
    return coordinates;
}

bool play_recursive(cell game_brd[ROWS][COLS], cell hidden_brd[ROWS][COLS],
                    int mines[][2], int x_crd, int y_crd, int *remaining_moves) {

    if (game_brd[x_crd][y_crd].ch != '-') {
        return (false);
    }
    //stepped on mine
    if (hidden_brd[x_crd][y_crd].ch == '*') {
        game_brd[x_crd][y_crd].ch = '*';
        for (int i = 0; i < MINES; i++) {
            game_brd[mines[i][0]][mines[i][1]].ch = '*';
        }
        print_brd(game_brd);
        printf("\nYou lost!\n");
        return (true);
    } else {
        int cnt_of_mines = count_mines(x_crd, y_crd, hidden_brd);
        (*remaining_moves)--;
        game_brd[x_crd][y_crd].ngh_mines = cnt_of_mines;
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
                    if (is_cell_valid(x_crd + neighbors[i][j], y_crd + neighbors[i][j + 1]) == true) {
                        if (is_mine(x_crd + neighbors[i][j], y_crd + neighbors[i][j + 1], hidden_brd) == false)
                            play_recursive(game_brd, hidden_brd, mines, x_crd + neighbors[i][j],
                                           y_crd + neighbors[i][j + 1], remaining_moves);
                    }
                }
            }
        }
        return false;
    }
}

