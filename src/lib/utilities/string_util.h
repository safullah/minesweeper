/**
 * \file string_utl.h
* Created by saif on 2/12/20.
*/
///

#ifndef MINESPR_STRING_UTIL_H
#define MINESPR_STRING_UTIL_H

#include "../player/player.h"

char *get_input(char *str, char *hint);

char *cutout_backslashn(const char *str);

char *concat_filename(char *name);

char *concat_filepath(char *path, char *file_name);

void clear_overflow(void);

#endif //MINESPR_STRING_UTIL_H
