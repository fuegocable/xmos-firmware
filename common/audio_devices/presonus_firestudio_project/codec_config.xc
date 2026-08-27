#include "fc_spi.h"
#include "system.h"
#include "codec_config.h"

void fc_presonus_fsp_adc_dac_config_spi_bus()
{
    // From ADC/DAC datasheet: SPI Mode is selected if there is ever a high-to-low transition on the
    // AD0/CS pin after the RST pin has been restored high.

    // In case that ADC/DAC are not in reset state
    fc_presonus_fsp_adc_dac_reset_hold();
    delay_milliseconds(100);

    fc_spi_set_ss_port_bit(ADC_DAC_SPI_DEVICE, ADC_DAC_SPI_SS_BIT);

    // Make sure that SS is high before releasing reset (end_transaction deasserts SS)
    fc_spi_begin_transaction(ADC_DAC_SPI_DEVICE, ADC_DAC_SPI_SPEED_IN_KHZ, ADC_DAC_SPI_MODE);
    delay_milliseconds(100);
    fc_spi_end_transaction(ADC_DAC_SPI_SS_DELAY);
    delay_milliseconds(10);

    // Release reset
    fc_presonus_fsp_adc_dac_reset_release();
    delay_milliseconds(100);

    // Assert SS to put ADC/DAC in SPI mode
    fc_spi_begin_transaction(ADC_DAC_SPI_DEVICE, ADC_DAC_SPI_SPEED_IN_KHZ, ADC_DAC_SPI_MODE);
    delay_milliseconds(100);
    fc_spi_end_transaction(ADC_DAC_SPI_SS_DELAY);
}

void fc_presonus_fsp_adc_write_reg(uint8_t reg, uint8_t data)
{
    fc_spi_begin_transaction(ADC_DAC_SPI_DEVICE, ADC_DAC_SPI_SPEED_IN_KHZ, ADC_DAC_SPI_MODE);
    uint8_t cmd_header = ADC_SPI_ADDRESS << 1 | ADC_DAC_SPI_WRITE_INDICATOR;
    fc_spi_transfer8(cmd_header);
    fc_spi_transfer8(reg);
    fc_spi_transfer8(data);
    fc_spi_end_transaction(ADC_DAC_SPI_SS_DELAY);
}

void fc_presonus_fsp_dac_write_reg(uint8_t reg, uint8_t data)
{
    fc_spi_begin_transaction(ADC_DAC_SPI_DEVICE, ADC_DAC_SPI_SPEED_IN_KHZ, ADC_DAC_SPI_MODE);
    uint8_t cmd_header = DAC_SPI_ADDRESS << 1 | ADC_DAC_SPI_WRITE_INDICATOR;
    fc_spi_transfer8(cmd_header);
    fc_spi_transfer8(reg);
    fc_spi_transfer8(data);
    fc_spi_end_transaction(ADC_DAC_SPI_SS_DELAY);
}
