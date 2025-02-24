#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include "morse.h"  // Include the header for blink_led() and blink_sos()

int main(void) {
    printf("Your app for the NUCLEO-F429ZI is working!\n");

    while (1) {
        blink_sos();  // Call the function to blink SOS in Morse code
    }

    return 0;
}
