#include <stdio.h>
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "config.h"
#include "wifi_cmds.h"
#include "adc.h"

void task_heartbeat()
{
    static uint16_t heartbeat_period_ms = 300;
    gpio_reset_pin(BLINK_GPIO);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
    while(1) {
        /* Blink off (output low) */
        gpio_set_level(BLINK_GPIO, 0);
        vTaskDelay(heartbeat_period_ms / portTICK_PERIOD_MS);
        /* Blink on (output high) */
        gpio_set_level(BLINK_GPIO, 1);
        vTaskDelay(heartbeat_period_ms / portTICK_PERIOD_MS);
    }
}


void app_main(void)
{
    //while(wifi_init_sta());
    xTaskCreate(task_heartbeat, "Blink", 4096, NULL, 0, NULL); //4096 Bytes in case we want to use printf or something
    xTaskCreate(task_adc, "ADC Task", 4096, NULL, 1, NULL);
}
