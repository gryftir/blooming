#ifndef _bloom_h_
#define _bloom_h_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h> 
#include <glib.h>
#include <glib/gprintf.h>
#include <inttypes.h>
#include "xxHash/xxhash.h"

//constants for hashing to element
#define HASHVAL1 1
#define HASHVAL2 2


typedef enum {UTF8, UTF16, UNICODE} encoding;

typedef struct bloom {
	uint32_t num_elements;
	unsigned int element_size_bits;
	void * array;
	encoding encoding;
} BLOOM;	

typedef struct search_string {
	void * string;
	uint32_t length_in_bytes;
	int num_chars;	
	encoding encoding;
} STRING_STRUCT;


//set locale
char * init(void);

//BLOOM

BLOOM * new_bloom(size_t element_size_bits, uint32_t num_elements, encoding encoding);
int destroy_bloom(BLOOM * bloom_array);


int found(BLOOM * bloom_array, STRING_STRUCT * string);

int add_to_bloom(BLOOM * bloom_array, char * string); //assumes utf-8 encoding for now
int set_bloom_element(BLOOM * b,  STRING_STRUCT * string);
//STRING_STRUCT

STRING_STRUCT * new_string_struct(void * string, encoding encoding, unsigned int num_chars, unsigned int element_length_in_bytes);

//produces new copy of string_struct (possibly with changes

STRING_STRUCT * new_string_struct_encoding(STRING_STRUCT * string, encoding  encoding);
STRING_STRUCT * new_string_struct_size(STRING_STRUCT * string, int length_in_bytes);
STRING_STRUCT * copy_string_struct(STRING_STRUCT * string); 

int destroy_string_struct(STRING_STRUCT * string);

//bit macros
#define  check_bit(value, bit) ((uint32_t)(value)) & ( ((uint32_t)1) << (bit)) 
#define  get_set_bit(value, bit)   ((uint32_t)(value)) |( ((uint32_t)1) << (bit))  
#define  set_bit(value, bit)  (value) = get_set_bit((value), (bit)) 


/*

*/

#endif
