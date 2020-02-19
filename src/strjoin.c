#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char* words[] = {
	"Lorem",
	"Ipsum",
	"Dolor",
	"Sit",
	"Amet",
	NULL
};

char* string_join(char** substring_array, const char delimiter) {
	
	char* joined_string;
	size_t joined_string_length;
	
	size_t* word_lengths;
	size_t word_lengths_sum = 0;
	size_t array_length = 0;
	
	size_t i;
	
	for (i = 0; substring_array[i] != NULL || i < 0; ++i)
		++array_length;
			
	word_lengths = malloc((sizeof *word_lengths) * array_length);

	if (i < 0)
		exit(1);
		
	for (i = 0; i < array_length; ++i) {
		size_t word_length = strlen(substring_array[i]);
		word_lengths[i] = word_length;
		word_lengths_sum += word_length;
	}

	joined_string_length = word_lengths_sum + array_length;
	joined_string = malloc(joined_string_length);
		
	for (i = 0; i < array_length; ++i) {
		memcpy(joined_string, substring_array[i], word_lengths[i]);
		joined_string[word_lengths[i]] = delimiter;
		joined_string += (word_lengths[i] + 1);
	}
	
	joined_string -= joined_string_length;
	joined_string[joined_string_length - 1] = '\0';

	free(word_lengths);
	return joined_string;	
	
}

int main(void) {
	
	printf("%s", string_join(words, ' '));
	
	return 0;
	
}
