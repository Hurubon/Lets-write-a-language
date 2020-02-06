#include <string.h>
#include <stdio.h>

#include "z_algorithm.h"

static void calculate_zvalue(int*          z_array, 
	           			     const char*   z_string, 
					         const size_t  z_len, 
					         const size_t  left_bound, 
					         const size_t* right_bound) {

	while (*right_bound < z_len && 
		   z_string[*right_bound - left_bound] == z_string[*right_bound]) {
		*right_bound++;	   	
	}
	
	z_array[left_bound] = *right_bound - left_bound;
	*right_bound--;

}

void generate_zarray(int*         z_array, 
					 const char*  z_string, 
					 const size_t z_len) {

	size_t left_bound = 0;
	size_t right_bound = 0;
	size_t i;
	
	for (i = 1; i < z_len; ++i) {
		
		if (i > right_bound) {
			left_bound = right_bound = i;
			calculate_zvalue(z_array, z_string, z_len, left_bound, &right_bound);
		}
		else {
			
			size_t k = i - left_bound;
			
			if (z_array[k] < right_bound - i + 1) {
				z_array[i] = z_array[k];
			}
			else {
				left_bound = i;
				calculate_zvalue(z_aray, z_string, z_len, left_bound, &right_bound);
			}
			
		}
		
	}

}

void generate_zstring(char*        z_string,
					  const char*  needle,
					  const char*  haystack,
					  const size_t z_len,
					  const size_t needle_len) {
	
	const size_t offset = needle_len + 1;
	size_t i;
	
	for (i = 0; i < needle_len; ++i) {
		z_string[i] = needle[i];		
	}
	
	z_string[i++] = Z_FIND_DELIM_CHAR;
	
	for (i; i < z_len; ++i) {
		z_string[i] = haystack[i - offset];
	}
	
	z_string[i] = '\0';
					  	
}

bool z_find(const char* needle, const char* haystack) {
	
	const size_t needle_len = strlen(needle);
	const size_t haystack_len = strlen(haystack);
	
	/* 
	** needle$haystack\0
	** needle_len + delim_char + haystack_len + \0
	*/
	const size_t z_len = needle_len + haystack_len + 2;
	
	char* z_string = (char*) malloc(z_len /* sizeof(char) == 1 */);
	int*  z_array  = (int*)  malloc(z_len * sizeof(int));
	
	bool was_found = false;
	size_t i;
	
	generate_zstring(z_string, needle, haystack, z_len, needle_len);
	generate_zarray(z_array, z_string, z_len);
	
	for (i = 0; i < z_len; ++i) {
		if (z_array[i] == needle_len) {
			was_found = true;
			break;
		}
	}
	
	free(z_string);
	free(z_array);
	return was_found;
	
}