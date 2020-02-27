/** \file
 * \brief main function. */
#include "lib/utilities/game_util.h"
#include "lib/player/player.h"
#include "lib/service/get/getservice.h"
#include "lib/utilities/string_util.h"
#include "lib/service/set/setservice.h"
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <string.h>

int main(int argc, char *argv[]) {
    srand(time(NULL));
    get_opt(argc, argv);
    PLAYERX = init_player(PLAYERX.name);
    char db_path[PATH_MAX + 1] = {'\0'};
    char *target = "minespr_databank";
    char *result = realpath(target, db_path);
    if (!result) {
        strcpy(db_path, get_path(target));
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
                /*
                 * in case rows, cols and mines were not defined via cli
                 * and player decides not to load aborted game
                 * then I have to make sure rows, cols and mines do not remain 0
                 */
                if ((strcmp(answer, "n") == 0 || strcmp(answer, "no") == 0)) {
                    if (ROWS == 0){
                        set_row();
                    }
                    if (COLS == 0) {
                        set_col();
                    }
                    if (MINES == 0) {
                        set_mine();
                    }
                } else {
                    load_game_info();
                }
            }
        }
    }
    play_game(answer, player_file_path);
    //I need to get back here
    return EXIT_SUCCESS;
}
