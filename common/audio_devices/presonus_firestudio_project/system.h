#include "board/board_gpio.h"

#define P_ADC_DAC_RESET_GPIO P_FC_GPIO_1

extern port_t P_FC_GPIO_PORT_INSTANCE;

void fc_presonus_fsp_adc_dac_reset_hold();
void fc_presonus_fsp_adc_dac_reset_release();