#ifndef MYLANG_API_FILE_ADAPTER_H
#define MYLANG_API_FILE_ADAPTER_H

#include <stddef.h>

typedef struct {
    char* contents;
    size_t length;
    size_t cursor;
} FileAdapter;

/* Loads the contents of some file into the adapter;
** @param: FileAdapter* - pointer to adapter struct in which to load the file.
** @param: const char* - name of the file from which to load.
*/
void  fileadapter_load  (FileAdapter* file,
                         const char*  file_name);

/* Returns character at cursor position and moves cursor to the right by 1.
** @param: FileAdapter* - pointer to adapter struct.
** @returns: char - character at the cursor's current position.
*/
char fileadapter_getchar(FileAdapter* file);

/* Frees the file contents array and the adapter struct itself.
** @param: FileAdapter* - pointer to adapter struct.
*/
void fileadapter_free   (FileAdapter* file);

#endif /* MYLANG_API_FILE_ADAPTER_H */
