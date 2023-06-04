#include "esp_log.h"
#include "rgb_led.h"

#define BLINK_GPIO CONFIG_RGB_BLINK_GPIO
#define RGB_COLOR_BRIGHTNESS   CONFIG_RGB_BRIGHNESS

// // LED numbers in the strip
#define LED_STRIP_LED_NUMBERS 1

// // 10MHz resolution, 1 tick = 0.1us (led strip needs a high resolution)
#define LED_STRIP_RMT_RES_HZ   (10 * 1000 * 1000)

typedef led_strip_handle_t RgbLed;

int rgb_led_set_pixel(RgbLed rgbled, int parm, int red, int green, int blue) {
  int r = led_strip_set_pixel(rgbled, parm, red, green, blue);
  led_strip_refresh(rgbled);
  return r;
}

int rgb_led_set_red(RgbLed rgbled) {
  int r = led_strip_set_pixel(rgbled, 0, RGB_COLOR_BRIGHTNESS, 0, 0);
  led_strip_refresh(rgbled);
  return r;
}

int rgb_led_set_green(RgbLed rgbled) {
  int r = led_strip_set_pixel(rgbled, 0, 0, RGB_COLOR_BRIGHTNESS, 0);
  led_strip_refresh(rgbled);
  return r;
}

int rgb_led_set_blue(RgbLed rgbled) {
  int r = led_strip_set_pixel(rgbled, 0, 0, 0, RGB_COLOR_BRIGHTNESS);
  led_strip_refresh(rgbled);
  return r;
}

int rgb_led_refresh(RgbLed rgbled) 
{
  return led_strip_refresh(rgbled);
}

int  rgb_led_clear(RgbLed rgbled)
{
  return led_strip_clear(rgbled);
}

int rgb_led_setup(RgbLed *prgbled)
{
  led_strip_config_t strip_config = {
    .strip_gpio_num = BLINK_GPIO,
    .max_leds = LED_STRIP_LED_NUMBERS, // at least one LED on board
  };

  led_strip_rmt_config_t rmt_config = {
    .resolution_hz = LED_STRIP_RMT_RES_HZ, // 10MHz
  };

  int r = led_strip_new_rmt_device(&strip_config, &rmt_config, prgbled);
  /* Set all LED off to clear all pixels */
  led_strip_clear(*prgbled);

  return r;
}

