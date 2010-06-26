#include <string.h>
#include <stdlib.h>

#include "check-plus.h"


#define SUITE_NAME example
BEGIN_SUITE("Example test suite");

#define TEST_CASE core
BEGIN_TEST_CASE("Core tests");

TEST(strcmp)
{
    fail_unless(strcmp("hello", "HELLO") != 0);
    fail_unless(strcasecmp("hello", "HELLO") == 0);
}
END_TEST

TEST(strcat)
{
    char buf[1024] = {0};
    strcat(buf, "Hello, ");
    strcat(buf, "World.");
    fail_unless(strcmp(buf, "Hello, World.") == 0);
}
END_TEST

END_TEST_CASE;
#undef TEST_CASE

char *ptr;

void malloc_setup(void) {
    ptr = malloc(1024);
}

void malloc_teardown(void) {
    free(ptr);
}

#define TEST_CASE malloc
BEGIN_TEST_CASE("Fun with malloc");
DEFINE_FIXTURE(malloc_setup, malloc_teardown);

TEST(use_malloced)
{
    ptr[0] = 0;
    strcpy(ptr, "Test string");
    fail_unless(strcmp(ptr, "Test string") == 0);
}
END_TEST

END_TEST_CASE;
#undef TEST_CASE
END_SUITE;
#undef SUITE_NAME

Suite *get_suite() {
    return construct_test_suite(example);
}

int main()
{
    int failed;

    SRunner *sr = srunner_create(get_suite());

    srunner_run_all(sr, CK_ENV);
    failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return failed != 0;
}
