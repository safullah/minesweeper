/**
* Created by saif on 1/19/20.
*/
///

#include "board_variables.h"
#include <stdlib.h>
#include "../validators/validators.h"
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <stdio.h>

int ROWS = 0;
int COLS = 0;
int MINES = 0;
int MAXCOLS = 20;
int OPENED_CELLS = 0;
int FLAGGED_CORRECT = 0;
int FLAGGED_WRONG = 0;
int FLAGGED_TOTAL = 0;

int *convert_str_to_int(char *str[], int count) {
    static int integers[2] = {0};
    char *rest_of_char;
    for (int i = 0; i < count; i++) {
        errno = 0; // always reset errno
        double integer = strtod(str[i], &rest_of_char);
        if (rest_of_char == str[i]) {
            printf("Error, type the size of board and number of mines in the following format:\n"
                   "  rowsxcols mines: 10x10 20");
            exit(1);
        } else if (*rest_of_char != '\0') {
            printf("Error, type the size of board and number of mines in the following format:\n"
                   "  rowsxcols mines: 10x10 20");
            exit(1);
        } else {
            if (errno) {
                printf("Error, type the size of board and number of mines in the following format:\n"
                       "  rowsxcols mines: 10x10 20");
                exit(1);
            } else {
                if (integer >= 0) {
                    integers[i] = (int) integer;
                } else {
                    printf("Error, enter positve values in the following format:\n"
                           "  rowsxcols mines: 10x10 20");
                    exit(1);
                }
            }
        }
    }
    return integers;
}

int *get_cli_args(int argc, char *argv[]) {
    is_argc_valid(argc);
    for (int i = 0; argv[1][i] != '\0'; i++) {
        argv[1][i] = (char) tolower(argv[1][i]);
    }

    char *cli_input[2] = {NULL};
    int index = 0;
    char *board_size = strtok(argv[1], "x");
    if (board_size) {
        cli_input[index] = board_size;
        index++;
        while (board_size != NULL) {
            if (index > 2) {
                break;
            }
            board_size = strtok(NULL, "x");
            if (board_size) {
                cli_input[index] = board_size;
            }
        }

        if (cli_input[1]) {
            static int cli_args[3] = {0};
            int *rows_cols = convert_str_to_int(cli_input, 2);
            cli_args[0] = *(rows_cols + 0);
            cli_args[1] = *(rows_cols + 1);

            char *mine_arr[1] = {NULL};
            mine_arr[0] = argv[2];
            int *mines = convert_str_to_int(mine_arr, 1);;
            int num_of_mines = mines[0];
            cli_args[2] = num_of_mines;

            return cli_args;
        } else {
            printf("Error, type the size of board and number of mines in the following format:\n"
                   "  rowsxcols mines: 10x10 20");
            exit(1);
        }

    } else {
        printf("Error, type the size of board and number of mines in the following format:\n"
               "  rowsxcols mines: 10x10 20");
        exit(1);
    }
}
