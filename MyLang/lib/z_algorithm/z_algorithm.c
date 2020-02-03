#include <stdlib.h>
#include <string.h>
#include "../bool/bool.h"
#include "z_algorithm.h"

void calculate_z_value(const char*  s,
                       const size_t s_len,
                       size_t       L,
                       size_t*      R,
                       int*         Z) {
    while (*R < s_len && s[*R - L] == s[*R])
        ++(*R);
    Z[L] = *R - L;
    --(*R);
}

void generate_z_array(const char* s, const size_t s_len, int* Z) {

    size_t L = 0;
	size_t R = 0;
	size_t i;

    for (i = 1; i < s_len; ++i) {

        if (i > R) {

            L = R = i;
            calculate_z_value(s, s_len, L, &R, Z);

        } else {

            size_t k = i - L;

            if (Z[k] < R - i + 1) {
                Z[i] = Z[k];
            } else {
                L = i;
                calculate_z_value(s, s_len, L, &R, Z);
            }

        }


    }

}

void generate_z_string(char*       z_string,
                       const char* search_string,
                       const char* sub_string,
                       size_t      z_len,
                       size_t      substr_len) {
                       	
    size_t i;
    for (i = 0; i < z_len; ++i) {

        if (i < substr_len) {
            z_string[i] = sub_string[i];
        } else if (i == substr_len) {
            z_string[i] = Z_MATCH_DELIM_CHAR;
        } else {
            z_string[i] = search_string[i - substr_len - 1];
        }

    }

    z_string[z_len] = '\0';
    
}

bool z_find(const char* search_string, const char* sub_string) {

    bool was_found = false;

    const size_t srcstr_len = strlen(search_string);
    const size_t substr_len = strlen(sub_string);

    /* substr + Z_MATCH_DELIM_CHAR + srcstr + '\0' */
    const size_t z_len = 2 + srcstr_len + substr_len;

    int* Z         = (int*)  malloc(z_len * sizeof(int));
    char* z_string = (char*) malloc(z_len * sizeof(char));

    size_t i;

    generate_z_string(z_string, search_string, sub_string, z_len, substr_len);
    generate_z_array(z_string, z_len, Z);

    for (i = 0; i < z_len; ++i) {
        if (Z[i] == substr_len) {
            was_found = true;
            break;
        }
    }

    free(Z);
    free(z_string);
    return was_found;

}
