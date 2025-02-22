#include <zephyr/ztest.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

#define DOT_TIME_MS 200
#define DASH_TIME_MS 600
#define GAP_TIME_MS 200  
#define LETTER_GAP_MS 300
#define WORD_GAP_MS 700

#define LED0_NODE DT_ALIAS(led0)
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

struct blink_fixture {
    int mock_gpio_calls;
    int mock_sleep_calls;
};

static void *blink_setup(void)
{
    struct blink_fixture *fixture = malloc(sizeof(struct blink_fixture));
    zassume_not_null(fixture, "Fixture allocation failed");
    return fixture;
}

static void blink_before(void *f)
{
    struct blink_fixture *fixture = (struct blink_fixture *)f;
    fixture->mock_gpio_calls = 0;
    fixture->mock_sleep_calls = 0;
}

/* Mock functions */
static int mock_gpio_pin_set_dt_call_count = 0;
static int mock_k_msleep_call_count = 0;

void blink_led(int duration)
{
    mock_gpio_pin_set_dt_call_count++;
    k_msleep(duration);
    mock_gpio_pin_set_dt_call_count++;
    k_msleep(GAP_TIME_MS);
}

void blink_sos()
{
    int sos_pattern[] = {DOT_TIME_MS, DOT_TIME_MS, DOT_TIME_MS,  
                         DASH_TIME_MS, DASH_TIME_MS, DASH_TIME_MS,
                         DOT_TIME_MS, DOT_TIME_MS, DOT_TIME_MS};
    
    for (int i = 0; i < 9; i++) {
        blink_led(sos_pattern[i]);
        if (i == 2 || i == 5) {
            k_msleep(LETTER_GAP_MS);
        }
    }
    k_msleep(WORD_GAP_MS);
}

/* Test if blink_led correctly sets the GPIO pin */
ZTEST_F(blink_led_tests, test_blink_led)
{
    blink_led(DOT_TIME_MS);

    zassert_true(mock_gpio_pin_set_dt_call_count > 0, "GPIO set was not called");
    zassert_true(mock_k_msleep_call_count > 0, "Sleep function was not called");
}

/* Test if blink_sos correctly executes the SOS pattern */
ZTEST_F(blink_led_tests, test_blink_sos)
{
    blink_sos();

    zassert_true(mock_gpio_pin_set_dt_call_count > 5, "GPIO set was not called enough times for SOS");
    zassert_true(mock_k_msleep_call_count > 0, "Sleep function was not called during SOS sequence");
}

static void blink_teardown(void *f)
{
    free(f);
}

ZTEST_SUITE(blink_led_tests, NULL, blink_setup, blink_before, NULL, blink_teardown);
