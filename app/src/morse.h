// app/src/morse.h
#ifndef MORSE_H
#define MORSE_H

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

#define DOT_TIME_MS 200   // Duration of a dot
#define DASH_TIME_MS 600  // Duration of a dash (3x dot time)
#define GAP_TIME_MS 200   // Gap between elements
#define LETTER_GAP_MS 600 // Gap between letters
#define WORD_GAP_MS 1400  // Gap between words

extern const struct gpio_dt_spec led;

void blink_led(int duration);
void blink_sos(void);

#endif // MORSE_H