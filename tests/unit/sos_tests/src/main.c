#include <zephyr/ztest.h>
#include <stdio.h>

ZTEST(app_test, test_printf)
{
    printk("Your app for the NUCLEO-F429ZI is working!\n");
    zassert_true(1, "Printf test passed!");
}

ZTEST_SUITE(app_test, NULL, NULL, NULL, NULL, NULL);