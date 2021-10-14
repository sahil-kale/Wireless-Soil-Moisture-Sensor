#include "adc.h"
#include <driver/adc.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdint.h>
#include "config.h"
#include "esp_timer.h"

static void init_adc();
static int get_adc_reading();

enum adc_error_codes{TIMEOUT_DUE_TO_WIFI = -1, UNKNOWN_ERROR = -2};

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
static int get_adc_reading()
{
    int read_raw = 0; //This is an int because the function uses int and not int16_t :(
    esp_err_t r = adc2_get_raw( ADC_CHANNEL, ADC_WIDTH_12Bit, &read_raw);
    if ( r == ESP_OK ) {
        return read_raw;
    } else if ( r == ESP_ERR_TIMEOUT ) {
        return TIMEOUT_DUE_TO_WIFI;
    }
    
    return UNKNOWN_ERROR; //Undefined error
}

void task_adc()
{
    init_adc();
    while(true)
    {
        int reading = get_adc_reading();
        printf("Time: %lld, Reading -> %d\n", (long long)esp_timer_get_time(), reading );
        vTaskDelay(10);
    }
    
}