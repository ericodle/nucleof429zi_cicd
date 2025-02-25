// app/src/main.c
#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include "morse.h"

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
