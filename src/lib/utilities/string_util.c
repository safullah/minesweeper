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
    static char file[30];
    memset(file, '\0', sizeof(file));
    char *path = "/home/saif/dev/minespr/databank/";
    strcpy(file, path);
    strcat(file, p.name);
    char *file_extension = ".txt";
    strcat(file, file_extension);
    return file;
}

/* qsort comparison function */
int player_cmp(const void *a, const void *b) {
    const player *q = a;
    const player *p = b;
    return strcmp(q->name, p->name);
}

int search_cmp(const void *a, const void *b) {
    const player *target = *(const player **)a;
    return strcmp(target, ((const player *)b)->name);
}
