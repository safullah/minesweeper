/**
* Created by saif on 2/12/20.
*/
///

#include "string_util.h"
#include <string.h>
#include <stdio.h>

char *get_input(char *str, char *hint) {
    printf("%s ", str);
    char input[50];
    memset(input, '\0', sizeof(char) * 50);
    char *result = NULL;
    while (result == NULL || strcmp(result, "\n") == 0) {
        result = fgets(input, sizeof(input) / sizeof(char), stdin);
        if (strchr(input, '\n') == NULL) {
            printf("input too long: %s\n", result);
            printf("\n%s ", hint);
            clear_overflow();
            result = NULL;
        }
    }
    char *copy = cutout_backslashn(input);
    return copy;
}

char *cutout_backslashn(const char *str) {
    static char copy[50];
    memset(copy, '\0', sizeof(char) * 50);
    for (int j = 0; *(str + j) != '\n'; j++) {
        copy[j] = *(str + j);
    }
    return copy;
}

char *concat_filename(player p) {
    static char file_name[50];
    memset(file_name, '\0', sizeof(file_name));
    strcpy(file_name, p.name);
    char *file_extension = ".txt";
    strcat(file_name, file_extension);
    return file_name;
}

char *concat_filepath(player p) {
    static char filepath[100];
    memset(filepath, '\0', sizeof(filepath));
    char *path = "/home/saif/dev/minespr/databank/";
    strcpy(filepath, path);
    strcat(filepath, p.name);
    char *file_extension = ".txt";
    strcat(filepath, file_extension);
    return filepath;
}

void clear_overflow() {
    int ch;
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        //do nothing until buffer is cleared
    }
}
