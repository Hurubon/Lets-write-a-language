#include <stdlib.h> /* For stdlib memory functions and memcpy(). */
#include <string.h> /* For strlen().                             */


#include "pancake_memory_debug.h"
#include "pancake_string.h"


char** pancake_string_split(const char* string, const char delimiter) {

    /* We add 1 because we care about the \0 character too. See below. */
    const size_t string_len = strlen(string) + 1;
    size_t sub_start = 0;
    size_t sub_index = 0;
    size_t sub_len;
    size_t i;

    char** substrings = malloc((sizeof *substrings) * (string_len / 2));

    for (i = 0; i < string_len; ++i) {

        /*
        ** Potentially faster to check if i reached the end of the
        ** string (the \0 character) than checking if string[i] == '\0'.
        */
        if (string[i] == delimiter || i == string_len - 1) {

            sub_len = i - sub_start;

            substrings[sub_index] = malloc(sub_len + 1);
            substrings[sub_index][sub_len] = '\0';
            memcpy(substrings[sub_index], string + sub_start, sub_len);

            sub_index += 1;
            sub_start = i + 1;

            /*
            ** If we just encountered a delimiter, we don't expect the
            ** next character to also be a delimiter, so we can skip it.
            */
            ++i;

        }

    }

    /* NULL-terminate the array so we can find its length. */
    substrings[sub_index] = NULL;
    return substrings;

}


/* Alternative implementation. */
char** pancake_string_split2(const char* string, const char delimiter) {

    /* We add 1 because we care about the \0 character too. See below. */
    const size_t string_len = strlen(string) + 1;
    size_t sub_start;
    size_t sub_len;

    /*
    ** Allocate arrays to store the indices of delimiters and
    ** the substrings themselves.
    */
    char** substrings = malloc((sizeof *substrings) * (string_len / 2));
    int* delimiter_indices = malloc((sizeof *delimiter_indices) * (string_len / 2));

    size_t delimiter_index = 1;
    size_t i;

    /*
    ** This is used in calculations later on. Basically, we create
    ** virtual delimiters just before the beginning and just after
    ** the end of the string.
    */
    delimiter_indices[0] = -1;

    /* Store the indices of each delimiter. */
    for (i = 1; i < string_len; ++i) {
        if (string[i] == delimiter || i == string_len - 1) {
            delimiter_indices[delimiter_index++] = i++;
        }
    }

    /*
    ** delimiter_index is now the total number of delimiters,
    ** including the virtual ones.
    */
    for (i = 0; i < delimiter_index - 1; ++i) {

        /*
        ** A string starts just after a delimiter (here the virtual
        ** ones come in handy).
        */
        sub_start = delimiter_indices[i] + 1;

        /*
        ** And it's length is however many characters there is until
        ** the next delimiter.
        */
        sub_len = delimiter_indices[i + 1] - sub_start;

        substrings[i] = malloc(sub_len + 1);
        substrings[i][sub_len] = '\0';
        memcpy(substrings[i], string + sub_start, sub_len);

    }

    substrings[delimiter_index - 1] = NULL;

    free(delimiter_indices);
    return substrings;

}

void pancake_string_array_free(char** array) {

    void* pointer;
    size_t i;

    /* This is to prevent indexing the array twice. */
    for (i = 0; (pointer = array[i]) != NULL; ++i) {
        free(pointer);
    }

    free_comment(array, "Freed array of strings.");

}

char* pancake_string_join(const char** substring_array, const char delimiter) {

    char* joined_string;
    size_t joined_string_length;

    size_t* word_lengths;
    size_t word_lengths_sum = 0;
    size_t array_length = 0;

    size_t i;

    for (i = 0; substring_array[i] != NULL || i < 0; ++i)
        ++array_length;

    word_lengths = malloc((sizeof *word_lengths) * array_length);

    /* In case the array isn't NULL-terminated. */
    if (i < 0)
        return NULL;

    for (i = 0; i < array_length; ++i) {
        size_t word_length = strlen(substring_array[i]);
        word_lengths[i] = word_length;
        word_lengths_sum += word_length;
    }

    joined_string_length = word_lengths_sum + array_length;
    joined_string = malloc(joined_string_length);

    for (i = 0; i < array_length; ++i) {

        memcpy(joined_string, substring_array[i], word_lengths[i]);
        joined_string[word_lengths[i]] = delimiter;

        /* Move the pointer forwards until the beginning of the next word. */
        joined_string += (word_lengths[i] + 1);

    }

    /* Move the pointer back to the beginning of the string. */
    joined_string -= joined_string_length;
    joined_string[joined_string_length - 1] = '\0';

    free(word_lengths);
    return joined_string;

}
