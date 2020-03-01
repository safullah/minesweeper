/**
 * \file string_utl.c
 * \brief function to work on strings
 *
* Created by saif on 2/12/20.
*/
///

#include "string_util.h"
#include <string.h>
#include <stdio.h>
#include <limits.h>

/**
 * \brief prompts the user for input
 *
 * @param str  string with which the user is prompted
 * @param hint  a hint for the player
 * @return  char *
 */
char *get_input(char *str, char *hint) {
    char input[50];
    memset(input, '\0', sizeof(input));
    char *result = NULL;
    while (result == NULL || strcmp(result, "\n") == 0) {
        printf("%s: ", str);
        result = fgets(input, sizeof(input) / sizeof(char), stdin);
        if (strchr(input, '\n') == NULL) {
            printf("input too long: %s\n", result);
            printf("%s\n", hint);
            clear_overflow();
            result = NULL;
        }
    }
    char *copy = cutout_backslashn(input);
    return copy;
}

/**
 * \brief cut out back slash n from the end of a string
 * @param str   string with back slash at the end
 * @return char *
 */
char *cutout_backslashn(const char *str) {
    static char copy[50];
    memset(copy, '\0', sizeof(copy));
    for (int j = 0; *(str + j) != '\n'; j++) {
        copy[j] = *(str + j);
    }
    return copy;
}

/**
 * \brief concats a file name
 *
 * @param name file name
 * @return char *   filename.txt
 */
char *concat_filename(char *name) {
    static char file_name[50];
    memset(file_name, '\0', sizeof(file_name));
    strcpy(file_name, name);
    strcat(file_name, ".txt");
    return file_name;
}

/**
 * \brief concats the path of a file
 *
 * @param path      directory where the file is
 * @param file_name
 * @return char *   returns the absolute path fo the file
 */
char *concat_filepath(char *path, char *file_name) {
    static char filepath[PATH_MAX+1] = {'\0'};
    strcpy(filepath, path);
    strcat(filepath, file_name);
    return filepath;
}

/**
 * \brief clears the overflow of fgets()
 */
void clear_overflow(void) {
    int ch;
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        //do nothing until buffer is cleared
    }
}

