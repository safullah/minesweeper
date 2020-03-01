/**
* Created by saif on 2/27/20.
*/
///

#include "../../utilities/string_util.h"
#include "../../converter/strtoint.h"
#include "../../validators/validators.h"

void set_row(void) {
    if (ROWS == 0) {
        char *command = "Enter number of rows";
        char *hint = command;
        char *str = get_input(command, hint);
        int rows = str_to_int(str);
        if (is_row_valid(rows, str)) {
            ROWS = rows;
        } else {
            set_row();
        }
    }
}

void set_col(void) {
    if (COLS == 0) {
        char *command = "Enter number of columns";
        char *hint = command;
        char *str = get_input(command, hint);
        int cols = str_to_int(str);
        if (is_col_valid(cols, str)) {
            COLS = cols;
        } else {
            set_col();
        }
    }
}

void set_mine(void) {
    if (ROWS == 0) {
        set_row();
    }
    if (COLS == 0) {
        set_col();
    }
    char *command = "Enter number of mines";
    char *hint = command;
    char *str = get_input(command, hint);
    int mines = str_to_int(str);
    if (is_mine_valid(mines, str)) {
        MINES = mines;
    } else {
        set_mine();
    }
}

void set_param(void) {
    set_row();
    set_col();
    set_mine();
}
