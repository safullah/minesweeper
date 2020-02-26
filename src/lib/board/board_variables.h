/** \file board_variables.h
 * \brief here I declare global variables needed for the game board, because I don't want to pass too many arguments to my functions
*
 * Created by saif on 1/19/20.
*/
///

#ifndef MINESPR_BOARD_VARIABLES_H
#define MINESPR_BOARD_VARIABLES_H
extern int ROWS;
extern int COLS;
extern int MINES;
extern int OPENED_CELLS;
extern int FLAGGED_CORRECT;
extern int FLAGGED_WRONG;
extern int FLAGGED_TOTAL;
int *convert_str_to_int(int argc, char *argv[]);
int *get_cli_args(int argc, char *argv[]);
char **extract_params(int argc, char *argv[]);
void show_params(int argc, char *argv[]);
void show_hint();
#endif //MINESPR_BOARD_VARIABLES_H
