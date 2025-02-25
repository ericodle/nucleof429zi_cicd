#include <check.h>
#include <stdio.h>

// Function to test
int add(int a, int b) {
    return a + b;
}

// Test case
START_TEST(test_addition) {
    ck_assert_int_eq(add(2, 3), 5);
    ck_assert_int_eq(add(-1, 1), 0);
}
END_TEST

// Test suite setup
Suite *math_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("Math");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_addition);
    suite_add_tcase(s, tc_core);

    return s;
}

// Main function to run the tests
int main(void) {
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = math_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? 0 : 1;
}
