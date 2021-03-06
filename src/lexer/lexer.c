#include <stdio.h>
#include <ctype.h>
#include <stddef.h>


#include "../zfind_algorithm/zfind_algorithm.h"
#include "lexer.h"

#include "lexer_macros/define.h"

static void read_label(IFile* file) {

    size_t label_start = file->cursor - 1;
    size_t token_len = 0;
    char c;

    do {
        c = ifile_getchar(file);
        token_len += 1;
    }
    while (IS_LABEL_CHAR(c));

    file->cursor -= 1;

    printf("{'%.*s': 'label'}\n", token_len, file->contents + label_start);

}

static void read_string(IFile* file, char opening_quote) {

    /* Don't need the opening quote. */
    size_t string_start = file->cursor;
    size_t token_len = 0;
    char c;

    do {
        c = ifile_getchar(file);
        token_len += 1;
    }
    while (c != opening_quote);

    /* Take off the closing quote. */
    token_len -= 1;

    printf("{'%.*s': 'string'}\n", token_len, file->contents + string_start);

}

static void read_hexadecimal(IFile* file) {

    /* Don't need the '0x' */
    size_t hex_start = file->cursor;
    size_t token_len = 0;
    char c;

    do {
        c = ifile_getchar(file);
        token_len += 1;
    }
    while (IS_HEX_DIGIT(c));

    file->cursor -= 1;
    token_len -= 1;

    printf("{'%.*s': 'hexadecimal'}\n", token_len, file->contents + hex_start);

}

static void read_binary(IFile* file) {

    /* Don't need the initial 0. */
    size_t bin_start = file->cursor;
    size_t token_len = 0;
    char c;

    do {
        c = ifile_getchar(file);
        token_len += 1;
    }
    while (IS_BIN_DIGIT(c));

    file->cursor -= 1;
    token_len -= 1;

    printf("{'%.*s': 'binary'}\n", token_len, file->contents + bin_start);

}

static void read_decimal(IFile* file) {

    size_t dec_start = file->cursor - 1;
    size_t token_len = 0;
    char c;

    do {
        c = ifile_getchar(file);
        token_len += 1;
    }
    while (IS_DEC_DIGIT(c));

    file->cursor -= 1;

    printf("{'%.*s': 'decimal'}\n", token_len, file->contents + dec_start);

}

static void read_number(IFile* file, char first_digit) {

    if (first_digit == '0') {
        if (ifile_getchar(file) == 'x')
            read_hexadecimal(file);
        else
            read_binary(file);
    }
    else {
        read_decimal(file);
    }

}

static void read_operator(IFile* file) {
    printf("{'%.*s': 'operator'}\n", 1, file->contents + file->cursor - 1);
}

static void read_bracket(IFile* file) {
    printf("{'%.*s': 'bracket'}\n", 1, file->contents + file->cursor - 1);
}

static void read_punctuation(IFile* file) {
    printf("{'%.*s': 'punctuation'}\n", 1, file->contents + file->cursor - 1);
}

static void analyse(char c, IFile* file) {

    if (IS_WHITESPACE(c)) {
        return;
    }
    else if (STARTS_LABEL(c)) {
        read_label(file);
    }
    else if (STARTS_STRING(c)) {
        read_string(file, c);
    }
    else if (STARTS_NUMBER(c)) {
        read_number(file, c);
    }
    else if (IS_OPERATOR(c)) {
        read_operator(file);
    }
    else if (IS_BRACKET(c)) {
        read_bracket(file);
    }
    else if (IS_PUNCTUATION(c)) {
        read_punctuation(file);
    }
    else {
        printf("Encountered unexpected character at character %d: %d\n", file->cursor - 1, (int)c);
    }

}

#include "lexer_macros/undefine.h"

void mylang_lex(IFile* file) {

    char character;

    while (file->cursor < file->length) {
        character = ifile_getchar(file);
        analyse(character, file);
    }

}
