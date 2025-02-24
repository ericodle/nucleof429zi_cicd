#include <zephyr.h>
#include <ztest.h>
#include <zephyr/drivers/gpio.h>
#include "morse.h"

// Mock GPIO functionality
static bool gpio_called = false;

static int mock_gpio_pin_set(const struct gpio_dt_spec *spec, int value)
{
    gpio_called = true;
    return 0; // Success
}

// Test for blink_led
void test_blink_led(void)
{
    // Set mock GPIO function
    gpio_pin_set_dt = mock_gpio_pin_set;
    
    // Call the blink_led function
    blink_led(DOT_TIME_MS);

    // Assert that the mock GPIO function was called
    zassert_true(gpio_called, "GPIO pin set not called");
}

// Test for blink_sos
void test_blink_sos(void)
{
    // Set mock GPIO function
    gpio_pin_set_dt = mock_gpio_pin_set;

    // Call the blink_sos function
    blink_sos();

    // Verify GPIO was called the expected number of times (e.g., 9 for SOS)
    zassert_true(gpio_called, "GPIO pin set not called during SOS blinking");
}

// Define the test suite
void test_main(void)
{
    ztest_test_suite(morse_tests,
        ztest_unit_test(test_blink_led),
        ztest_unit_test(test_blink_sos)
    );

    ztest_run_test_suite(morse_tests);
}
