/**
* Created by saif on 1/14/20.
*/
///

#include "playing_util.h"
#include "../validators/validators.h"
#include <stdbool.h>
#include "adjacent_cells.h"
#include "../playing_board/board.h"
#include <stdio.h>
#include "mines_util.h"
#include <errno.h>
#include <string.h>
#include <stdlib.h>

int *retrieve_move(char *str[], int count) {
    //usr can also exit game by typing exit
    char *exit_game = "exit";
    char *restart_game = "restart";
    //or restart the game by typing restart
    static int coordinates[2] = {-1};
    char *rest_of_char;
    for (int i = 0; i < count; i++) {
        errno = 0; // always reset errno
        double integer = strtod(str[i], &rest_of_char);
        if (rest_of_char == str[i]) {
            if (rest_of_char == exit_game) {
                printf("Exit Game");
                exit(1);
            }
            if (str[i] == restart_game) {
                //TODO restart game and open one cell
            }
            printf("Error, please enter coordinates in the following format:\n"
                   "  row col: 1 5");
        } else if (*rest_of_char != '\0') {
            printf("Error, please enter coordinates in the following format:\n"
                   "  row col: 1 5");
        } else {
            if (errno) {
                printf("Error, please enter coordinates in the following format:\n"
                       "  row col: 1 5");
            } else {
                if (integer >= 0) {
                    coordinates[i] = (int) integer;
                } else {
                    printf("Error, enter positive coordinates in the following format:\n"
                           "  row col: 1 5");
                }
            }
        }
    }
    return coordinates;
}

void make_move(int *x_crd, int *y_crd, int rows, int cols) {
    bool input_correct;
    char *input[2] = {NULL};
    int *coordinates = 0;
    int size_of_input = sizeof(input) / sizeof(char);

    do {
        input_correct = true;
        printf("Enter row column: ");
        fgets(input, sizeof(input), stdin);
        coordinates = retrieve_move(input, size_of_input);
        if (*(coordinates + 0) != -1) {
            x_crd = *(coordinates + 0);
            y_crd = *(coordinates + 1);
            if (is_coordinate_valid(x_crd, y_crd, rows, cols)) {
                input_correct = false;
            }
        } else {
            input_correct = false;
        }
    } while (input_correct != true);
}

// A Recursive Fucntion to play the Minesweeper Game
bool playMinesweeperUtil(char myBoard[][MAXSIDE], char realBoard[][MAXSIDE],
                         int mines[][2], int row, int col, int *movesLeft) {

    // Base Case of Recursion
    if (myBoard[row][col] != '-') {
        return (false);
    }

    int i, j;

    // You opened a mine
    // You are going to lose
    if (realBoard[row][col] == '*') {
        myBoard[row][col] = '*';

        for (i = 0; i < MINES; i++) {
            myBoard[mines[i][0]][mines[i][1]] = '*';
        }

        print_board(myBoard);
        printf("\nYou lost!\n");
        return (true);
    } else {
        // Calculate the number of adjacent mines and put it
        // on the board
        int count = countAdjacentMines(row, col, mines, realBoard);
        (*movesLeft)--;

        myBoard[row][col] = count + '0';

        if (!count) {
            /*
            Recur for all 8 adjacent cells

                N.W   N   N.E
                    \ | /
                    \ | /
                W----Cell----E
                    / | \
                    / | \
                S.W   S  S.E

            Cell-->Current Cell (row, col)
            N --> North	 (row-1, col)
            S --> South	 (row+1, col)
            E --> East		 (row, col+1)
            W --> West		 (row, col-1)
            N.E--> North-East (row-1, col+1)
            N.W--> North-West (row-1, col-1)
            S.E--> South-East (row+1, col+1)
            S.W--> South-West (row+1, col-1)
            */

            //----------- 1st Neighbour (North) ------------

            // Only process this cell if this is a valid one
            if (isValid(row - 1, col) == true) {
                if (isMine(row - 1, col, realBoard) == false)
                    playMinesweeperUtil(myBoard, realBoard, mines, row - 1, col, movesLeft);
            }

            //----------- 2nd Neighbour (South) ------------

            // Only process this cell if this is a valid one
            if (isValid(row + 1, col) == true) {
                if (isMine(row + 1, col, realBoard) == false)
                    playMinesweeperUtil(myBoard, realBoard, mines, row + 1, col, movesLeft);
            }

            //----------- 3rd Neighbour (East) ------------

            // Only process this cell if this is a valid one
            if (isValid(row, col + 1) == true) {
                if (isMine(row, col + 1, realBoard) == false)
                    playMinesweeperUtil(myBoard, realBoard, mines, row, col + 1, movesLeft);
            }

            //----------- 4th Neighbour (West) ------------

            // Only process this cell if this is a valid one
            if (isValid(row, col - 1) == true) {
                if (isMine(row, col - 1, realBoard) == false) {

                    playMinesweeperUtil(myBoard, realBoard, mines, row, col - 1, movesLeft);
                }
            }

            //----------- 5th Neighbour (North-East) ------------

            // Only process this cell if this is a valid one
            if (isValid(row - 1, col + 1) == true) {
                if (isMine(row - 1, col + 1, realBoard) == false)
                    playMinesweeperUtil(myBoard, realBoard, mines, row - 1, col + 1, movesLeft);
            }

            //----------- 6th Neighbour (North-West) ------------

            // Only process this cell if this is a valid one
            if (isValid(row - 1, col - 1) == true) {
                if (isMine(row - 1, col - 1, realBoard) == false)
                    playMinesweeperUtil(myBoard, realBoard, mines, row - 1, col - 1, movesLeft);
            }

            //----------- 7th Neighbour (South-East) ------------

            // Only process this cell if this is a valid one
            if (isValid(row + 1, col + 1) == true) {
                if (isMine(row + 1, col + 1, realBoard) == false)
                    playMinesweeperUtil(myBoard, realBoard, mines, row + 1, col + 1, movesLeft);
            }

            //----------- 8th Neighbour (South-West) ------------

            // Only process this cell if this is a valid one
            if (isValid(row + 1, col - 1) == true) {
                if (isMine(row + 1, col - 1, realBoard) == false)
                    playMinesweeperUtil(myBoard, realBoard, mines, row + 1, col - 1, movesLeft);
            }
        }

        return (false);
    }
}

void play_game(int board_rows, int board_cols, int num_of_mines) {
    bool game_over = false;

    // Actual Board and My Board
    char hidden_board[board_rows][board_cols], game_board[board_rows][board_cols];
    int remaining_moves = board_rows * board_cols - num_of_mines, x, y;
    //[x,y] coordinates of mines
    int mines[num_of_mines][2];
    init_boards(hidden_board, game_board);
    place_mines(mines, hidden_board);

    int executed_moves = 0;
    while (game_over == false) {
        printf("Current Status of Board:\n");
        print_board(game_board);
        make_move(&x, &y, board_rows, board_cols);

        // This is to guarantee that the first move is
        // always safe
        // If it is the first move of the game
        if (executed_moves == 0) {
            // If the first move itself is a mine
            // then we remove the mine from that location
            if (isMine(x, y, hidden_board) == true) {
                replaceMine(x, y, hidden_board);
            }
        }

        executed_moves++;

        game_over = playMinesweeperUtil(game_board, hidden_board, mines, x, y, &remaining_moves);

        if ((game_over == false) && (remaining_moves == 0)) {
            //TODO it prints you won when aborting the game
            printf("\nYou won !\n");
            game_over = true;
        }
    }
    return;
}