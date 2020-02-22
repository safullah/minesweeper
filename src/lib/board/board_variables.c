/**
* Created by saif on 1/19/20.
*/
///

#include "board_variables.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <stdio.h>

int ROWS = 0;
int COLS = 0;
int MINES = 0;
int OPENED_CELLS = 0;
int FLAGGED_CORRECT = 0;
int FLAGGED_WRONG = 0;
int FLAGGED_TOTAL = 0;

int *convert_str_to_int(char *str[], int count) {
    static int integer_arr[2] = {-1};
    char *rest_of_str;
    for (int i = 0; i < count; i++) {
        errno = 0; // always reset errno
        double integer = strtod(str[i], &rest_of_str);
        if (rest_of_str == str[i] || *rest_of_str != '\0' || errno) {
            break;
        } else {
            integer_arr[i] = (int) integer;
        }
    }
    return integer_arr;
}

int *get_cli_args(int argc, char *argv[]) {
    //<rows>X<cols> makes X to lower
    for (int i = 0; argv[1][i] != '\0'; i++) {
        argv[1][i] = (char) tolower(argv[1][i]);
    }
    char **param = extract_params(argc, argv);
    if (param[0] != NULL && param[1] != NULL) {
        //cli_args = [row, cols, mines]
        static int cli_args[3] = {0};
        int *rows_cols = convert_str_to_int(param, 2);
        cli_args[0] = *(rows_cols + 0);
        cli_args[1] = *(rows_cols + 1);
        char *mine_arr[1] = {NULL};
        mine_arr[0] = argv[2];
        int *mines = convert_str_to_int(mine_arr, 1);;
        int num_of_mines = mines[0];
        cli_args[2] = num_of_mines;
        return cli_args;
    } else {
        show_params(argc, argv);
        show_hint();
        exit(EXIT_FAILURE);
    }
}

char **extract_params(int argc, char *argv[]) {
    static char *param_arr[2] = {NULL};
    int cnt = 0;
    char *param = strtok(argv[1], "x");
    if (param) {
        param_arr[cnt] = param;
        cnt++;
        while (param != NULL) {
            if (cnt > 2) {
                break;
            }
            param = strtok(NULL, "x");
            if (param) {
                param_arr[cnt] = param;
            }
        }
    } else {
        show_params(argc, argv);
        show_hint();
        exit(EXIT_FAILURE);
    }

    return param_arr;
}

void show_params(int argc, char *argv[]) {
    printf("your parameters: ");
    for (int i = 0; i < argc; i++) {
        printf("%s ", argv[i]);
    }
}

void show_hint() {
    printf("\ncorrect format: <rows>x<cols> <mines> \nexample: ./minespr 10x10 20\n");
}
