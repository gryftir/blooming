#include "bloom.h"

int main(int argc, char ** argv) {
	uint32_t * i = NULL;
	BLOOM * b = new_bloom(32, 10, UTF8);
	for( i = (uint32_t *) (b->array); i <  (uint32_t *)(b->array + (sizeof(uint32_t) * b->num_elements)); i++){
		printf("%"PRIu32"\n", *i); 
	}
	printf("\n\n");
	char * string = "ᴁ test";
	add_to_bloom(b, string);
	for(i = (uint32_t *) (b->array); i <  (uint32_t *)(b->array + (sizeof(uint32_t) * b->num_elements)); i++){
		printf("%"PRIu32"\n", *i); 
	}
	destroy_bloom(b);
		return 0;

}
