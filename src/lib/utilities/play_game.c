/**
* Created by saif on 1/18/20.
*/
///

#include "play_game.h"
#include <stdbool.h>
#include "../playing_board/board.h"
#include "mines_util.h"
#include <stdio.h>
#include "playing_util.h"
#include "../validators/validators.h"
void play_game(int board_rows, int board_cols, int num_of_mines) {
    bool game_over = false;
    // Actual Board and My Board
    char hidden_board[board_rows][board_cols], game_board[board_rows][board_cols];
    int remaining_moves = board_rows * board_cols - num_of_mines, x_crd, y_crd;
    //[x_crd,y_crd] coordinates of mines
    int mines[num_of_mines][2];
    init_boards(hidden_board, game_board);
    place_mines(mines, hidden_board);

    int executed_moves = 0;
    while (game_over == false) {
        printf("Current Status of Board:\n");
        print_board(game_board);
        int *coordinates = make_move(board_rows, board_cols);
        int x_crd = *(coordinates + 0);
        int y_crd = *(coordinates + 1);
        //when first move
        if (executed_moves == 0) {
            if (is_mine(x_crd, y_crd, hidden_board) == true) {
                replace_mine(x_crd, y_crd, hidden_board);
            }
        }
        executed_moves++;
        game_over = play_recursiv(game_board, hidden_board, mines, x_crd, y_crd, &remaining_moves);
        if ((game_over == false) && (remaining_moves == 0)) {
            //TODO it prints you won when aborting the game
            printf("\nYou won !\n");
            game_over = true;
        }
    }
    return;
}