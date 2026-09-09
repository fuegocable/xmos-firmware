#include <stdint.h>
#include "board/board_gpio.h"
#include "fc_spi.h"

#define P_METERS_OUTPUT_ENABLE_N_GPIO P_FC_GPIO_0
#define P_ADC_DAC_RESET_GPIO P_FC_GPIO_1

#define METERS_SPI_DEVICE 1
#define METERS_SPI_SS_BIT 1
#define METERS_SPI_SS_DELAY     1000
#define METERS_SPI_SPEED_IN_KHZ 1000
#define METERS_SPI_MODE FC_SPI_MODE_0

void fc_presonus_fsp_adc_dac_reset_hold();
void fc_presonus_fsp_adc_dac_reset_release();
void fc_presonus_fsp_meters_output_enable();
void fc_presonus_fsp_meters_output_disable();
uint8_t fc_presonus_fsp_sample_to_led_value(int32_t sample);
void fc_presonus_fsp_meters_update(char channel_leds[8]);

