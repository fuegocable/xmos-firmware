#include <assert.h>
#include <xs1.h>

#include "board/board.h"
#include "board/board_gpio.h"
#include "xassert.h"
#include <platform.h>

#include "i2c.h"
#include "spi.h"

#include <print.h>
#include <stdio.h>

#include "audio_device.h"

out port P_FC_GPIO_PORT_INSTANCE = P_FC_GPIO_PORT;

port p_i2c = PORT_I2C;

out buffered port:32 p_sclk = PORT_SPI_SCLK;
out buffered port:32 p_mosi = PORT_SPI_MOSI;
out port p_ss                 = PORT_SPI_SS;

void dxio_mc_3w_i2c_master(SERVER_INTERFACE(i2c_master_if, i2c[1]))
{
    i2c_master_single_port(i2c, 1, p_i2c, 10, 0, 1, 0);
}

void dxio_mc_3w_spi_master(SERVER_INTERFACE(spi_master_if, spi[1]))
{
    spi_master(spi, 1, p_sclk, p_mosi, null, p_ss, 1, null);
}

void dxio_mc_3w_AudioHwInit(CLIENT_INTERFACE(i2c_master_if, i2c),
                            const fc_audio_device_config_t &config)
{
    fc_audio_device_hw_init(i2c, config);
}

void dxio_mc_3w_AudioHwConfig(CLIENT_INTERFACE(i2c_master_if, i2c),
                              const fc_audio_device_config_t &config, unsigned samFreq,
                              unsigned mClk, unsigned dsdMode, unsigned sampRes_DAC,
                              unsigned sampRes_ADC)
{
    fc_audio_device_hw_config_begin(i2c, config, samFreq, mClk, dsdMode, sampRes_DAC,
                                      sampRes_ADC);

    enable_mclk(mClk);

    fc_audio_device_hw_config(i2c, config, samFreq, mClk, dsdMode, sampRes_DAC, sampRes_ADC);

    fc_audio_device_hw_config_end(i2c, config, samFreq, mClk, dsdMode, sampRes_DAC,
                                      sampRes_ADC);
}
