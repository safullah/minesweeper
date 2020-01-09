/**
* Created by saif on 1/9/20.
*/
///

#include <ncurses.h>

#ifndef MINESPR_CREATEWIND_H
#define MINESPR_CREATEWIND_H

WINDOW *create_newwin(int height, int width, int starty, int startx);

void destroy_win(WINDOW *local_win);

void call_winfunc();

typedef struct _win_border_struct {
    chtype ls, rs, ts, bs,
            tl, tr, bl, br;
} WIN_BORDER;

typedef struct _WIN_struct {

    int startx, starty;
    int height, width;
    WIN_BORDER border;
} WIN;

void init_win_params(WIN *p_win);

void print_win_params(WIN *p_win);

void create_box(WIN *win, bool flag);

void call_efwinfunc();

#endif //MINESPR_CREATEWIND_H
