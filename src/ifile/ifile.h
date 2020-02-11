#ifndef MYLANG_API_FILE_INTERFACE_H
#define MYLANG_API_FILE_INTERFACE_H

#include <stddef.h>

typedef struct FileInterface {
    char* contents;
    size_t length;
    size_t cursor;
} IFile;

/* Loads the contents of some file into the struct;
** @param: IFile* - pointer to interface struct in which to load the file.
** @param: const char* - name of the file from which to load.
*/
void ifile_load   (IFile*       file,
                   const char*  file_name);

/* Returns character at cursor position and moves cursor to the right by 1.
** @param: IFile* - pointer to interface struct.
** @returns: char - character at the cursor's current position.
*/
char ifile_getchar(IFile* file);

/* Frees the file contents array and the interface struct itself and
** sets the pointer to NULL.
** @param: IFile** - address pointer to interface struct.
*/
void ifile_free   (IFile** file);

#endif /* MYLANG_API_FILE_INTERFACE_H */
