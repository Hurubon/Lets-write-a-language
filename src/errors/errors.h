#ifndef MYLANG_API_ERRORS_H
#define MYLANG_API_ERRORS_H

#include "../bool/bool.h"

#define MALLOC_ERROR 1
#define EOF_REACHED_FLAG 2

/* Checks if statement is true and handles errors.
** @param: int - custom code in case errno can't catch the possible error.
*/
void error_check(bool statement, int error_code);

#endif /* MYLANG_API_ERRORS_H */
