#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

#define DOT_TIME_MS 200   // Duration of a dot
#define DASH_TIME_MS 600  // Duration of a dash (3x dot time)
#define GAP_TIME_MS 200   // Gap between elements
#define LETTER_GAP_MS 600 // Gap between letters
#define WORD_GAP_MS 1400  // Gap between words

#define LED0_NODE DT_ALIAS(led0)
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

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

int main(void) {
    int ret;
    
    printf("Your app for the NUCLEO-F429ZI is working!\n");

    if (!gpio_is_ready_dt(&led)) {
        printf("Error: GPIO device is not ready\n");
        return 0;
    }

    ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
    if (ret < 0) {
        printf("Error: Failed to configure LED pin\n");
        return 0;
    }

    while (1) {
        blink_sos();
    }

    return 0;
}
