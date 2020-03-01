/** \file board.c
 * \brief functions for the game board
 *
* Created by saif on 1/10/20.
*/
///

#include "board.h"
#include "board_variables.h"
#include <stdio.h>

/**
 * \brief initializes the game board
 * According to the amount of ROWS and COLS an array of cells is initialized
 * @param gaming_brd    the board is initialized with default a cell \c c
 */
void init_brd(cell gaming_brd[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            cell c = {'-', hidden, -1};
            gaming_brd[i][j] = c;
        }
    }
}

/**
 * \alp_arr
 * \brief an array of char. listing the alphabet in capital letters
 */
char alp_arr[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

/**
 * \brief prints a board
 *
 * print_brd iterated over \c game_brd and depending
 * on the state of the cell it prints "-", "*" or the amount of neighbor mines
 * @param game_brd      the board which is supposed to be printed
 */
void print_brd(cell game_brd[ROWS][COLS]) {
    printf("\n    ");
    for (int i = 0; i < COLS; i++) {
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
            if (game_brd[i][j].state != hidden) {
                if (game_brd[i][j].ch == '*'){
                    printf(" %c ", game_brd[i][j].ch);
                } else {
                    printf(" %d ", game_brd[i][j].ngh_mines);
                }
            } else {
                if (game_brd[i][j].ch == '*' && game_brd[i][j].state == hidden) {
                    printf(" - ");
                } else {
                    printf(" %c ", game_brd[i][j].ch);
                }
            }
        }
        printf("\n");
    }
}

/**
 * \brief prints the remaining mines in the game
 *
 * Calculates the remaining mines and prints them
 * Wronged flagged mines are also printed
 * prints also the number of wrong flagged mines
 */
void print_rmaining_mines(void){
    int rmaining_mines = MINES - FLAGGED_CORRECT;
    printf("\nremaining mines: %d\n", rmaining_mines);
    printf("flagged wrong: %d\n", FLAGGED_WRONG);
}

/**
 * \brief prints the board with mines
 * @param game_brd
 */
void show_brd(cell game_brd[ROWS][COLS]) {
    printf("\n    ");
    for (int i = 0; i < COLS; i++) {
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
            if (game_brd[i][j].state == opened) {
                printf(" %d ", game_brd[i][j].ngh_mines);
            } else {
                printf(" %c ", game_brd[i][j].ch);
            }
        }
        printf("\n");
    }
}
