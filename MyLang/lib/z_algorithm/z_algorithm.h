#ifndef Z_MATCH_ALGORITHM_H
#define Z_MATCH_ALGORITHM_H

#include <stddef.h>

#define Z_MATCH_DELIM_CHAR '$'

void calculate_z_value (const char*  s,
                        const size_t s_len,
                        size_t       L,
                        size_t*      R,
                        int*         Z);

void generate_z_array  (const char*  s,
                        const size_t s_len,
                        int* Z);

void generate_z_string (char*        z_string,
                        const char*  search_string,
                        const char*  sub_string,
                        size_t       z_len,
                        size_t       substr_len);

bool find              (const char* search_string,
                        const char* sub_string);

#endif /* Z_MATCH_ALGORITHM_H */
