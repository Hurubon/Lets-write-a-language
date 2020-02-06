#include <stdlib.h>
#include <stdio.h>

#include "fileadapter.h"

void FileAdapter_Load(FileAdapter* adapter, const char* file_name) {

    FILE* file = fopen("foo.txt", "r");
    size_t i;

    fseek(file, 0, SEEK_END);
    adapter->cursor = 0;
    adapter->length = ftell(file);
    adapter->contents = (char*) malloc(adapter->length);
    fseek(file, 0, SEEK_SET);

    for (i = 0; i < adapter->length; ++i) {
        adapter->contents[i] = fgetc(file);
    }
    adapter->contents[i] = '\0';

    fclose(file);

}

void FileAdapter_Close(FileAdapter* adapter) {
    free(adapter->contents);
    free(adapter);
}

char FileAdapter_GetChar(FileAdapter* adapter) {
    return adapter->contents[adapter->cursor++];
}

size_t FileAdapter_GetCursor(const FileAdapter* adapter) {
    return adapter->cursor;
}

void FileAdapter_SetCursor(FileAdapter* adapter, const size_t index) {
    adapter->cursor = index;
}
