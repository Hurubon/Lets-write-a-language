/*
** Internal header used for defining function prototypes for
** pancake_memory_debug.c. Separated from the public header
** to avoid name collisions with its macro definitions.
*/

#ifndef PANCAKE_MEMORY_DEBUG_INTERNAL_H
#define PANCAKE_MEMORY_DEBUG_INTERNAL_H

    /*
    ** If PANCAKE_MEMORY_DEBUG_ENABLE is defined, prints out
    ** a nicely-formatted memory report consisting of both
    ** pancake_memory_get_memory_leak_count() and
    ** pancake_memory_get_bytes_allocated_count().
    **
    ** IMPORTANT: Does nothing otherwise.
    **
    ** Example:
    **     pancake_memory_report();
    **
    ** Output:
    **     Total memory currently allocated: n bytes.
    **     Total blocks currently not freed: m blocks.
    */
    void pancake_memory_report(void);

    #if defined(PANCAKE_MEMORY_DEBUG_ENABLE)

        #include <stddef.h> /* For size_t. */

        /*
        ** Wraps stdlib's malloc, giving diagnostic information such as:
        **     - how much memory was allocated
        **     - in which file and on which line it was called
        **     - the address of the returned pointer
        */
        void* pancake_memory_internal_malloc (const size_t memory_size,
                                              const char*  file,
                                              const int    line);

        /*
        ** Wraps stdlib's calloc, giving diagnostic information such as:
        **     - how much memory was allocated
        **         - how many 'objects'
        **         - of which size
        **     - in which file and on which line it was called
        **     - the address of the returned pointer
        */
        void* pancake_memory_internal_calloc (const size_t object_num,
                                              const size_t object_size,
                                              const char*  file,
                                              const int    line);

        /*
        ** Wraps stdlib's realloc, giving diagnostic information, such as:
        **     - the memory block's previous size
        **     - the memory block's new size
        **     - in which file and on which line it was called
        **     - the addres of the returned pointer
        */
        void* pancake_memory_internal_realloc(void*        pointer,
                                              const size_t old_size,
                                              const size_t new_size,
                                              const char*  file,
                                              const int    line);

        /*
        ** Wraps stdlib's free, giving diagnostic information such as:
        **     - which memory location it was called on
        **     - how much memory was freed
        **     - the file and line on which it was called
        */
        void  pancake_memory_internal_free   (void*        pointer,
                                              const size_t memory_size,
                                              const char*  file,
                                              const int    line);


        /*
        ** These wrap the previous 4 functions, but also print out a
        ** given comment meant to describe why the function was called
        ** or what it's supposed to do.
        **
        ** Example:
        **     char* input = malloc_comment(64, "Allocated string for user input.");
        **
        ** Output:
        **     -- Allocated string for user input.
        **     file:line: Allocated 64 bytes at address ________ with malloc().
        */
        void* pancake_memory_internal_malloc_comment (const size_t memory_size,
                                                      const char*  comment,
                                                      const char*  file,
                                                      const int    line);

        void* pancake_memory_internal_calloc_comment (const size_t object_num,
                                                      const size_t object_size,
                                                      const char*  comment,
                                                      const char*  file,
                                                      const int    line);

        void* pancake_memory_internal_realloc_comment(void*        pointer,
                                                      const size_t old_size,
                                                      const size_t new_size,
                                                      const char*  comment,
                                                      const char*  file,
                                                      const int    line);

        void  pancake_memory_internal_free_comment   (void*        pointer,
                                                      const size_t memory_size,
                                                      const char*  comment,
                                                      const char*  file,
                                                      const int    line);


        /*
        ** Returns the difference between the number of allocations (malloc
        ** or calloc) and free's. Example use-case would be to check if there
        ** are any memory leaks or double free's when the program exits.
        */
        int    pancake_memory_get_memory_leak_count    (void);

        /* Returns the number of bytes currently allocated. */
        size_t pancake_memory_get_bytes_allocated_count(void);


        /*
        ** Wraps a compiler/OS-specific function for getting the size
        ** of an allocated block via a pointer to its beginning.
        **
        ** Notes:
        **     - Not fully portable.
        **     - Includes the required header for the specific function.
        */
        #if defined(_WIN32)

            #include <malloc.h>
            #define pancake_memory_internal_memsize(pointer) (_msize(pointer))

        #elif defined(__APPLE__) || defined(__MACH__)

            #include <malloc/malloc.h>
            #define pancake_memory_internal_memsize(pointer) (malloc_size(pointer))

        #elif defined(__gnu_linux__)

            #include <malloc.h>
            #define pancake_memory_internal_memsize(pointer) (malloc_usable_size(pointer))

        #else

            #error "Unknown platform. No known function to retrieve malloc block size."

        #endif /* COMPILER/OS GUARDS */

    #endif /* PANCAKE_MEMORY_DEBUG_ENABLE */

#endif /* PANCAKE_MEMORY_DEBUG_INTERNAL_H */
