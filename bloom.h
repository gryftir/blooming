#ifndef _bloom_h_
#define _bloom_h_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h> 
#include <glib.h>
#include <glib/gprintf.h>

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
} SEARCH;


//set locale
char * init(void);

//BLOOM

BLOOM * new_bloom(size_t element_size_bits, long num_elements, encoding encoding);
int destroy_bloom(BLOOM * bloom_array);


int found(BLOOM * bloom_array, SEARCH * string);

//SEARCH

SEARCH * new_search(void * string, encoding encoding, int char_size);

//produces new copy of search (possibly with changes

SEARCH * new_search_encoding(SEARCH * string, encoding  encoding);
SEARCH * new_search_size(SEARCH * string, int char_size);
SEARCH * copy_search(SEARCH * string); 

int destroy_search(SEARCH * string);




/*

*/

#endif
