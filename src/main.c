#include "lib/utilities/play_game.h"
#include "lib/boards/board_variables.h"
#include "lib/validators/validators.h"

#include <stdlib.h>

int main(int argc, char *argv[]) {
    int *cli_args = get_cli_args(argc, argv);
    ROWS = *(cli_args + 0);
    COLS = *(cli_args + 1);
    MINES = *(cli_args + 2);
    is_rows_cols_valid();
    is_mines_valid();
    play_game();

    return EXIT_SUCCESS;
}
