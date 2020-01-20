/**
* Created by saif on 1/10/20.
*/
///

#include "board.h"
#include "board_variables.h"
#include <stdio.h>

char alp_arr[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

void init_brds(cell hidden_brd[ROWS][COLS], cell gaming_brd[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            cell c = {'-', hidden, 0};
            gaming_brd[i][j] = hidden_brd[i][j] = c;
        }
    }
}

void print_brd(cell game_brd[ROWS][COLS]) {
    printf("    ");
    for (int i = 0; i < ROWS; i++) {
        printf("%c  ", alp_arr[i]);
    }
    printf("\n");
    for (int i = 0; i < ROWS; i++) {
        if (i < 10) {
            printf(" %d ", i);
        } else {
            printf("%d ", i);
        }

        for (int j = 0; j < COLS; j++) {
            printf(" %c ", game_brd[i][j].ch);
        }
        printf("\n");
    }
}
