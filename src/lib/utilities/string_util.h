/**
* Created by saif on 2/12/20.
*/
///

#ifndef MINESPR_STRING_UTIL_H
#define MINESPR_STRING_UTIL_H

#include "../player/player.h"

char *take_input(char *str);

char *cutout_bslashn(char *str);

char *concat_filename(player p);

int player_cmp(const void *a, const void *b);

int search_cmp(const void *a, const void *b);

#endif //MINESPR_STRING_UTIL_H
