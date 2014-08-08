#ifndef _bloom_h_
#define _bloom_h_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h> 
#include <glib.h>
#include <glib/gprintf.h>

//constants for hashing to element
#define HASHVAL1 1
#define HASHVAL2 2

//constants for hashing to bit
#define BITVAL1 11
#define BITVAL2 22

typedef enum {UTF8, UTF16, UNICODE} encoding;

typedef struct bloom {
	long num_elements;
	size_t element_size_bits;
	void * array;
	encoding encoding;
} BLOOM;	

typedef struct search_string {
	void * searchstring;
	long byte_length;
	int char_size;	
	encoding encoding;
} STRING_STRUCT;


//set locale
char * init(void);

//BLOOM

BLOOM * new_bloom(size_t element_size_bits, long num_elements, encoding encoding);
int destroy_bloom(BLOOM * bloom_array);


int found(BLOOM * bloom_array, STRING_STRUCT * string);

int add_to_bloom(BLOOM * bloom_array, char * string); //assumes utf-8 encoding for now
int set_bloom_element(void * element, size_t bit_size, STRING_STRUCT * string);
//STRING_STRUCT

STRING_STRUCT * new_search(void * string, encoding encoding, int char_size);

//produces new copy of search (possibly with changes

STRING_STRUCT * new_search_encoding(STRING_STRUCT * string, encoding  encoding);
STRING_STRUCT * new_search_size(STRING_STRUCT * string, int char_size);
STRING_STRUCT * copy_search(STRING_STRUCT * string); 

int destroy_search(STRING_STRUCT * string);

//bit macros
#define  check_bit(value, bit) ((unsigned long)(value)) & (1UL << (bit)) 
#define  get_set_bit(value, bit)   ((unsigned long)(value)) | (1UL << (bit))
#define  set_bit(value, bit)  (value) = get_set_bit((value), (bit)) 


/*

*/

#endif
