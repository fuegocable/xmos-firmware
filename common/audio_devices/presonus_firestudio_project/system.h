#include <stdint.h>
#include "board/board_gpio.h"

#define P_ADC_DAC_RESET_GPIO P_FC_GPIO_1

void fc_presonus_fsp_adc_dac_reset_hold();
void fc_presonus_fsp_adc_dac_reset_release();
