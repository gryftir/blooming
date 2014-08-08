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
	char * temp = setlocale(LC_ALL, NULL);
	loc->locale = strdup(temp);
	return;
}

//setup bloom
void setup_bloom(bloom_struct * bloom, gconstpointer test_data) {
	setup_init(bloom, NULL);	
	bloom->bloom = new_bloom(32, 1024, UTF8);
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
	g_assert_cmpint( bloom->bloom->num_elements,==, 1024);	
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

int main(int argc, char *argv[])
{
	g_test_init(&argc, &argv, NULL);
	g_test_add("/set1/init test", bloom_struct, NULL, setup_init, test_init, teardown_init);
	g_test_add("/set/bloom test", bloom_struct, NULL, setup_bloom, test_bloom, teardown_bloom);
	g_test_add("/set/bit test", bloom_struct, NULL, setup_bloom, test_bit, teardown_bloom);
	return g_test_run();
}
