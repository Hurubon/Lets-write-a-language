#include <stdlib.h>
#include <stdio.h>

#include "bool/bool.h"
#include "errors/errors.h"
#include "file_adapter/file_adapter.h"
#include "zfind_algorithm/zfind_algorithm.h"
#include "lexer/lexer.h"

int main(void) {

    FileAdapter* file = (FileAdapter*) malloc(sizeof(FileAdapter));
    error_check(file != NULL, MALLOC_ERROR);
    fileadapter_load(file, "../testfile.txt");

    mylang_lex(file);

    fileadapter_free(&file);
    getchar();
    return 0;

}
