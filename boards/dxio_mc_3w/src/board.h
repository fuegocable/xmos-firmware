#pragma once

#include "i2c.h"
#include "spi.h"
#include <xccompat.h>
#include "audio_device.h"

void dxio_mc_3w_i2c_master(SERVER_INTERFACE(i2c_master_if, i2c[1]));

void dxio_mc_3w_spi_master(SERVER_INTERFACE(spi_master_if, spi[1]));

void dxio_mc_3w_AudioHwInit(CLIENT_INTERFACE(i2c_master_if, i2c),
                            const REFERENCE_PARAM(fc_audio_device_config_t, config));

void dxio_mc_3w_AudioHwConfig(CLIENT_INTERFACE(i2c_master_if, i2c),
                              const REFERENCE_PARAM(fc_audio_device_config_t, config), unsigned samFreq,
                              unsigned mClk, unsigned dsdMode, unsigned sampRes_DAC,
                              unsigned sampRes_ADC);
