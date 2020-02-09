#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "errors.h"

extern int errno;

static const char* error_messages[] = {
    "Undocumented error!",          /* 0 */
    "Memory allocation failed!",
    "End of file reached!",
};

void error_check(bool statement, int error_code) {

    static int cached_errno;

    if (statement) {
        return;
    }
    else if (cached_errno != errno && errno != 0) {
        perror("");
    }
    else {
        puts(error_messages[error_code]);
    }

    getchar();
    exit(error_code);

}
