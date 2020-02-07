#include <stdlib.h>
#include <stdio.h>

#include "lib/bool/bool.h"
#include "lib/errors/errors.h"
#include "lib/file_adapter/file_adapter.h"
#include "lib/zfind_algorithm/zfind_algorithm.h"

int main(void) {

    FileAdapter* file = (FileAdapter*) malloc(sizeof(FileAdapter));
    error_check(file != NULL, MALLOC_ERROR);
    fileadapter_load(file, "foo.txt");

    /* TODO: Lex(file) */
    /* code */

    fileadapter_free(file);
    getchar();
    return 0;

}
