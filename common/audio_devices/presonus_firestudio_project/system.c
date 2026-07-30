#include "gpio_access.h"
#include "system.h"

// ADC/DAC reset has negative logic
void fc_presonus_fsp_adc_dac_reset_hold()
{
    set_gpio(P_ADC_DAC_RESET_GPIO, 0);
}

void fc_presonus_fsp_adc_dac_reset_release()
{
    set_gpio(P_ADC_DAC_RESET_GPIO, 1);
}