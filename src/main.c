// A C++ Program to Implement and Play Minesweeper 

#include "lib/utilities/playing_util.h"
#include "lib/playing_board/board.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

// Driver Program to test above functions
int main(int argc, char *argv[]) {
    // ./minespr 10x10 20
    char input_from_command_line[50] = "\0";
    int counter_4input_array = 0;

    double rows = 0;
    double cols = 0;

    if (argc != 3) {
        exit(1);
    }

    //get rows and cols from argv[1]
    //get number of mines [2]

    //split string
    char *charpointer = NULL;
    char *input_token = strtok(argv[1], "x");
    input_from_command_line[counter_4input_array] = input_token;
    counter_4input_array++;
    //strtod(token,)
    while (input_token != NULL) {
        input_token = strtok(NULL, "x");
        counter_4input_array++;
    }
/*
    for (int i = 0; i < 7; i++) {
        printf("\nString \"%s\"\n", str[i]);
        errno = 0; // Always reset errno
        double tmp = strtod(token, &charpointer);
        // Check if conversion was successful
        if (ptr == str[i]) {
            fprintf(stderr, "strtol failed converting!\n");
        } else if (*ptr != ’\0’) {
            fprintf(stderr, "strtol: %ld (with rest)\n", tmp);
        } else {
            if (errno) {
                fprintf(stderr, "strtol had an overflow!\n");
            } else {
                printf("strtol: %ld\n", tmp);
            }
        }
    }
*/
    playMinesweeper();

    return EXIT_SUCCESS;
}
