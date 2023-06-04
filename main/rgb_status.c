/*
  Implementa lógica de display de diversos statuses a traves de colores del RGB LED

  El RGB LED mostará en secuencia los colores habilitados separados por un OFF

  Cada status corresponderá a un color definido.
*/

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "sdkconfig.h"
#include "rgb_led.h"
#include "rgb_status.h"


static int            ncolors;
static word           states;  
static byte           *colors;
static RgbLed         rgbled;

void rgb_status_task(void *p)
{
  static int curr_color = 0;

  for(;;) {
    word isOn = (1 << curr_color);
    if(states & isOn) {
      ESP_ERROR_CHECK(rgb_led_set_pixel(rgbled, 0, 
        colors[curr_color] & RGB_RED ? CONFIG_RGB_BRIGHNESS : 0,
        colors[curr_color] & RGB_GREEN ? CONFIG_RGB_BRIGHNESS : 0,
        colors[curr_color] & RGB_BLUE ? CONFIG_RGB_BRIGHNESS : 0
      ));
    }
    else
      ESP_ERROR_CHECK(rgb_led_clear(rgbled));

    if(++curr_color >= ncolors)
      curr_color = 0;

    vTaskDelay(pdMS_TO_TICKS(CONFIG_RGB_BLINK_PERIOD));
  }
}

int rgb_status_init(int num_colors, byte *color_defs)
{
  ncolors = num_colors;
  colors = color_defs;
  states = 0;

  ESP_ERROR_CHECK(rgb_led_setup(&rgbled));

  xTaskCreate( (void (*)(void*))  rgb_status_task, "rgb_status_task", 4 * 1024, NULL, tskIDLE_PRIORITY, NULL );

  return 0;
}

int rgb_status_set(int n_status, byte enable)
{
  ESP_LOGI("rgb_status_set", "n_status: %d, enable: %d", n_status, enable);
  if(n_status >= ncolors)
    return -1;

  if(enable)
    states |= (1 << n_status);
  else
    states &= ~(1 << n_status);

  return 0;
}


