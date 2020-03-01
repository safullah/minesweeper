/** \file player.c
 *  \brief functions for player
* Created by saif on 2/11/20.
*/
///

#include "player.h"
#include "../validators/validators.h"
#include "../utilities/string_util.h"
#include <stdio.h>
#include <string.h>
#include <dirent.h>

/**
 * \brief gets the name of the player when starting the game.
 *
 * With the function \c get_input() the name is retrieved
 * Max length of name is set to 50 chars.
 *
 * @return char * name
 */
char *get_name(void) {
    char *command = "Enter your name";
    char *hint = command;
    char *input = get_input(command, hint);
    return input;
}

/**
 * \brief initializes a player when starting the game
 * Information of an aborted game are saved in game \c info
 *
 * @param player_name
 * @return player
 */
player init_player(char *player_name) {
    game info = {0, 0, 0, false};
    player p = {"\0", 0, 0, 0, 0, info};
    strcpy(p.name, player_name);
    if (strcmp(p.name, "") == 0  ){
        strcpy(p.name, get_name());
    }
    return p;
}

/**
 * \brief finds out whether file is in path/ or not
 * Searches path/ and all subdirectories for \c file
 *
 * @param path       path to a directory
 * @param file      name of the file
 * @return boolean  does file exist in path/ or not
 */
bool is_existent(char *path, char *file) {
    bool exists = false;
    DIR *directory;
    struct dirent *dir;
    if ((directory = opendir(path)) == NULL) {
        printf("Error, cannot open directory: %s\n", path);
        exit(EXIT_FAILURE);
    }
    if (directory) {
        while ((dir = readdir(directory)) != NULL) {
            size_t name_len = strcspn(dir->d_name, "\0");
            char file_name[50];
            memset(file_name, '\0', sizeof(file_name));
            strncpy(file_name, dir->d_name, name_len);
            if (strcmp(file_name, file) == 0) {
                exists = true;
                break;
            }
        }
    }
    closedir(directory);
    return exists;

}

/**
 * \brief gets the answer to the question: Load the aborted game? y/n
 *
 * The player can type yes, no or y, n.
 * Capital letter and small letter are treated equally.
 *
 * @param str       this the question the player is asked
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

