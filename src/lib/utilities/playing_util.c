/**
* Created by saif on 1/14/20.
*/
///

#include "playing_util.h"
#include "../validators/validators.h"
#include <stdbool.h>
#include <stdio.h>
#include "game_util.h"
#include "../converter/strtoint.h"
#include "../player/player.h"
#include "string_util.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

move extract_move(char *str) {
    move mov = {false, -1, -1, false, false};
    if (is_flag(&str[0])) {
        mov.flag = true;
    }
    int si = 0;
    while (str[si] != '\0') {
        if (isalpha(str[si])) {
            //TODO define highest char
            char ch = toupper(str[si++]);
            if (ch > 'Z') {
                printf("error, entered column greater than allowed\n");
            } else {
                mov.col = (int) ch - 'A';
            }
        }
        if (isdigit(str[si])) {
            mov.row = str_to_int(&str[si]);
            si += 2;
        }
        si++;
    }
    return mov;
}

move get_move(void) {
    bool valid = false;
    move mov = {NULL, -1, -1, false, false};
    char *command = "Enter <column> <row>";
    char *hint = "Enter <column> <row> [example A5]";
    while (valid != true) {
        char *input = get_input(command, hint);
        if (strcmp(input, "exit") == 0) {
            if (fwrite(&PLAYERX, sizeof(player), 1, GAME) != 1) {
                printf("Error, while saving data!");
            }
            fclose(GAME);
            exit(EXIT_SUCCESS);
        }
        if (strcmp(input, "restart") == 0) {
            mov.restart = true;
            break;
        }
        if (strcmp(input, "abort") == 0) {
            mov.abort = true;
            break;
        }
        mov = extract_move(input);
        if (mov.col != -1 && mov.row != -1) {
            if (is_crd_valid(mov.col, mov.row)) {
                valid = true;
            } else {
                printf("error, invalid input: %s\n", input);
                printf("Please, enter valid coordinates!\n");
            }
        } else {
            printf("error, invalid input: %s\n", input);
        }
    }
    return mov;
}
