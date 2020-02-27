/**
* Created by saif on 2/27/20.
*/
///

#include <stdbool.h>
#include <stdio.h>
#include "../../player/player.h"

bool set_board(cell game_brd[ROWS][COLS], char *player_file_path) {
    bool is_set = false;
    GAME = fopen(player_file_path, "r");
    fseek(GAME, sizeof(PLAYERX), SEEK_SET);
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            cell c;
            if (fread(&c, sizeof(cell), 1, GAME) == 1) {
                game_brd[i][j] = c;
            } else {
                printf("Error, while loading the game\n");
                goto goto_exit;
            }
        }
    }
    is_set = true;
    goto_exit :
    fclose(GAME);
    return is_set;
}
