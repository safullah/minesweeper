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
 * Parameters of argv, which need to be converted are copied to \c params then they are converted to int.
 * In case of success \interger_arr is returned else exit()
 *
 * @param argc
 * @param argv
 * @return  static int integer_array[3]     returns rows, cols and mines
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

/**
 * \brief gets cli arguments
 *
 * Letters are made to lower case.
 * Parameter are converted and saved an int array
 *
 * @param argc
 * @param argv
 * @return int array[3]         returns rows, cols and mines
 */
int *get_cli_args(int argc, char *argv[]) {
    //makes X to lower <rows>X<cols>
    for (int i = 0; argv[1][i] != '\0'; i++) {
        if (isalpha(argv[1][i])) {
            argv[1][i] = (char) tolower(argv[1][i]);
        }
    }
    //cli_args = [row, cols, mines]
    static int cli_args[3] = {0};
    int *params = convert_str_to_int(argc, argv);
    cli_args[0] = *(params + 0);
    cli_args[1] = *(params + 1);
    cli_args[2] = *(params + 2);
    return cli_args;
}

/**
 * \brief extracts rows and cols
 *
 * The mandatory format typing rows and cols is: <row>x<cols>
 * Only in this format the parameters are accepted. \c extract_params cuts the string in two
 * in order to make the conversion of string to int possible
 *
 * @param argc
 * @param argv
 * @return char *array[2]       return rows and cols as strings
 */
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

/**
 * \brief shows the parameter with which the game was started
 *
 * \c show_params iterates over argv and prints all parameters
 * This function is called in cases of wrong input.
 * The user sees his input and should help to recognize his mistake
 *
 * @param argc
 * @param argv
 */
void show_params(int argc, char *argv[]) {
    printf("your parameters: ");
    for (int i = 0; i < argc; i++) {
        printf("%s ", argv[i]);
    }
}

/**
 * \brief prints a hint to the user how to start the game correctly
 */
void show_hint() {
    printf("\ncorrect format: <rows>x<cols> <mines> \nexample: ./minespr 10x10 20\n");
}
