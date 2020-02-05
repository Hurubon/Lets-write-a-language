#include <stdio.h>
#include <stdlib.h>

#include "lib/bool/bool.h"
#include "lib/z_algorithm/z_algorithm.h"

void scan_label(FILE* file_ptr, char input) {
	
	bool is_label_char;
	char* token = malloc(128);
	int i = 0;
	
	do {
		token[i++] = input;
		input = fgetc(file_ptr);
		is_label_char = isalpha(input) || input == '_';
	} while (is_label_char);
	
	token[i] = '\0';
	
	printf("{'%s': 'label'}\n", token);
	
	fseek(file_ptr, -1, SEEK_CUR);
	
	free(token);
	
}

void lex(FILE* file_ptr, char input) {
	
	if (input == ' ' || input == '\t' || input == '\n') {
		return;
	}
	else if (isalpha(input) || input == '_') {
		scan_label(file_ptr, input);
	} 
	else if (z_find("()[]{}", &input)) {
		printf("{'%c': 'bracket'}\n", input);
	}
	else {
		printf("{'%c'}\n", input);
	}
	
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
