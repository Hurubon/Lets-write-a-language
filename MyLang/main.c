#include <stdio.h>
#include <stdlib.h>

#include "lib/bool/bool.h"
#include "lib/z_algorithm/z_algorithm.h"
void scan_names(FILE* file_ptr, char** token_ptr, size_t token_size, const char input) {

	char c = input;
	size_t curr_size = token_size;
	size_t i;
	
	for (i = 0; (c = fgetc(file_ptr)) != ' '; ++i) {
		
		(*token_ptr)[i] = c;
		
		if (i < curr_size) {
			continue;
		} 
		
		char* temp = realloc(*token_ptr, curr_size * 2);
		curr_size *= 2;
		
		if (temp == NULL) {
			exit(1);
		}
		
		*token_ptr = temp;
		
	}

}

void lex(FILE* file_ptr, char input) {
	
	const size_t token_size = 64;
	char token[token_size];
	
	if (isalpha(input) || input == '_') {
		scan_names(file_ptr, &token, token_size, input);
	}
	
	printf("%s", name);
	
}

int main(void) {

	FILE* file_ptr = fopen("foo.txt", "r");
	
	if (file_ptr == NULL) {
		return 1;
	}
	
	char input;
	
	while ((input = fgetc(file_ptr)) != EOF) {
		lex(file_ptr, input);
	}

    getchar();
    return 0;

}
