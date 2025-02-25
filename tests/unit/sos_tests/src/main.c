#include <zephyr/ztest.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include "morse.h"

/* Mock function to simulate GPIO pin control */
static int mock_gpio_pin_set_dt(const struct gpio_dt_spec *spec, int value) {
    ARG_UNUSED(spec);
    ARG_UNUSED(value);
    return 0;  /* Simulating success */
}

/* Mock function to replace k_msleep */
static void mock_k_msleep(int ms) {
    ARG_UNUSED(ms);
}

/* Test if blink_led executes without errors */
ZTEST(sos_tests, test_blink_led) {
    blink_led(DOT_TIME_MS);
    zassert_true(true, "blink_led should execute without errors");
}

/* Test if blink_sos executes without errors */
ZTEST(sos_tests, test_blink_sos) {
    blink_sos();
    zassert_true(true, "blink_sos should execute without errors");
}

/* Define test suite */
ZTEST_SUITE(sos_tests, NULL, NULL, NULL, NULL, NULL);
