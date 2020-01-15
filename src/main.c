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
    argc_is_valid(argc);
// TODO make a function of retrieving raws and cols
// TODO think about how to secure wrong input
    char *cli_input[50] = {NULL};
    int index = 0;
    int board_rows_cols[2] = {0};

    for (int i = 0; argv[1][i] != '\0'; i++) {
        argv[1][i] = (char) tolower(argv[1][i]);
    }

    char *board_size = strtok(argv[1], "x");
    cli_input[index] = board_size;
    index++;
    while (board_size != NULL) {

        if (index > 2) {
            break;
        }
        board_size = strtok(NULL, "x");
        if (board_size) {
            cli_input[index] = board_size;
        }
    }
    char *rest_of_char;
    for (int i = 0; i < 2; i++) {
        errno = 0; // Always reset errno
        double size_of_board = strtod(cli_input[i], &rest_of_char);
        // Check if conversion was successful
        if (rest_of_char == cli_input[i]) {
            fprintf(stderr, "Error, type the size of board in the following fomat!\n"
                            "rowxcols: 10x10\n");
        } else if (*rest_of_char != '\0') {
            fprintf(stderr, "Error, type the size of board in the following fomat!\n"
                            "rowxcols: 10x10\n");
        } else {
            if (errno) {
                fprintf(stderr, "Error, type the size of board in the following fomat!\n"
                                "rowxcols: 10x10\n");
            } else {
                board_rows_cols[i] = (int) size_of_board;
            }
        }
    }
    int num_of_mines = 0;
    int check_of_sscanf = sscanf(argv[2], "%d", &num_of_mines);
    if (check_of_sscanf != 1) {
        fprintf(stderr, "Error, please enter a valid number for the amount of mines");
        exit(1);
    }

    int board_rows = board_rows_cols[0];
    int board_cols = board_rows_cols[1];

    if (num_of_mines > (board_rows * board_cols)) {
        fprintf(stderr, "Error, please enter less mines than the numbe of fields");
    }
    playMinesweeper();

    return EXIT_SUCCESS;
}
