#include <glib.h>
#include "../bloom.h"


typedef struct {
	BLOOM * bloom;
	char * locale;
} bloom_struct;

typedef struct {
	STRING_STRUCT * search;
} search_struct;

//setup
void setup_init(bloom_struct * loc, gconstpointer test_data) {
	loc->locale = strdup(setlocale(LC_ALL, NULL));
	return;
}

//setup bloom
void setup_bloom(bloom_struct * bloom, gconstpointer test_data) {
	setup_init(bloom, NULL);	
	bloom->bloom = new_bloom(32, 12, UTF8);
	return;
}


//teardown
void teardown_init(bloom_struct * loc, gconstpointer test_data) {
	setlocale(LC_ALL, loc->locale);
	free (loc->locale);
	return;
}

//teardown bloom
void teardown_bloom(bloom_struct * bloom, gconstpointer test_data) {
	teardown_init(bloom, NULL);
	destroy_bloom(bloom->bloom);
	return;
}

//test_init

void test_init (bloom_struct * loc, gconstpointer ignored) {
	char * current = init();
	g_assert_cmpstr(current, !=, loc->locale);
	g_assert_cmpstr(current, ==, "en_US.UTF-8");
	return;
}
//test object created successfully

//test bloom
void test_bloom(bloom_struct * bloom, gconstpointer ignored) {
	g_assert_cmpint(bloom->bloom->element_size_bits, ==,  32);
	g_assert_cmpint( bloom->bloom->num_elements,==, 12);	
	g_assert(bloom->bloom->encoding == UTF8);
	return;
}

//test check_bit get_set_bit set_bit
void test_bit(bloom_struct * b, gconstpointer ignored) {
	uint32_t l = 2;
	uint32_t ltemp = 0;
	g_test_message("check_bit ");
	g_assert( ((uint32_t *)(b->bloom->array))[1]  == ltemp );
	g_assert_cmpint( ((uint32_t *)(b->bloom->array))[1],  ==, ltemp );
	g_assert_cmpint(check_bit(	((uint32_t *)(b->bloom->array))[1], 1), == , 0);

	g_test_message("get_set_bit ");
	ltemp = get_set_bit( ((uint32_t *)(b->bloom->array))[1] , l);
	g_assert_cmpint(ltemp, ==, 4);

	g_test_message("set_bit ");
	set_bit( ( ((uint32_t *)(b->bloom->array))[1]) , l);
	g_assert_cmpint( check_bit ( ((uint32_t *)(b->bloom->array))[1], l), ==, 4);
	g_assert( ((uint32_t *)(b->bloom->array))[1]  == ltemp );
	return;
}

void test_new_string(bloom_struct * b, gconstpointer ignored) {
	char * teststring = "ᴁ test";
	STRING_STRUCT * holder = new_string_struct((void*)teststring, UTF8, strlen(teststring), sizeof(char));
	g_assert(holder);
	g_assert_cmpstr((char *)(holder->string), ==, teststring);
	g_assert(holder->num_chars == strlen(teststring));
	g_assert(holder->encoding == UTF8);
	g_assert(holder->length_in_bytes == sizeof(*teststring));
	destroy_string_struct(holder);
	return;
}
	

void test_add_to_bloom(bloom_struct * b, gconstpointer ignored) {
	char * teststring = "ᴁ test";
	bloom_struct compare;
	setup_bloom(&compare, NULL);	
	g_assert( 0 ==  memcmp(b->bloom->array, compare.bloom->array, 
				(b->bloom->element_size_bits / 8) * b->bloom->num_elements) );
	add_to_bloom(b->bloom, teststring);		
	g_assert(0 !=  memcmp(b->bloom->array, compare.bloom->array, 
				(b->bloom->element_size_bits / 8) * b->bloom->num_elements) );
	teardown_bloom(&compare, NULL);	
	return;
}


int main(int argc, char *argv[])
{
	g_test_init(&argc, &argv, NULL);
	g_test_add("/set1/init test", bloom_struct, NULL, setup_init, test_init, teardown_init);
	g_test_add("/set/bloom test", bloom_struct, NULL, setup_bloom, test_bloom, teardown_bloom);
	g_test_add("/set/bit test", bloom_struct, NULL, setup_bloom, test_bit, teardown_bloom);
	g_test_add("/set/new string test", bloom_struct, NULL, setup_bloom, test_new_string, teardown_bloom);
	g_test_add("/set/add_to_bloom test", bloom_struct, NULL, setup_bloom, test_add_to_bloom, teardown_bloom);
	return g_test_run();
}
