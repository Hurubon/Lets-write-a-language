#ifndef PANCAKE_MEMORY_DEBUG_H
#define PANCAKE_MEMORY_DEBUG_H

    #if defined(PANCAKE_MEMORY_DEBUG_ENABLE)

        #include "pancake_memory_debug_internal.h"

        /*
        ** If it's too wide for you, don't bother reading it.
        ** It's meant to be transparent anyway.
        */

        /* Replaces stdlib memory functions with pancake internal wrappers. */
        #define malloc(memory_size)                            (pancake_memory_internal_malloc (memory_size,                                                        __FILE__, __LINE__))
        #define calloc(obj_num, obj_size)                      (pancake_memory_internal_calloc (obj_num, obj_size,                                                  __FILE__, __LINE__))
        #define realloc(pointer, memory_size)                  (pancake_memory_internal_realloc(pointer, pancake_memory_internal_memsize(pointer), memory_size,     __FILE__, __LINE__))
        #define free(pointer)                                  (pancake_memory_internal_free   (pointer, pancake_memory_internal_memsize(pointer),                  __FILE__, __LINE__))

        /*
        ** Extra functions which allow you to leave comments about
        ** the allocated memory for debugging purposes.
        */
        #define malloc_comment(memory_size, comment)           (pancake_memory_internal_malloc_comment (memory_size,                                       comment, __FILE__, __LINE__))
        #define calloc_comment(obj_num, obj_size, comment)     (pancake_memory_internal_calloc_comment (obj_num, obj_size,                                 comment, __FILE__, __LINE__))
        #define realloc_comment(pointer, memory_size, comment) (pancake_memory_internal_realloc_comment(pointer, memory_size,                              comment, __FILE__, __LINE__))
        #define free_comment(pointer, comment)                 (pancake_memory_internal_free_comment   (pointer, pancake_memory_internal_memsize(pointer), comment, __FILE__, __LINE__))

    #else

        /*
        ** If debugging isn't enabled, these collapse into standard memory
        ** functions. This allows you to use them without having to refactor
        ** your code once you're done debugging.
        */
        #define malloc_comment(memory_size, comment)           (malloc(memory_size))
        #define calloc_comment(obj_num, obj_size, comment)     (calloc(obj_num, obj_size))
        #define realloc_comment(pointer, obj_size, comment)    (realloc(pointer, memory_size))
        #define free_comment(pointer, comment)                 (free(pointer))

    #endif /* PANCAKE_MEMORY_DEBUG_ENABLE */

#endif /* PANCAKE_MEMORY_DEBUG_H */
