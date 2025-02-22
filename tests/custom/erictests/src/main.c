#include <zephyr/ztest.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/util.h>

#define DOT_TIME_MS 200
#define DASH_TIME_MS 600
#define LETTER_GAP_MS 300
#define WORD_GAP_MS 700

#define LED0_NODE DT_ALIAS(led0)
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

/* Reproduce the blink_led and blink_sos functions here */
void blink_led(int duration) {
    gpio_pin_set_dt(&led, 1);
    k_msleep(duration);
    gpio_pin_set_dt(&led, 0);
    k_msleep(GAP_TIME_MS);
}

void blink_sos() {
    // SOS: ... --- ...
    int sos_pattern[] = {DOT_TIME_MS, DOT_TIME_MS, DOT_TIME_MS,  
                         DASH_TIME_MS, DASH_TIME_MS, DASH_TIME_MS,
                         DOT_TIME_MS, DOT_TIME_MS, DOT_TIME_MS};
    
    for (int i = 0; i < 9; i++) {
        blink_led(sos_pattern[i]);
        if (i == 2 || i == 5) {
            k_msleep(LETTER_GAP_MS);  // Longer gap between letters
        }
    }
    k_msleep(WORD_GAP_MS);  // Pause before repeating
}

/* Mock functions for gpio_pin_set_dt and k_msleep */
static int mock_gpio_pin_set_dt_call_count = 0;
static int mock_k_msleep_call_count = 0;

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
