/**
* Created by saif on 1/10/20.
*/
///

#include "board.h"
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include "../validators/validators.h"
#include <string.h>
#include <ctype.h>
#include <errno.h>

int *convert_str_to_int(char *str[], int count) {
    static int integers[2] = {0};
    char *rest_of_char;
    for (int i = 0; i < count; i++) {
        errno = 0; // always reset errno
        double integer = strtod(str[i], &rest_of_char);
        if (rest_of_char == str[i]) {
            printf("Error, type the size of board and number of mines in the following format:\n"
                   "  rowsxcols mines: 10x10 20");
            exit(1);
        } else if (*rest_of_char != '\0') {
            printf("Error, type the size of board and number of mines in the following format:\n"
                   "  rowsxcols mines: 10x10 20");
            exit(1);
        } else {
            if (errno) {
                printf("Error, type the size of board and number of mines in the following format:\n"
                       "  rowsxcols mines: 10x10 20");
                exit(1);
            } else {
                if (integer >= 0) {
                    integers[i] = (int) integer;
                } else {
                    printf("Error, enter positve values in the following format:\n"
                           "  rowsxcols mines: 10x10 20");
                    exit(1);
                }
            }
        }
    }
    return integers;
}

int *get_cli_args(int argc, char *argv[]) {

    is_argc_valid(argc);

    for (int i = 0; argv[1][i] != '\0'; i++) {
        argv[1][i] = (char) tolower(argv[1][i]);
    }

    char *cli_input[2] = {NULL};
    int index = 0;
    char *board_size = strtok(argv[1], "x");
    if (board_size) {
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

        if (cli_input[1]) {
            int *rows_cols = convert_str_to_int(cli_input, 2);
            int board_rows = rows_cols[0];
            int board_cols = rows_cols[1];

            char *mine_arr[1] = {NULL};
            mine_arr[0] = argv[2];
            int *mines = convert_str_to_int(mine_arr, 1);;
            int num_of_mines = mines[0];

            is_rows_cols_valid(board_rows, board_cols);
            is_mines_valid(num_of_mines, board_rows, board_cols);

            static int cli_args[3] = {0};
            cli_args[0] = board_rows;
            cli_args[1] = board_cols;
            cli_args[2] = num_of_mines;

            return cli_args;
        } else {
            printf("Error, type the size of board and number of mines in the following format:\n"
                   "  rowsxcols mines: 10x10 20");
            exit(1);
        }

    } else {
        printf("Error, type the size of board and number of mines in the following format:\n"
               "  rowsxcols mines: 10x10 20");
        exit(1);
    }
}

// A Function to init_boards the game
void init_boards(char hidden_board[][MAXSIDE], char gaming_board[][MAXSIDE]) {
    // Initiate the random number generator so that
    // the same configuration doesn't arises
    srand(time(NULL));

    // Assign all the cells as mine-free
    for (int i = 0; i < SIDE; i++) {
        for (int j = 0; j < SIDE; j++) {
            gaming_board[i][j] = hidden_board[i][j] = '-';
        }
    }

    return;
}

// A Function to print the current gameplay board
void print_board(char **myBoard) {
    int i, j;

    printf("   ");

    for (i = 0; i < SIDE; i++) {
        printf("%d  ", i);
    }

    printf("\n");

    for (i = 0; i < SIDE; i++) {
        printf("%d ", i);

        for (j = 0; j < SIDE; j++) {
            printf(" %c ", myBoard[i][j]);
        }
        printf("\n");
    }
    return;
}


/*
void generate_playing_boatd(char myBoard[][MAXSIDE])
{
    int i, j;

    printf ("    ");

    for (i=0; i<SIDE; i++)
        printf ("%d ", i);

    printf ("\n\n");

    for (i=0; i<SIDE; i++)
    {
        printf ("%d   ", i);

        for (j=0; j<SIDE; j++)
            printf ("%c ", myBoard[i][j]);
        printf ("\n");
    }
    return;

    typedef struct cell {
    char cell_char[3];
    bool state;
    bool mine;
    int neigbor_mines;

} Cell;

Cell cell00 = {"|x|", false, false, 0};
Cell cell01 = {"|x|", false, false, 0};

Cell board [10][10] = {
        {cell00, cell01}
};
for (int i = 0; i < 1; i++) {
for (int j = 0; j < 2; j++) {
printf(board[i][j].cell_char);
}
}
}
 */
