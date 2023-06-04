#include "led_strip.h"

#define BLINK_GPIO CONFIG_RGB_BLINK_GPIO
#define RGB_COLOR_BRIGHTNESS   CONFIG_RGB_BRIGHNESS

// // LED numbers in the strip
#define LED_STRIP_LED_NUMBERS 1

// // 10MHz resolution, 1 tick = 0.1us (led strip needs a high resolution)
#define LED_STRIP_RMT_RES_HZ   (10 * 1000 * 1000)

typedef led_strip_handle_t RgbLed;

int rgb_led_set_pixel(RgbLed rgbled, int r, int red, int green, int blue);

int rgb_led_set_red(RgbLed rgbled);

int rgb_led_set_green(RgbLed rgbled);

int rgb_led_set_blue(RgbLed rgbled);

int rgb_led_refresh(RgbLed rgbled);

int rgb_led_clear(RgbLed rgbled);

int rgb_led_setup(RgbLed *prgbled);

