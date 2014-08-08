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

int found(BLOOM * bloom_array, STRING_STRUCT * string){
	int success = 0;
	return success;
}

STRING_STRUCT * new_search(void * string, encoding encoding, int char_size){
	STRING_STRUCT * self = NULL;
	
	return self;
}

STRING_STRUCT * new_search_encoding(STRING_STRUCT * string, encoding encoding){
	STRING_STRUCT * self = NULL;
	
	return self;
}

STRING_STRUCT * copy_search(STRING_STRUCT * string){
	STRING_STRUCT * self = NULL;
	
	return self;
}

int destroy_search(STRING_STRUCT * string){
	int success = 0;	
	return success;
}

