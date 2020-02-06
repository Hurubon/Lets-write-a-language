#ifndef MYLANG_FILE_ADAPTER_H
#define MYLANG_FILE_ADAPTER_H

#include <stddef.h>

typedef struct {

    char* contents;
    size_t length;
    size_t cursor;

} FileAdapter;

void FileAdapter_Load(FileAdapter* adapter, const char* file_name);
void FileAdapter_Close(FileAdapter* adapter);
char FileAdapter_GetChar(FileAdapter* adapter);
size_t FileAdapter_GetCursor(const FileAdapter* adapter);
void FileAdapter_SetCursor(FileAdapter* adapter, const size_t index);

#endif /* MYLANG_FILE_ADAPTER_H */
