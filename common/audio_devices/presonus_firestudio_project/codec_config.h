#include <stdint.h>
#include "fc_spi.h"
#include "drivers/cs5368.h"
#include "drivers/cs4385.h"

#define ADC_DAC_SPI_DEVICE 0
#define ADC_DAC_SPI_SS_BIT 0

#define ADC_DAC_SPI_SS_DELAY     1000 // 10 microseconds (1us betwwen transactions required by ADC/DAC)
#define ADC_DAC_SPI_SPEED_IN_KHZ 1000

#define ADC_DAC_SPI_WRITE_INDICATOR 0
#define ADC_DAC_SPI_READ_INDICATOR  1

#define ADC_SPI_ADDRESS CS5368_SPI_ADDR
#define DAC_SPI_ADDRESS CS4385_SPI_ADDR

#define ADC_DAC_SPI_MODE FC_SPI_MODE_0

void fc_presonus_fsp_adc_dac_config_spi_bus();
void fc_presonus_fsp_adc_write_reg(uint8_t register, uint8_t data);
void fc_presonus_fsp_dac_write_reg(uint8_t register, uint8_t data);
