#include <stdlib.h>
#include <stdio.h>

#include "bool/bool.h"
#include "errors/errors.h"
#include "ifile/ifile.h"
#include "zfind_algorithm/zfind_algorithm.h"
#include "lexer/lexer.h"

int main(void) {

    IFile* file = (IFile*) malloc(sizeof(IFile));
    error_check(file != NULL, MALLOC_ERROR);
    ifile_load(file, "../testfile.txt");

    mylang_lex(file);

    ifile_free(&file);
    return 0;

}
