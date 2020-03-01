/**\file strtoint.c
 * \brief str_to_int converts a char *str to int
* Created by saif on 1/21/20.
*/
///

#include <errno.h>
#include <stdlib.h>

/**
 * \brief str_to_int converts a string to int
 *
 * @param str   string to convert
 * @return int  in case of success the number corresponding to the string otherwise -1
 */
int str_to_int(char *str) {
    char *rest = "\0";
    errno = 0; // always reset errno
    double integer = strtod(str, &rest);
    if (rest == str || *rest != '\0' || errno) {
        return -1;
    } else {
        if (integer >= 0) {
            return (int) integer;
        } else {
            return -1;
        }
    }
}
