#include <stdlib.h> /* For stdlib memory functions and memcpy(). */
#include <string.h> /* For strlen().                             */


#include "pancake_memory_debug.h"
#include "pancake_string.h"


char** pancake_string_split(const char*  string,
                            const char   delimiter) {

    char** substrings_array;

    size_t string_length;
    size_t delimiter_count = 0;

    size_t substring_start = 0;
    size_t substring_index = 0;

    size_t i;
    char c;

    for (i = 0; (c = string[i]) != '\0'; ++i) {
        delimiter_count += (c == delimiter);
    }

    string_length = i;

    if (string_length == 0)
        return NULL;

    /*
    ** There are delimiter_count + 1 tokens in the given string.
    ** We also need another element for the NULL pointer terminator.
    */
    substrings_array = malloc(
                        (sizeof *substrings_array) * (delimiter_count + 2)
                       );

    for (i = 0; i < string_length + 1; ++i) {

        /*
        ** Potentially faster to check if i reached the end of the
        ** string (the \0 character) than checking if string[i] == '\0'.
        */
        if (string[i] == delimiter || i == string_length) {

            const size_t substring_length = i - substring_start;
            char* substring = malloc(substring_length + 1);

            substring[substring_length] = '\0';
            memcpy(substring, string + substring_start, substring_length);

            substrings_array[substring_index] = substring;

            /*
            ** If we just encountered a delimiter, we don't expect the
            ** next character to also be a delimiter, so we can skip it
            ** and assume a new token starts after it.
            */
            substring_start = (++i);
            substring_index += 1;

        }

    }

    /* NULL-terminate the array so we can later find its length. */
    substrings_array[substring_index] = NULL;

    return substrings_array;

}

char* pancake_string_join(char**       substrings_array,
                          const size_t array_length,
                          const char   delimiter) {

    char* joined_string;
    size_t joined_length;

    size_t* word_lengths = malloc((sizeof *word_lengths) * array_length);
    size_t word_lengths_sum = 0;

    size_t i;

    for (i = 0; i < array_length; ++i) {

        char* substring = substrings_array[i];
        size_t word_length;

        if (substring == NULL) {
            free(word_lengths);
            return NULL;
        }

        word_length = strlen(substring);
        word_lengths[i] = word_length;
        word_lengths_sum += word_length;

    }

    joined_length = word_lengths_sum + array_length;
    joined_string = malloc(joined_length + 1);

    for (i = 0; i < array_length; ++i) {

        const size_t current_word_length = word_lengths[i];

        memcpy(joined_string, substrings_array[i], current_word_length);
        joined_string[current_word_length] = delimiter;

        /* Move the pointer forwards to where the next word should start. */
        joined_string += (current_word_length + 1);

    }

    free(word_lengths);

    /*
    ** The pointer should now be pointing at where '\0' should be.
    ** Put the character there, then move it back to the beginning.
    */
    *joined_string = '\0';
    joined_string -= joined_length;

    return joined_string;

}

void pancake_string_array_free(char**       string_array,
                               const size_t array_length) {

    size_t i;
    for (i = 0; i < array_length; ++i) {
        free(string_array[i]);
    }

    free_comment(string_array, "Freed array of strings.");

}

size_t pancake_string_array_length(char** string_array) {
    size_t i = 0;
    while (string_array[i] != NULL)
        ++i;

    return i;
}

void pancake_string_reverse(char* string, const size_t string_length) {
    size_t i;
    for (i = 0; i < string_length / 2; ++i) {
        char tmp = string[i];
        string[i] = string[string_length - i - 1];
        string[string_length - i - 1] = tmp;
    }
}

char* pancake_string_reverse_copy(const char*  string,
                                  const size_t string_length) {

    char* reversed_string = malloc(string_length + 1);
    size_t i;

    for (i = 0; i < string_length; ++i) {
        reversed_string[i] = string[string_length - i - 1];
    }

    reversed_string[string_length] = '\0';

    return reversed_string;

}
