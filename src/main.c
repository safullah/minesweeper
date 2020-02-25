#include "lib/utilities/game_util.h"
#include "lib/board/board_variables.h"
#include "lib/validators/validators.h"
#include "lib/utilities/string_util.h"

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    //amount of argc is 3
    if (argc != 3){
        show_params(argc, argv);
        show_hint();
        exit(EXIT_FAILURE);
    }
    int *cli_args = get_cli_args(argc, argv);
    ROWS = *(cli_args + 0);
    COLS = *(cli_args + 1);
    MINES = *(cli_args + 2);
    bool r_c_valid =is_rows_cols_valid(argc, argv);
    bool mines_valid = is_mines_valid(argc, argv);
    if (!r_c_valid || !mines_valid) {
        show_params(argc, argv);
        exit(EXIT_FAILURE);
    }
    play_game();
    return EXIT_SUCCESS;
}
