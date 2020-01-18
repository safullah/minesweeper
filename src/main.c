// A C++ Program to Implement and Play Minesweeper 

#include "lib/utilities/playing_util.h"
#include "lib/playing_board/board.h"
#include "lib/validators/validators.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    // ./minespr 10x10 20

    int *cli_args = get_cli_args(argc, argv);
    const int board_rows = *(cli_args + 0);
    const int board_cols = *(cli_args + 1);
    const int num_of_mines = *(cli_args + 2);

    play_game(board_rows, board_cols, num_of_mines);

    return EXIT_SUCCESS;
}
