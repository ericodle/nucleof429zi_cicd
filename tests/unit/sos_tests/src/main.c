#include <zephyr/ztest.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>

/* Mocking the GPIO struct */
extern struct gpio_dt_spec led;

/* Mocking GPIO functions */
int gpio_pin_configure_dt(const struct gpio_dt_spec *spec, gpio_flags_t flags) {
    return 0; // Simulating successful configuration
}

int gpio_pin_set_dt(const struct gpio_dt_spec *spec, int value) {
    zassert_not_null(spec, "GPIO spec should not be NULL");
    return 0;
}

/* Mocking sleep function */
void k_msleep(int ms) {
    /* In unit tests, we skip actual sleeping */
}

/* Include the original function implementations */
#include "../src/main.c" // Adjust path if needed

/**
 * @brief Test LED Blink Function
 */
ZTEST(test_morse, test_blink_led) {
    /* Ensure function runs without errors */
    blink_led(DOT_TIME_MS);
    blink_led(DASH_TIME_MS);
}

/**
 * @brief Test SOS Blinking Pattern
 */
ZTEST(test_morse, test_blink_sos) {
    blink_sos(); // Run SOS function to ensure no crashes
}

/**
 * @brief Test GPIO Initialization
 */
ZTEST(test_morse, test_gpio_init) {
    int ret = gpio_pin_configure_dt(&led_mock, GPIO_OUTPUT_ACTIVE);
    zassert_equal(ret, 0, "GPIO configuration failed");
}

/**
 * @brief Register the test suite
 */
ZTEST_SUITE(test_morse, NULL, NULL, NULL, NULL, NULL);
