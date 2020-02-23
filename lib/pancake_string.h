#ifndef PANCAKE_STRING_H
#define PANCAKE_STRING_H

    /*
    ** Splits a string of tokens separated by the given delimiter into a
    ** NULL-terminated array of strings.
    **
    ** Usage:
    **     char** fruits = pancake_string_split("Apple,Orange,Banana", ',');
    **
    ** Result:
    **     fruits = {
    **         "Apple",
    **         "Orange",
    **         "Banana",
    **         NULL,
    **     };
    */
    char** pancake_string_split     (const char* string,
                                     const char  delimiter);

    /* Alternative implementation of above function. */
    char** pancake_string_split2    (const char* string,
                                     const char  delimiter);

    /*
    ** Inverse of string_split(). Joins an array of tokens into
    ** a single string of tokens separated by the given delimiter.
    */
    char*  pancake_string_join      (const char** substring_array,
                                     const char   delimiter);

    /* Properly frees the array returned by pancake_string_split(). */
    void   pancake_string_array_free(char** array);

#endif /* PANCAKE_STRING_H */
