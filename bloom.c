#include "bloom.h"

char * init (void) {
	return	setlocale (LC_ALL, "");
}

	
BLOOM * new_bloom(size_t element_size_bits, long num_elements, encoding encoding){
	BLOOM * self = NULL;
	self = (BLOOM *)malloc(sizeof(BLOOM) );
	if (!self){
		return NULL;
	}
	self->encoding = encoding;
	self->element_size_bits = element_size_bits;
	self->num_elements = num_elements;
	self->array = calloc(num_elements, element_size_bits);
	return self;
}

int destroy_bloom(BLOOM * bloom_array){
	int success = 0;
	free(bloom_array->array);
	free(bloom_array);
	return success;
}

int found(BLOOM * bloom_array, SEARCH * string){
	int success = 0;
	
	return success;
}

SEARCH * new_search(void * string, encoding encoding, int char_size){
	SEARCH * self = NULL;
	
	return self;
}

SEARCH * new_search_encoding(SEARCH * string, encoding encoding){
	SEARCH * self = NULL;
	
	return self;
}

SEARCH * copy_search(SEARCH * string){
	SEARCH * self = NULL;
	
	return self;
}

int destroy_search(SEARCH * string){
	int success = 0;	
	return success;
}

