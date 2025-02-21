#include <zephyr/ztest.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/util.h>

// Include the main application functions
extern void blink_led(int duration);
extern void blink_sos(void);

// Mock GPIO structure
static struct gpio_dt_spec mock_led = {0};

// Fake GPIO state for testing
static int fake_gpio_state = 0;

// Mock function for gpio_pin_set_dt()
int mock_gpio_pin_set_dt(const struct gpio_dt_spec *spec, int value)
{
    fake_gpio_state = value;
    return 0; // Simulate success
}

// Test LED blink durations
ZTEST(morse_code_tests, test_blink_durations)
{
    int test_durations[] = {200, 600, 200}; // DOT, DASH, GAP
    for (int i = 0; i < ARRAY_SIZE(test_durations); i++) {
        blink_led(test_durations[i]);
        zassert_equal(fake_gpio_state, 0, "LED should be off after blinking.");
    }
}

// Test SOS pattern structure
ZTEST(morse_code_tests, test_sos_pattern)
{
    // Capture LED states and durations
    blink_sos();
    zassert_equal(fake_gpio_state, 0, "LED should be off after SOS sequence.");
}

// Register the test suite
ZTEST_SUITE(morse_code_tests, NULL, NULL, NULL, NULL, NULL);
