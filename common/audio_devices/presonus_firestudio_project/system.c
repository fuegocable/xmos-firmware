#include "system.h"
#include "gpio_access.h"

extern port_t P_FC_GPIO_PORT_INSTANCE;

void fc_presonus_fsp_adc_dac_reset_hold()
{
    set_gpio(P_ADC_DAC_RESET_GPIO, 1);
}

void fc_presonus_fsp_adc_dac_reset_release()
{
    set_gpio(P_ADC_DAC_RESET_GPIO, 0);
}
