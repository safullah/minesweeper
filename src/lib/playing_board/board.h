/**
* Created by saif on 1/10/20.
*/
///

#ifndef MINESPR_BOARD_H
#define MINESPR_BOARD_H

#define BEGINNER 0
#define INTERMEDIATE 1
#define ADVANCED 2
#define MAXSIDE 10
#define MAXMINES 20
#define MOVESIZE 526 // (25 * 25 - 99)
int SIDE ; // side length of the board
int MINES ; // number of mines on the board
int *get_cli_args(int argc, char *argv[]);
void generate_playing_board();
void chooseDifficultyLevel ();
void init_boards(char hidden_board[][MAXSIDE], char gaming_board[][MAXSIDE]);
void print_board(char **myBoard);


#endif //MINESPR_BOARD_H
