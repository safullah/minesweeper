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

int *get_move(char str[], int count) {
    static int coordinates[2] = {-1};
    char *string[2] = {NULL};
    int index = 0;
    char *split = strtok(str, " ");
    if (split) {
        string[index] = split;
        index++;
        while (split != NULL) {
            if (index > 2) {
                break;
            }
            split = strtok(NULL, " ");
            if (split) {
                string[index] = split;
            }
        }
        if (string[1]) {
            //converting string to int
            char *rest_of_char;
            for (int i = 0; i < count; i++) {
                errno = 0; // always reset errno
                int integer = strtod(string[i], &rest_of_char);
                if (rest_of_char == string[i]) {
                    printf("Error, please enter coordinates in the following format:\n"
                           "  enter row column: 1 5\n");
                    return coordinates;
                } else if (*rest_of_char != '\0') {
                    printf("Error, please enter coordinates in the following format:\n"
                           "  enter row column: 1 5\n");
                    return coordinates;
                } else {
                    if (errno) {
                        printf("Error, please enter coordinates in the following format:\n"
                               "  enter row column: 1 5\n");
                        return coordinates;
                    } else {
                        if (integer >= 0) {
                            coordinates[i] = integer;
                        } else {
                            printf("Error, enter positive coordinates in the following format:\n"
                                   "  enter row column: 1 5\n");
                            return coordinates;
                        }
                    }
                }
            }
            return coordinates;
        } else {
            printf("Error, please enter coordinates in the following format:\n"
                   "  enter row col: 1 5");
            return coordinates;
        }
    } else {
        if (strcmp(split, "exit") == 0) {
            printf("Exit Game!\n");
            exit(1);
        }
        if (strcmp(split, "restart") == 0) {
            //TODO restart game
            exit(1);
        } else {
            printf("Error, please enter coordinates in the following format:\n"
                   "  enter row col: 1 5\n");
            return coordinates;
        }
    }
}

int *make_move() {
    bool input_correct = false;
    char input[10] = "\0";
    int *crds = 0;

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
        crds = get_move(copy_of_input, 2);
        if (*(crds + 0) != -1 && *(crds + 1) != -1) {
            if (is_crd_valid(*(crds + 0), *(crds + 1))) {
                input_correct = true;
            } else {
                input_correct = false;
            }
        } else {
            input_correct = false;
        }
    }

    static int coordinates[2] = {0};
    coordinates[0] = *(crds + 0);
    coordinates[1] = *(crds + 1);
    return coordinates;
}

bool play_recursive(char game_brd[ROWS][COLS], char hidden_brd[ROWS][COLS],
                    int mines[][2], int x_crd, int y_crd, int *remaining_moves) {

    if (game_brd[x_crd][y_crd] != '-') {
        return (false);
    }
    //stepped on mine
    if (hidden_brd[x_crd][y_crd] == '*') {
        game_brd[x_crd][y_crd] = '*';
        for (int i = 0; i < MINES; i++) {
            game_brd[mines[i][0]][mines[i][1]] = '*';
        }
        print_brd(game_brd);
        printf("\nYou lost!\n");
        return (true);
    } else {
        int cnt_of_mines = count_mines(x_crd, y_crd, hidden_brd);
        (*remaining_moves)--;
        game_brd[x_crd][y_crd] = cnt_of_mines + '0';
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

