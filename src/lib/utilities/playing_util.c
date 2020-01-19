/**
* Created by saif on 1/14/20.
*/
///

#include "playing_util.h"
#include "../validators/validators.h"
#include <stdbool.h>
#include "neighbor_cells.h"
#include "../playing_board/board.h"
#include <stdio.h>
#include "mines_util.h"
#include <errno.h>
#include <string.h>
#include <stdlib.h>

int *retrieve_move(char *str, int count) {
    //usr can also exit game by typing exit
    static int coordinates[2] = {-1};
    char *exit_game = "exit";
    char *restart_game = "restart";

    //first split than convert if necessary
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
                           "  enter row column: 1 5");
                    return coordinates;
                } else if (*rest_of_char != '\0') {
                    printf("Error, please enter coordinates in the following format:\n"
                           "  enter row column: 1 5");
                    return coordinates;
                } else {
                    if (errno) {
                        printf("Error, please enter coordinates in the following format:\n"
                               "  enter row column: 1 5");
                        return coordinates;
                    } else {
                        if (integer >= 0) {
                            coordinates[i] = integer;
                        } else {
                            printf("Error, enter positive coordinates in the following format:\n"
                                   "  enter row column: 1 5");
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
        if (split == exit_game) {
            printf("Exit Game!");
            exit(1);
        }
        if (split == restart_game) {
            //TODO restart game
            exit(1);
        } else {
            printf("Error, please enter coordinates in the following format:\n"
                   "  enter row col: 1 5");
            return coordinates;
        }
    }
}

int *make_move(int rows, int cols) {
    bool input_correct = false;
    char *input = "\0";
    int *coordinates = 0;
    int size_of_input = sizeof(input) / sizeof(char);

    while (input_correct != true) {
        printf("Enter row column: ");
        while (fgets(input, sizeof(input), stdin) == NULL) {
            printf("Enter row column in the following format: \n"
                   "  enter row column: 1 5 ");
            fgets(input, sizeof(input), stdin);
        }

        coordinates = retrieve_move(input, size_of_input);
        if (coordinates[0] != -1) {
            if (is_coordinate_valid(coordinates[0], coordinates[1], rows, cols)) {
                input_correct = true;
            } else {
                input_correct = false;
            }
        } else {
            input_correct = false;
        }
    }
    return coordinates;
}

    bool play_recursive(char game_brd[][MAXSIDE], char hidden_brd[][MAXSIDE],
                        int mines[][2], int row, int col, int *remaining_moves) {

        if (game_brd[row][col] != '-') {
            return (false);
        }
        //stepped on mine
        if (hidden_brd[row][col] == '*') {
            game_brd[row][col] = '*';
            for (int i = 0; i < MINES; i++) {
                game_brd[mines[i][0]][mines[i][1]] = '*';
            }
            print_brd(game_brd);
            printf("\nYou lost!\n");
            return (true);
        } else {
            int cnt_of_mines = count_mines(row, col, hidden_brd);
            (*remaining_moves)--;
            game_brd[row][col] = cnt_of_mines + '0';
            if (!cnt_of_mines) {
                /*
                {-1,-1}, {-1, 0}, {-1, 1},
                  { 0,-1}, home { 0, 1},
                { 1,-1}, { 1, 0}, { 1, 1}
                */
                //{-1, 0}
                if (is_cell_valid(row - 1, col) == true) {
                    if (is_mine(row - 1, col, hidden_brd) == false)
                        play_recursive(game_brd, hidden_brd, mines, row - 1, col, remaining_moves);
                }
                //{ 1, 0}
                if (is_cell_valid(row + 1, col) == true) {
                    if (is_mine(row + 1, col, hidden_brd) == false)
                        play_recursive(game_brd, hidden_brd, mines, row + 1, col, remaining_moves);
                }
                //{ 0,-1}
                if (is_cell_valid(row, col + 1) == true) {
                    if (is_mine(row, col + 1, hidden_brd) == false)
                        play_recursive(game_brd, hidden_brd, mines, row, col + 1, remaining_moves);
                }
                //{-1, 1}
                if (is_cell_valid(row, col - 1) == true) {
                    if (is_mine(row, col - 1, hidden_brd) == false) {

                        play_recursive(game_brd, hidden_brd, mines, row, col - 1, remaining_moves);
                    }
                }
                //{-1,-1}
                if (is_cell_valid(row - 1, col + 1) == true) {
                    if (is_mine(row - 1, col + 1, hidden_brd) == false)
                        play_recursive(game_brd, hidden_brd, mines, row - 1, col + 1, remaining_moves);
                }
                //{ 1, 1}
                if (is_cell_valid(row - 1, col - 1) == true) {
                    if (is_mine(row - 1, col - 1, hidden_brd) == false)
                        play_recursive(game_brd, hidden_brd, mines, row - 1, col - 1, remaining_moves);
                }
                //{ 1,-1}
                if (is_cell_valid(row + 1, col + 1) == true) {
                    if (is_mine(row + 1, col + 1, hidden_brd) == false)
                        play_recursive(game_brd, hidden_brd, mines, row + 1, col + 1, remaining_moves);
                }

                if (is_cell_valid(row + 1, col - 1) == true) {
                    if (is_mine(row + 1, col - 1, hidden_brd) == false)
                        play_recursive(game_brd, hidden_brd, mines, row + 1, col - 1, remaining_moves);
                }
            }

            return (false);
        }
    }

