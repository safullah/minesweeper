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

void *get_opt(int argc, char *argv[]) {
    int option = 0;
    bool explain_params;
    while ((option = getopt(argc, argv, ":r:c:m:n:hx")) != -1){
        switch (option) {
            case 'r':
                ROWS = str_to_int(optarg);
                if (!is_row_valid(ROWS, optarg)){
                    set_row();
                }
                break;
            case 'c':
                COLS = str_to_int(optarg);
                if (!is_col_valid(COLS, optarg)){
                    set_col();
                }
                break;
            case 'm':
                MINES = str_to_int(optarg);
                if (!is_mine_valid(MINES, optarg)){
                    set_mine();
                }
                break;
            case 'n':
                if (strcpy(PLAYERX.name, optarg) == NULL) {
                    printf("error, your input for name %s\n", optarg);
                    strcpy(PLAYERX.name, get_name());
                }
                break;
            case 'h':
                explain_params = true;
                help(explain_params);
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
                printf("unknown option: %c\n", optopt);
                break;
            default:
                break;
        }
    }
    for(; optind < argc; optind++){
        printf("extra arguments: %s\n", argv[optind]);
    }
}

