/**
* Created by saif on 1/21/20.
*/
///

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include "strtoint.h"

int str_to_int(char *str) {
    char *rest = "\0";
    errno = 0; // always reset errno
    double integer = strtod(str, &rest);
    if (rest == str) {
        return -1;
    } else if (*rest != '\0') {
        return -1;
    } else {
        if (errno) {
            return -1;
        } else {
            if (integer >= 0) {
                return (int) integer;
            } else {
                return -1;
            }
        }
    }
}
