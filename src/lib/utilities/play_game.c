/**
* Created by saif on 1/18/20.
*/
///

#include "play_game.h"
#include "playing_util.h"
#include "mines_util.h"
#include <stdbool.h>
#include <stdio.h>
#include "../boards/board.h"
#include "../boards/board_variables.h"
#include "../validators/validators.h"

void play_game() {
    bool game_over = false;
    // Actual Board and My Board
    cell hidden_brd[ROWS][COLS], game_brd[ROWS][COLS];
    int remaining_moves =  ROWS * COLS - MINES;
    //[x_crd,y_crd] coordinates of mines
    int mines[MINES][2];
    init_brds(hidden_brd, game_brd);
    place_mines(mines, hidden_brd);

    int executed_moves = 0;
    while (game_over == false) {
        print_brd(game_brd);
        int *coordinates = make_move();
        int x_crd = *(coordinates + 0);
        int y_crd = *(coordinates + 1);
        //when first move
        if (executed_moves == 0) {
            if (is_mine(x_crd, y_crd, hidden_brd) == true) {
                replace_mine(x_crd, y_crd, hidden_brd);
            }
        }
        executed_moves++;
        game_over = play_recursive(game_brd, hidden_brd, mines, x_crd, y_crd, &remaining_moves);
        if ((game_over == false) && (remaining_moves == 0)) {
            //TODO it prints you won when aborting the game
            printf("\nYou won !\n");
            game_over = true;
        }
    }
}