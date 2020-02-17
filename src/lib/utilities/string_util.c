/**
* Created by saif on 2/12/20.
*/
///

#include "string_util.h"
#include <string.h>
#include <stdio.h>
#include "../validators/validators.h"

char *take_input(char *str) {
    printf("%s\n", str);
    static char input[30];
    memset(input, '\0', sizeof(char) * 30);
    char *result = fgets(input, sizeof(input) / sizeof(char), stdin);
    while (result == NULL) {
        printf("%s\n", str);
        result = fgets(input, sizeof(input) / sizeof(char), stdin);
    }
    if (is_overflow(input)) {
        printf("Input too long!\n");
        take_input(str);
    }
    return input;
}

char *cutout_bslashn(char *str) {
    static char copy[30];
    memset(copy, '\0', sizeof(char) * 30);
    for (int j = 0; *(str + j) != '\n'; j++) {
        copy[j] = *(str + j);
    }
    return copy;
}
char *concat_filename(player p) {
    static char file_name[30];
    memset(file_name, '\0', sizeof(file_name));
    strcpy(file_name, p.name);
    char *file_extension = ".txt";
    strcat(file_name, file_extension);
    return file_name;
}

char *concat_filepath(player p) {
    static char filepath[60];
    memset(filepath, '\0', sizeof(filepath));
    char *path = "/home/saif/dev/minespr/databank/";
    strcpy(filepath, path);
    strcat(filepath, p.name);
    char *file_extension = ".txt";
    strcat(filepath, file_extension);
    return filepath;
}

/* qsort comparison function */
int player_cmp(const void *a, const void *b) {
    const player *q = a;
    const player *p = b;
    return strcmp(q->name, p->name);
}

/*
int search_cmp(const void *a, const void *b) {
    const player *target = *(const player **)a;
    return strcmp(&target, ((const player *)b)->name);
}
*/
