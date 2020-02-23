#include <stdlib.h> /* For stdlib memory functions. */
#include <stdio.h>  /* For printf() and puts().     */


#include "pancake_memory_debug_internal.h"


/* ------------------ Internal memory tracking variables ------------------- */

static int memory_leak_count = 0;
static size_t bytes_allocated_count = 0;




static void pancake_memory_internal_comment(const char* comment) {
    printf("\n-- %s\n", comment);
}

static void pancake_memory_internal_tracking_update(const int    leak_count,
                                                    const size_t bytes_count) {
    memory_leak_count      += leak_count;
    bytes_allocated_count  += bytes_count;
}


/* ----------------------- Standard memory functions ----------------------- */


void* pancake_memory_internal_malloc(const size_t memory_size,
                                     const char*  file,
                                     const int    line) {

    void* pointer = malloc(memory_size);
    printf(
        "%s:%d - Allocated %d bytes at %p with malloc().\n",
        file, line,
        memory_size, pointer
    );
    pancake_memory_internal_tracking_update(1, memory_size);
    return pointer;

}

void* pancake_memory_internal_calloc(const size_t object_num,
                                     const size_t object_size,
                                     const char*  file,
                                     const int    line) {

    void* pointer = calloc(object_num, object_size);
    printf(
        "%s:%d: - Allocated %d bytes (%d blocks) at %p with calloc().\n",
        file, line,
        object_num * object_size, object_num, pointer
    );
    pancake_memory_internal_tracking_update(1, object_num * object_size);
    return pointer;

}

void* pancake_memory_internal_realloc(void*        pointer,
                                      const size_t old_size,
                                      const size_t new_size,
                                      const char*  file,
                                      const int    line) {

    pointer = realloc(pointer, new_size);
    printf(
        "%s:%d: - Reallocated %d bytes to %d bytes at %p with realloc().\n",
        file, line,
        old_size, new_size, pointer
    );
    pancake_memory_internal_tracking_update(0, new_size - old_size);
    return pointer;

}

void pancake_memory_internal_free(void*        pointer,
                                  const size_t memory_size,
                                  const char*  file,
                                  const int    line) {

    printf("%s:%d: Freed %d bytes at %p.\n", file, line, memory_size, pointer);
    pancake_memory_internal_tracking_update(-1, -memory_size);
    free(pointer);

}


/* ----------------- Memory functions with comment option ------------------ */


void* pancake_memory_internal_malloc_comment(const size_t memory_size,
                                             const char*  comment,
                                             const char*  file,
                                             const int    line) {
    pancake_memory_internal_comment(comment);
    return pancake_memory_internal_malloc(memory_size, file, line);
}

void* pancake_memory_internal_calloc_comment(const size_t object_num,
                                             const size_t object_size,
                                             const char*  comment,
                                             const char*  file,
                                             const int    line) {
    pancake_memory_internal_comment(comment);
    return pancake_memory_internal_calloc(object_num, object_size, file, line);
}

void* pancake_memory_internal_realloc_comment(void*        pointer,
                                              const size_t old_size,
                                              const size_t new_size,
                                              const char*  comment,
                                              const char*  file,
                                              const int    line) {
    pancake_memory_internal_comment(comment);
    return pancake_memory_internal_realloc(pointer, old_size, new_size, file, line);
}

void pancake_memory_internal_free_comment(void*        pointer,
                                          const size_t memory_size,
                                          const char*  comment,
                                          const char*  file,
                                          const int    line) {
    pancake_memory_internal_comment(comment);
    pancake_memory_internal_free(pointer, memory_size, file, line);
}


/* ------------------------ Memory report functions ------------------------ */


int pancake_memory_get_memory_leak_count(void) {
    return memory_leak_count;
}

size_t pancake_memory_get_bytes_allocated_count(void) {
    return bytes_allocated_count;
}

void pancake_memory_report(void) {

    #if defined(PANCAKE_MEMORY_DEBUG_ENABLE)
        puts("");
        printf("Total memory currently allocated: %d bytes.\n",
               pancake_memory_get_bytes_allocated_count());
        printf("Total blocks currently not freed: %d blocks.\n",
               pancake_memory_get_memory_leak_count());
    #endif

}
