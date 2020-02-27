/**
* Created by saif on 2/27/20.
*/
///

#include <stdbool.h>
#include <stdio.h>
#include "../../player/player.h"

/**
 * \brief loads an existent player
 *
 * load_player_game loads the data of a player
 * his name, played games, wins, losses and opened cells in total are displayed
 * if the player had an aborted game he is asked if he wants to continue the aborted game
 * if yes the aborted game is loaded
 *
 * @param game_brd              the game board is set the value of the aborted game, f player wishes to continue the aborted game
 * @param player_file_path      path to the file of player
 *
 * @return boolean      existent player loaded or not
 */
bool load_player(char *player_file_path) {
    bool loaded = false;
    GAME = fopen(player_file_path, "r");
    if ((fread(&PLAYERX, sizeof(player), 1, GAME) != 0)) {
        printf("Name: %s\n", PLAYERX.name);
        printf("Games: %d\n", PLAYERX.games);
        printf("Wins: %d\n", PLAYERX.wins);
        printf("Losses: %d\n", PLAYERX.losses);
        printf("Opened cells: %d\n", PLAYERX.cells);
        loaded = true;
    } else {
        printf("Error, while loading player!\n");
    }
    fclose(GAME);
    return loaded;
}

void load_game_info() {
    ROWS = PLAYERX.info.rows;
    COLS = PLAYERX.info.cols;
    MINES = PLAYERX.info.mines;
}
