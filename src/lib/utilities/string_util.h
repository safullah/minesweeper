/**
* Created by saif on 2/12/20.
*/
///

#ifndef MINESPR_STRING_UTIL_H
#define MINESPR_STRING_UTIL_H

#include "../player/player.h"

char *get_input(char *str, char *hint);

char *cutout_backslashn(const char *str);

char *concat_filename(player p);

char *concat_filepath(char *db_path, char *file_name);

char *find_dir(char *searchin, char *searchfor);

void clear_overflow(void);

#endif //MINESPR_STRING_UTIL_H
