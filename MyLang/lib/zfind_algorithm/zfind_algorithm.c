#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "zfind_algorithm.h"

#define FIND_ZVALUE(z_array, z_string, z_len, left, right, i) {          \
    while (right < z_len && z_string[right - left] == z_string[right]) { \
        right++;                                                         \
    }                                                                    \
    z_array[i] = right - left;                                           \
    right--;                                                             \
}

static void generate_zarray(int*         z_array,
                            const char*  z_string,
                            const size_t z_len) {

    size_t left  = 0;
    size_t right = 0;
    size_t k, i;

    for (i = 1; i < z_len; i++) {

        if (i > right) {
            left = right = i;
            FIND_ZVALUE(z_array, z_string, z_len,
                        left,    right,    i);
        }
        else {
            k = i - left;
            if (z_array[k] < right - i + 1) {
                z_array[i] = z_array[k];
            }
            else {
                FIND_ZVALUE(z_array, z_string, z_len,
                            left,    right,    i);
            }
        }

    }

}

static void generate_zstring(char*        z_string,
                             const char*  needle,
                             const char*  haystack,
                             const size_t z_len,
                             const size_t needle_len,
                             const size_t haystack_len) {

    const size_t offset = needle_len + 1;

    memcpy(z_string, needle, needle_len);
    memcpy(z_string + offset, haystack, haystack_len + 1);
    z_string[needle_len] = ZFIND_DELIM_CHAR;

}

bool zfind_str(const char* needle, const char* haystack) {

    const size_t needle_len = strlen(needle);
    const size_t haystack_len = strlen(haystack);
    const size_t z_len = needle_len + haystack_len + 1;

    int*  z_array  = (int*)  malloc(z_len * sizeof(int));
    char* z_string = (char*) malloc(z_len + 1);

    bool was_found = false;
    size_t i;

    generate_zstring(z_string, needle,     haystack,
                     z_len,    needle_len, haystack_len);
    generate_zarray(z_array, z_string, z_len);

    for (i = 1; i < z_len; i++) {
        was_found = (z_array[i] == needle_len);
        if (was_found)
            break;
    }

    return was_found;

}

bool zfind_chr(const char character, const char* str) {

    const size_t string_len = strlen(str);
    bool was_found;
    size_t i;

    for (i = 0; i < string_len; i++) {
        was_found = (str[i] == character);
        if (was_found)
            break;
    }

    return was_found;

}

#undef FIND_ZVALUE
