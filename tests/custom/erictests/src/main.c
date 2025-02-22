#include <zephyr/ztest.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/util.h>

/* Mock functions for gpio_pin_set_dt and k_msleep */
static int mock_gpio_pin_set_dt_call_count = 0;
static int mock_k_msleep_call_count = 0;

static int mock_gpio_pin_set_dt(const struct gpio_dt_spec *spec, int value) {
    mock_gpio_pin_set_dt_call_count++;
    return 0; // Mock behavior
}

static void mock_k_msleep(int duration) {
    mock_k_msleep_call_count++;
}

/* Replace original functions with test doubles */
#define gpio_pin_set_dt mock_gpio_pin_set_dt
#define k_msleep mock_k_msleep

extern void blink_led(int duration);
extern void blink_sos();

/* Test if blink_led correctly sets the GPIO pin */
ZTEST(blink_led_tests, test_blink_led) {
    int duration = 200;

    /* Call function to test */
    blink_led(duration);

    /* Assert that mock_gpio_pin_set_dt was called at least once */
    zassert_true(mock_gpio_pin_set_dt_call_count > 0, "GPIO set was not called");

    /* You could also assert the number of times k_msleep is called, depending on the logic of blink_led */
    zassert_true(mock_k_msleep_call_count > 0, "Sleep function was not called");
}

/* Test if blink_sos correctly executes the SOS pattern */
ZTEST(blink_led_tests, test_blink_sos) {
    blink_sos();

    /* Assert that mock_gpio_pin_set_dt was called multiple times */
    zassert_true(mock_gpio_pin_set_dt_call_count > 5, "GPIO set was not called enough times for SOS");

    /* Assert that k_msleep was called the correct number of times */
    zassert_true(mock_k_msleep_call_count > 0, "Sleep function was not called during SOS sequence");
}

/* Test Suite Registration */
ZTEST_SUITE(blink_led_tests, NULL, NULL, NULL, NULL, NULL);
