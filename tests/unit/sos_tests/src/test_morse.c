#include <zephyr/ztest.h>
#include "morse.h"

/* Mock GPIO function */
int gpio_pin_set_dt(const struct gpio_dt_spec *spec, int value) {
    return 0;
}

void k_msleep(int ms) {
    /* Skip actual sleeping */
}

ZTEST(test_morse, test_blink_led) {
    blink_led(200);  // Test calling blink_led with a dot duration
    blink_led(600);  // Test calling blink_led with a dash duration
}

ZTEST(test_morse, test_blink_sos) {
    blink_sos();  // Ensure SOS function runs without error
}

ZTEST_SUITE(test_morse, NULL, NULL, NULL, NULL, NULL);
