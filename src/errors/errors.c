#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "errors.h"

extern int errno;

void error_check(bool statement, int error_code) {

    static int cached_errno;

    if (statement) {
        return;
    }

    if (cached_errno != errno && errno != 0) {
        perror("");
        getchar();
        exit(errno);
    }

    switch (error_code) {

        case MALLOC_ERROR:
            printf("Memory allocation failed!\n");
            break;

        default:
            printf("Undocumented error!\n");

    }

    getchar();
    exit(error_code);

}
