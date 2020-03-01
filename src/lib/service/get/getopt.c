/**
* Created by saif on 2/27/20.
*/
///

#include <stddef.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "../../board/board_variables.h"
#include "../../validators/validators.h"
#include "../../converter/strtoint.h"
#include "../set/setservice.h"
#include "../../utilities/game_util.h"
#include "../../player/player.h"
#include "./getservice.h"

void get__opt(int argc, char *argv[]) {
    optarg_check check = {false, "\0"};
    int option = 0;
    while ((option = getopt(argc, argv, ":r:c:m:n:hx")) != -1) {
        switch (option) {
            case 'r':
                check = is_option(optarg);
                if (!check.is_option) {
                    ROWS = str_to_int(optarg);
                    if (!is_row_valid(ROWS, optarg)) {
                        set_row();
                    }
                } else {
                    set_row();
                    call_set(check.option);
                }
                break;
            case 'c':
                check = is_option(optarg);
                if (!check.is_option) {
                    COLS = str_to_int(optarg);
                    if (!is_col_valid(COLS, optarg)) {
                        set_col();
                    }
                } else {
                    set_col();
                    call_set(check.option);
                }

                break;
            case 'm':
                check = is_option(optarg);
                if (!check.is_option) {
                    if (ROWS == 0 ) {
                        set_row();
                    }
                    if (COLS) {
                        set_col();
                    }
                    MINES = str_to_int(optarg);
                    if (!is_mine_valid(MINES, optarg)) {
                        set_mine();
                    }
                } else {
                    call_set(check.option);
                }
                break;
            case 'n':
                check = is_option(optarg);
                if (!check.is_option) {
                    if (strcpy(PLAYERX.name, optarg) == NULL) {
                        printf("error, your input for name %s\n", optarg);
                        strcpy(PLAYERX.name, get_name());
                    }
                } else {
                    strcpy(PLAYERX.name, get_name());
                    call_set(check.option);
                }

                break;
            case 'h':
                help();
                break;
            case ':':
                switch (optopt) {
                    case 'r':
                        set_row();
                        break;
                    case 'c':
                        set_col();
                        break;
                    case 'm':
                        set_mine();
                        break;
                    case 'n':
                        strcpy(PLAYERX.name, get_name());
                        break;
                    default:
                        break;
                }
            case '?':
                if (optopt != (int) 'r' && optopt != (int) 'c' && optopt != (int) 'm' && optopt != (int) 'n') {
                    printf("unknown option: %c\n", optopt);
                }
                break;
            default:
                break;
        }
    }
    for (; optind < argc; optind++) {
        printf("extra arguments: %s\n", argv[optind]);
    }
}

optarg_check is_option(char *arg) {
    optarg_check check = {false, "\0"};
    char *options[5] = {"-r", "-c", "-m", "-n", "-h"};
    for (int l = 0; l < 5; ++l) {
        if (strcmp(arg, options[l]) == 0) {
            check.is_option = true;
            check.option = options[l];
        }

    }
    return check;
}

void call_set(char *ch) {
    if (strcmp(ch, "-r") == 0) {
        set_row();
    } else if (strcmp(ch, "-c") == 0) {
        set_col();
    } else if (strcmp(ch, "-m") == 0) {
        set_mine();
    } else if (strcmp(ch, "-n") == 0) {
        strcpy(PLAYERX.name, get_name());
    } else if (strcmp(ch, "-h") == 0) {
        help();
    } else {
        //do nothing
    }
}
