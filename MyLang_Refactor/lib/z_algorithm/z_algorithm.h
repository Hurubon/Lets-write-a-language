#ifndef Z_FIND_ALGORITHM_H
#define Z_FIND_ALGORITHM_H

#include <stdlib.h>

#include "../bool/bool.h"

#define Z_FIND_DELIM_CHAR '$';

void generate_zstring(char* z_string,
					  const char* needle,
					  const char* haystack,
					  const size_t z_len,
					  const size_t needle_len);
					  
bool z_find(const char* needle, const char* haystack);

#endif /* Z_FIND_ALGORITHM_H */
