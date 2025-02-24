// morse.c
#include "morse.h"

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(DT_ALIAS(led0), gpios);

void blink_led(int duration) {
    gpio_pin_set_dt(&led, 1);   // Turn LED on
    k_msleep(duration);
    gpio_pin_set_dt(&led, 0);   // Turn LED off
    k_msleep(GAP_TIME_MS);      // Gap between elements
}

void blink_sos(void) {
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
