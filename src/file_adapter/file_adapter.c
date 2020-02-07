#include <stdlib.h>
#include <stdio.h>

#include "../errors/errors.h"
#include "file_adapter.h"

void fileadapter_load(FileAdapter* file, const char* file_name) {

    size_t i;
    FILE* cfile = fopen(file_name, "r");
    error_check(cfile != NULL, MALLOC_ERROR);

    fseek(cfile, 0, SEEK_END);

    file->cursor   = 0;
    file->length   = ftell(cfile);
    file->contents = (char*) malloc(file->length + 1);
    error_check(file->contents != NULL, MALLOC_ERROR);

    fseek(cfile, 0, SEEK_SET);

    fread(file->contents, 1, file->length, cfile);
    file->contents[file->length] = '\0';

    fclose(cfile);

}

char fileadapter_getchar(FileAdapter* file) {
    return file->contents[file->cursor++];
}

void fileadapter_free(FileAdapter* file) {
    free(file->contents);
    free(file);
}
