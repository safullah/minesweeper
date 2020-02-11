/**
* Created by saif on 2/11/20.
*/
///

#include "player_profile.h"
#include <stdio.h>
#include <string.h>


char *get_name() {
    printf("Enter your name : ");
    char input[30];
    memset(input, '\0', sizeof(char)*30);
    char *result = fgets(input, sizeof(input) / sizeof(char), stdin);
    while (result == NULL) {
        printf("Enter column row in the following format: \n"
               "  enter column row :A5\n");
        result = fgets(input, sizeof(input) / sizeof(char), stdin);
    }
    //cut out "\n"
    static char copy[10];
    memset(copy, '\0', sizeof(char)*10);
    for (int j = 0; input[j] != '\n'; j++) {
        copy[j] = input[j];
    }
    return copy;
}