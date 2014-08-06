#include <glib.h>
#include "../bloom.h"

typedef struct {
	char * locale;
} locale;

//setup
void setup_func(locale * loc, gconstpointer test_data) {
	char * temp = setlocale(LC_ALL, NULL);
	loc->locale = strdup(temp);
	return;
}

//teardown
void teardown_func(locale * loc, gconstpointer test_data) {
	setlocale(LC_ALL, loc->locale);
	free (loc->locale);
	return;
}

//test_init

void test_init (locale * loc, gconstpointer ignored) {
	char * current = init();
	g_assert_cmpstr(current, !=, loc->locale);
	g_assert_cmpstr(current, ==, "en_US.UTF-8");
	return;
}

int main(int argc, char *argv[])
{
	g_test_init(&argc, &argv, NULL);
	g_test_add("/set1/init test", locale, NULL, setup_func, test_init, teardown_func);
	return g_test_run();
}
