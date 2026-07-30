#include <assert.h>
#include <xs1.h>

#include "xassert.h"
#include "board/board.h"
#include "board/board_gpio.h"
#include <platform.h>

#include "i2c.h"

#include <print.h>
#include <stdio.h>

#include "audio_device.h"

out port P_FC_GPIO_PORT_INSTANCE = P_FC_GPIO_PORT;

port p_i2c        = PORT_I2C;

void dxio_mc_3w_i2c_master(SERVER_INTERFACE(i2c_master_if, i2c[1]))
{
    i2c_master_single_port(i2c, 1, p_i2c, 10, 0, 1, 0);
}

void dxio_mc_3w_AudioHwInit(CLIENT_INTERFACE(i2c_master_if, i2c), const fc_audio_device_config_t &config)
{
    fc_audio_device_hw_init(i2c, config);
}

void dxio_mc_3w_AudioHwConfig(CLIENT_INTERFACE(i2c_master_if, i2c),
                              const fc_audio_device_config_t &config, unsigned samFreq, unsigned mClk,
                              unsigned dsdMode, unsigned sampRes_DAC, unsigned sampRes_ADC)
{
    fc_audio_device_hw_config_prepare(i2c, config, samFreq, mClk, dsdMode, sampRes_DAC, sampRes_ADC);

    enable_mclk(mClk);

    fc_audio_device_hw_config(i2c, config, samFreq, mClk, dsdMode, sampRes_DAC, sampRes_ADC);
}
