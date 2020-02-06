#include <ctype.h>

#include "../zalgorithm/zalgorithm.h"
#include "lexer.h"

static void scan_label(FileAdapter* file, const char input) {

    char character = FileAdapter_GetChar(file);
    size_t label_begin = file->cursor - 1;
    size_t label_len = 1;

    while (isalpha(character) || isdigit(character) || character == '_') {
        ++label_len;
        character = FileAdapter_GetChar(file);
    }

    printf(
        "{'%.*s': 'label'}\n",
        file->cursor - label_begin - 1, file->contents + label_begin);

}

void lex(FileAdapter* file) {

    char input;

    while (file->cursor <= file->length) {

        input = FileAdapter_GetChar(file);

        if (input == ' ' || input == '\t' || input == '\n') {
            continue;
        }
        else if (isalpha(input) || input == '_') {
            scan_label(file, input);
        }

    }


}
