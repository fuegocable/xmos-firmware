#pragma once

#include "i2c.h"
#include "xassert.h"
#include <assert.h>
#include <xccompat.h>
#include <xs1.h>

typedef struct {
    /** I2S word length in bits. */
    unsigned i2s_n_bits;
} fc_audio_device_config_t;

void fc_audio_device_main();

void fc_audio_device_hw_init(CLIENT_INTERFACE(i2c_master_if, i2c),
                             const REFERENCE_PARAM(fc_audio_device_config_t, config));

void fc_audio_device_hw_config_begin(CLIENT_INTERFACE(i2c_master_if, i2c),
                                       const REFERENCE_PARAM(fc_audio_device_config_t, config), unsigned samFreq,
                                       unsigned mClk, unsigned dsdMode, unsigned sampRes_DAC,
                                       unsigned sampRes_ADC);

void fc_audio_device_hw_config(CLIENT_INTERFACE(i2c_master_if, i2c),
                               const REFERENCE_PARAM(fc_audio_device_config_t, config), unsigned samFreq,
                               unsigned mClk, unsigned dsdMode, unsigned sampRes_DAC,
                               unsigned sampRes_ADC);

void fc_audio_device_hw_config_end(CLIENT_INTERFACE(i2c_master_if, i2c),
                                       const REFERENCE_PARAM(fc_audio_device_config_t, config), unsigned samFreq,
                                       unsigned mClk, unsigned dsdMode, unsigned sampRes_DAC,
                                       unsigned sampRes_ADC);

/* Forward declaration for XUA function (from lib_xua) - only for C files, not XC */
#ifndef __XC__
void XUA_Endpoint0_setSerialStr(char * serial_str);
#endif
