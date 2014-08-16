#include "bloom.h"

char * init (void) {
	return	setlocale (LC_ALL, "");
}

	
BLOOM * new_bloom(size_t element_size_bits, uint32_t num_elements, encoding encoding){
	BLOOM * self = NULL;
	self = (BLOOM *)malloc(sizeof(BLOOM) );
	if ( !(num_elements && element_size_bits ) ){
		return NULL;
	}
  self->encoding = encoding;
	self->element_size_bits = element_size_bits;
	self->num_elements = num_elements;
	self->array = calloc(num_elements, element_size_bits/8);
	return self;
}

int destroy_bloom(BLOOM * bloom_array){
	int success = 0;
	free(bloom_array->array);
	free(bloom_array);
	return success;
}

int found(BLOOM * b, STRING_STRUCT * string){
	int success = 0;
	uint32_t hashval1 = XXH32(string->string,string->num_chars * string->length_in_bytes, HASHVAL1);	
	uint32_t hashval2 = XXH32(string->string,string->num_chars * string->length_in_bytes, HASHVAL2);	
	//TODO: a more clever way to do this
	switch (b->element_size_bits) {
		case 32:
			success =  check_bit( ( (uint32_t *)(b->array))[hashval1 % b->num_elements ], hashval2 %  b->element_size_bits ) && 
					check_bit( ( (uint32_t *)(b->array))[hashval2 % b->num_elements ], hashval1 % b->element_size_bits);
		break;
	case 16:
		success =  check_bit( ( (uint32_t *)(b->array))[hashval1 % b->num_elements ], hashval2 %  b->element_size_bits ) && 
				check_bit( ( (uint32_t *)(b->array))[hashval2 % b->num_elements ], hashval1 % b->element_size_bits);
		break;
	case 8:
		success =  check_bit( ( (uint8_t *)(b->array))[hashval1 % b->num_elements ], hashval2 %  b->element_size_bits ) && 
				check_bit( ( (uint32_t *)(b->array))[hashval2 % b->num_elements ], hashval1 % b->element_size_bits);
		break;
	default:
		success = 0;
		break;
	}
	return success;
}

STRING_STRUCT * new_string_struct(void * string, encoding encoding, unsigned int num_chars, unsigned int element_length_in_bytes){
	STRING_STRUCT * self = NULL;
	//needs to be some size
	if ( !(num_chars && element_length_in_bytes ) ){
		return NULL;
	}
	self = (STRING_STRUCT *) malloc(sizeof(STRING_STRUCT) );			
	self->string = calloc(num_chars + 1, element_length_in_bytes);
	self->length_in_bytes = element_length_in_bytes;
	self->num_chars = num_chars;
	memcpy (self->string, string, (num_chars + 1) * element_length_in_bytes);
	self->num_chars = num_chars;
	self->encoding = encoding;
	return self;
}

int add_to_bloom(BLOOM * bloom_array, char * string){ //assumes utf-8 encoding for now
	int return_val = 0;
	//strlen because assuming utf-8 coding, change when we change
	int length_in_bytes = strlen(string);
	STRING_STRUCT * string_container = new_string_struct(string, UTF8, length_in_bytes, 1);
	if ( set_bloom_element(bloom_array, string_container) ){
		return_val = 1;
	}
	destroy_string_struct(string_container);	
	return return_val;
}



int set_bloom_element(BLOOM * b, STRING_STRUCT * string){
	int return_val = 1;
	uint32_t hashval1 = XXH32(string->string,string->num_chars * string->length_in_bytes, HASHVAL1);	
	uint32_t hashval2 = XXH32(string->string,string->num_chars * string->length_in_bytes, HASHVAL2);	
	switch (b->element_size_bits) {
		case 32:
			set_bit( ( (uint32_t *)(b->array))[hashval1 % (uint32_t) (b->num_elements) ], hashval2 % (uint32_t) ( b->element_size_bits ));
			set_bit( ( (uint32_t *)(b->array))[hashval2 % (uint32_t) (b->num_elements) ], hashval1 % (uint32_t) ( b->element_size_bits ));
		break;
	case 16:
		set_bit( ( (uint16_t *)(b->array))[hashval1 % (uint16_t) (b->num_elements) ], hashval2 % (uint16_t) ( b->element_size_bits ));
		set_bit( ( (uint16_t *)(b->array))[hashval2 % (uint16_t) (b->num_elements) ], hashval1 % (uint16_t) ( b->element_size_bits ));
		break;
	case 8:
		set_bit( ( (uint8_t *)(b->array))[hashval1 % (uint8_t) (b->num_elements) ], hashval2 % (uint8_t) ( b->element_size_bits ));
		set_bit( ( (uint8_t *)(b->array))[hashval2 % (uint8_t) (b->num_elements) ], hashval1 % (uint8_t) ( b->element_size_bits ));
		break;
	default:
		return_val = 0;
		break;
	}
	return return_val;
}

//TODO

STRING_STRUCT * new_string_struct_encoding(STRING_STRUCT * string, encoding encoding){
	STRING_STRUCT * self = NULL;
	
	return self;
}

STRING_STRUCT * new_string_struct_size(STRING_STRUCT * string, int length_in_bytes){
	STRING_STRUCT * return_val = NULL;
	return return_val;
}


STRING_STRUCT * copy_string_struct(STRING_STRUCT * string){
	STRING_STRUCT * self = NULL;
	
	return self;
}

int destroy_string_struct(STRING_STRUCT * string){
	int success = 0;	
	free(string->string);
	free(string);	
	return success;
}

