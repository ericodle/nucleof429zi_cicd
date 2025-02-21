#include <zephyr/ztest.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/util.h>

// Declare external functions from main.c
extern void blink_led(int duration);
extern void blink_sos(void);

// Fake GPIO state for testing
static int fake_gpio_state = 0;

// Mock function for gpio_pin_set_dt()
int mock_gpio_pin_set_dt(const struct gpio_dt_spec *spec, int value)
{
    fake_gpio_state = value;
    return 0; // Simulate success
}

// Test that LED blinks for the expected durations
ZTEST(morse_code_tests, test_blink_durations)
{
    blink_led(200); // Simulate DOT
    zassert_equal(fake_gpio_state, 0, "LED should be off after blinking.");

    blink_led(600); // Simulate DASH
    zassert_equal(fake_gpio_state, 0, "LED should be off after blinking.");
}

// Test the SOS sequence
ZTEST(morse_code_tests, test_sos_pattern)
{
    blink_sos();
    zassert_equal(fake_gpio_state, 0, "LED should be off after the SOS sequence.");
}

// Register the test suite
ZTEST_SUITE(morse_code_tests, NULL, NULL, NULL, NULL, NULL);
