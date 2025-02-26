 #include <zephyr/ztest.h>


 ZTEST_SUITE(framework_tests, NULL, NULL, NULL, NULL, NULL);
 
 /**
  * @brief Test Asserts
  *
  * This test verifies some of the assert macros built into ztest.
  *
  */
 ZTEST(framework_tests, test_assert)
 {
     zassert_true(1, "1 is false");
     zassert_false(0, "0 is true");
     zassert_is_null(NULL, "NULL is not NULL");
     zassert_not_null("validate-test", "\"validate-test\" is NULL");
     zassert_equal(1, 1, "1 is not equal to 1");
     zassert_equal_ptr(NULL, NULL, "NULL is not equal to NULL");
 }