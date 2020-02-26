/** \file board_variable.c
 * \brief variable which I need for the game board are initialized here
 *
* Created by saif on 1/19/20.
*/
///

#include "board_variables.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdbool.h>

int ROWS = 0;
int COLS = 0;
int MINES = 0;
int OPENED_CELLS = 0;
int FLAGGED_CORRECT = 0;
int FLAGGED_WRONG = 0;
int FLAGGED_TOTAL = 0;

/**
 * \brief converts string into int
 *
 * elements of string array are converted to int
 * if the passed
 * @param str
 * @param count
 * @return
 */
int *convert_str_to_int(int argc, char *argv[]) {
    static int integer_arr[3] = {-1};
    char **params = extract_params(argc, argv);
    int cnt = 0;
    while(params[++cnt] != NULL);
    params[cnt] = argv[argc - 1];
    char *rest_of_str;
    for (int i = 0; i < cnt+1; i++) {
        errno = 0; // always reset errno
        double integer = strtod(params[i], &rest_of_str);
        if (rest_of_str == params[i] || *rest_of_str != '\0' || errno) {
            break;
        } else {
            integer_arr[i] = (int) integer;
        }
    }
    for (int j = 0; j < (int)(sizeof(integer_arr)/sizeof(integer_arr[0])); j++) {
        if (integer_arr[j] == -1) {
            show_params(argc, argv);
            show_hint();
            exit(EXIT_FAILURE);
        }
    }
    return integer_arr;
}

int *get_cli_args(int argc, char *argv[]) {
    //<rows>X<cols> makes X to lower
    for (int i = 0; argv[1][i] != '\0'; i++) {
        argv[1][i] = (char) tolower(argv[1][i]);
    }
    //cli_args = [row, cols, mines]
    static int cli_args[3] = {0};
    int *params = convert_str_to_int(argc, argv);
    cli_args[0] = *(params + 0);
    cli_args[1] = *(params + 1);
    cli_args[2] = *(params + 2);
    return cli_args;
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
