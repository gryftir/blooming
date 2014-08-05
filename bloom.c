#include "bloom.h"

char * init (void) {
	return	setlocale (LC_ALL, "");
}

	
BLOOM * new_bloom(int element_size_bits, long num_elements, char * encoding){
	
	return;
}

int destroy_bloom(BLOOM * bloom_array){
	
	return;
}

int found(BLOOM * bloom_array, SEARCH * string){
	
	return;
}

SEARCH * new_search(void * string, char * encoding, int char_size){
	
	return;
}

SEARCH * new_search_encoding(SEARCH * string, char * encoding){
	
	return;
}

SEARCH * copy_search(SEARCH * string){
	
	return;
}

int destroy_search(SEARCH * string){
	
	return;
}

