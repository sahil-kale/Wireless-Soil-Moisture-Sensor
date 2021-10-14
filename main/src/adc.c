#include "adc.h"
#include <driver/adc.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdint.h>
#include "config.h"

static void init_adc();
static void get_adc_reading();

/**
 * @brief initalizes the ADC
 */
static void init_adc()
{
    adc2_config_channel_atten(ADC_CHANNEL, ADC_ATTEN_0db );
}

/**
 * @brief grabs the ADC reading
 */
static void get_adc_reading()
{
    int read_raw = 0; //This is an int because the function uses int and not int16_t :(
    esp_err_t r = adc2_get_raw( ADC_CHANNEL, ADC_WIDTH_12Bit, &read_raw);
    if ( r == ESP_OK ) {
        printf("%d\n", read_raw );
    } else if ( r == ESP_ERR_TIMEOUT ) {
        printf("ADC2 used by Wi-Fi.\n");
    }
}

void task_adc()
{
    init_adc();
    while(true)
    {
        get_adc_reading();
        vTaskDelay(10);
    }
    
}