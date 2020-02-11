#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "errors.h"

extern int errno;

static const char* error_messages[] = {
    "Undocumented error!",          /* 0 */
    "Memory allocation failed!",
};

static int cached_errno;

void error_check(bool statement, int error_code) {

    if (statement) {
        return;
    }
    else if (cached_errno != errno && errno != 0) {
        cached_errno = errno;
        perror("");
    }
    else {
        puts(error_messages[error_code]);
    }

    exit(error_code);

}
