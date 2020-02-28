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
    char** pancake_string_split       (const char*  string,
                                       const char   delimiter);

    /*
    ** Inverse of string_split(). Joins an array of tokens into
    ** a single string of tokens separated by the given delimiter.
    */
    char*  pancake_string_join        (char**       substring_array,
                                       const size_t array_length,
                                       const char   delimiter);

    /* Properly frees the array returned by pancake_string_split(). */
    void   pancake_string_array_free  (char**       string_array,
                                       const size_t array_length);

    /*
    ** Returns the length of the array returned by pancake_string_split().
    ** Doesn't count the NULL pointer at the end.
    */
    size_t pancake_string_array_length(char**       string_array);

    void   pancake_string_reverse     (char*        string,
                                       const size_t string_length);

    char*  pancake_string_reverse_copy(const char*  string,
                                       const size_t string_length);

#endif /* PANCAKE_STRING_H */
