#include <stdlib.h>
#include <stdio.h>

#include "../errors/errors.h"
#include "ifile.h"

void ifile_load(IFile* file, const char* file_name) {

    FILE* cfile = fopen(file_name, "r");
    error_check(cfile != NULL, MALLOC_ERROR);

    fseek(cfile, 0, SEEK_END);

    file->cursor   = 0;
    file->length   = ftell(cfile);
    printf("Ftell says the file is %d characters long.\n", file->length);
    file->contents = (char*) malloc(file->length + 1);
    error_check(file->contents != NULL, MALLOC_ERROR);

    fseek(cfile, 0, SEEK_SET);

    fread(file->contents, sizeof(char), file->length, cfile);
    file->contents[file->length] = '\0';

    fclose(cfile);

}

char ifile_getchar(IFile* file) {
    return file->contents[file->cursor++];
}

void ifile_free(IFile** file) {
    free((*file)->contents);
    free(*file);
    *file = NULL;
}
