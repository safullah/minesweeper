/** \file
 *  \brief player.c
* Created by saif on 2/11/20.
*/
///

#include "player.h"
#include "../validators/validators.h"
#include "../utilities/playing_util.h"
#include "../service/set/setparam.h"
#include "../utilities/string_util.h"
#include <stdio.h>
#include <string.h>
#include <dirent.h>

/**
 * \brief gets the name of the player when starting the game
 *
 * with the function \c get_input() the name is retrieved
 * max length of name is set to 50 chars
 *
 * @return char * name
 */
char *get_name(void) {
    char *command = "Enter your <name>";
    char *hint = command;
    char *input = get_input(command, hint);
    return input;
}

/**
 * \brief initializes a player when starting the game
 *
 * Information of game \c info are set such as rows and cols of game board, the amount of mines and if the game is aborted
 * player \c p is initialized  via \c get_name() the name is set
 *
 * @param player_name
 * @return player
 */
player init_player(char *player_name) {
    game info = {0, 0, 0, false};
    player p = {"\0", 0, 0, 0, 0, info};
    if (player_name == NULL){
        strcpy(p.name, get_name());
    }
    return p;
}

/**
 * \brief is player in databank
 *
 * \c searches the databank for \c player_file
 *
 * @param db_path       path to databank
 * @param player_file   name of the players file
 * @return boolean      does the player exist in databank or nor
 */
bool is_existent(char *db_path, char *player_file) {
    bool exists = false;
    DIR *databank;
    struct dirent *dir;
    if ((databank = opendir(db_path)) == NULL) {
        printf("Error, cannot open directory: %s\n", db_path);
        exit(EXIT_FAILURE);
    }
    if (databank) {
        while ((dir = readdir(databank)) != NULL) {
            size_t name_len = strcspn(dir->d_name, "\0");
            char file_name[50];
            memset(file_name, '\0', sizeof(file_name)/sizeof(file_name[0]));
            strncpy(file_name, dir->d_name, name_len);
            if (strcmp(file_name, player_file) == 0) {
                exists = true;
                break;
            }
        }
    }
    closedir(databank);
    return exists;

}

/**
 * \brief gets the answer to the question Load the aborted game? y/n
 *
 * The player can type yes, no or y,n
 * capital letter and small letter are both accepted
 *
 * @param str       this the question the player is being asked for
 * @return char *answer     y or n
 */
char *get_answer(char *str) {
    bool is_correct = false;
    char *answer = "\0";
    while (!is_correct) {
        answer = get_input(str, str);
        is_correct = is_answer(answer);
    }
    return answer;
}

//TODO delete in case I don't need it
void free_mem(char **arr, int size) {
    for (int i = 0; i < size; i++) {
        free(arr[i]);
    }
    free(arr);
}
