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
#include "../converter/strtoint.h"
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

move get_move(char str[]) {
    move mov = {false, -1, -1};
    if (is_flag(&str[0])) {
        mov.flag = true;
    }
    int si = 0;
    while (str[si] != '\0') {
        if (isalpha(str[si])) {
            //TODO define highest char
            char ch = toupper(str[si++]);
            mov.col = (int) ch - 'A';
        }
        if (isdigit(str[si])) {
            mov.row = str_to_int(&str[si]);
            si += 2;
        }
        si++;
    }
    return mov;
}

char *get_input() {
    printf("Enter <row> <column>: ");
    char input[10] = "\0";
    char *result = fgets(input, sizeof(input) / sizeof(char), stdin);
    while (result == NULL) {
        printf("Enter column row in the following format: \n"
               "  enter column row :A5\n");
        result = fgets(input, sizeof(input) / sizeof(char), stdin);
    }
    //cut out "\n"
   static char copy[10];
    for (int j = 0; input[j] != '\n'; j++) {
        copy[j] = input[j];
    }
    return  copy;
}

move make_move() {
    bool valid = false;
    move mov = {NULL, -1, -1};
    while (valid != true) {
        char *input = get_input();
        if (strcmp(input, "exit") == 0) {
            exit(1);
        }
        if (strcmp(input, "restart") == 0) {
            bool restart = true;
            play_game(restart);
            //TODO open one cell
        }

        mov = get_move(input);
        if (mov.col != -1 && mov.row != -1) {
            if (is_crd_valid(mov.col, mov.row) == true) {
                valid = true;
            } else {
                printf("Please, enter valid coordinates\n");
                valid = false;
            }
        } else {
            printf("Error, please enter coordinates in the following format:\n"
                   "  enter column row : A5\n");
            valid = false;
        }
    }
    return mov;
}
