/** \file main.c
 * \brief main function. */
#include "lib/utilities/game_util.h"
#include "lib/player/player.h"
#include "lib/utilities/string_util.h"
#include "lib/validators/validators.h"
#include "lib/service/setget/setget.h"
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <string.h>
#include <stdio.h>

/**
 * \brief main function
 * @param argc
 * @param argv my options via cli are -h (help), -n (name), -r (rows), -c (cols), -m (mines)
 * @return int
 */
int main(int argc, char *argv[]) {
    printf("\nstarting minesweeper ...\n");
    srand(time(NULL));
    get_opt(argc, argv);
    PLAYERX = init_player(PLAYERX.name);
    char db_path[PATH_MAX + 1] = {'\0'};
    char *target = "minespr_databank";
    char *result = realpath(target, db_path);
    if (!result) {
        strcpy(db_path, get_path(target));
    } else {
        strcat(db_path, "/");
    }
    char *player_file = concat_filename(PLAYERX.name);
    char *player_file_path = concat_filepath(db_path, player_file);
    bool existent = is_existent(db_path, player_file);
    char *answer = NULL;
    if (existent) {
        bool player_loaded = load_player(player_file_path);
        if (player_loaded) {
            if (PLAYERX.info.aborted) {
                char *question = "Load the aborted game? y/n";
                answer = get_answer(question);
                if ((strcmp(answer, "y") == 0 || strcmp(answer, "yes") == 0)) {
                    load_game_info();
                }
            }
        }
    }
    /*
    * in case rows, cols and mines were not defined via cli
    * and player decides not to load aborted game
    * then I have to make sure rows, cols and mines do not remain 0
    */
    if (ROWS == 0) {
        set_row();
    }
    if (COLS == 0) {
        set_col();
    }
    if (MINES == 0) {
        set_mine();
    }
    play_game(answer, player_file_path);

    printf("Error, while opening %s's file!\n"
           "exiting game\n", PLAYERX.name);
    exit(EXIT_FAILURE);
    return EXIT_SUCCESS;
}
