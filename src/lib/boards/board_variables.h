/**
* Created by saif on 1/19/20.
*/
///

#ifndef MINESPR_BOARD_VARIABLES_H
#define MINESPR_BOARD_VARIABLES_H
int ROWS;
int COLS;
int MINES;
int *convert_str_to_int(char *str[], int count);
int *get_cli_args(int argc, char *argv[]);
#endif //MINESPR_BOARD_VARIABLES_H
