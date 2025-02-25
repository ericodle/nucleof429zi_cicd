// app/src/morse.c
#include "morse.h"

#define LED0_NODE DT_ALIAS(led0)
const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

void blink_led(int duration) {
    mock_gpio_pin_set_dt(&led, 1);
    mock_k_msleep(duration);
    mock_gpio_pin_set_dt(&led, 0);
    mock_k_msleep(GAP_TIME_MS);
}

void blink_sos() {
    int sos_pattern[] = {DOT_TIME_MS, DOT_TIME_MS, DOT_TIME_MS,  
                         DASH_TIME_MS, DASH_TIME_MS, DASH_TIME_MS,
                         DOT_TIME_MS, DOT_TIME_MS, DOT_TIME_MS};
    
    for (int i = 0; i < 9; i++) {
        blink_led(sos_pattern[i]);
        if (i == 2 || i == 5) {
            mock_k_msleep(LETTER_GAP_MS);
        }
    }
    mock_k_msleep(WORD_GAP_MS);
}
