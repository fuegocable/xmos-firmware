#pragma once

#include "i2c.h"
#include <xccompat.h>
#include "audio_device.h"

/**
 * @brief Configuration struct type for setting the hardware profile.
 */
typedef struct {
    /** I2S word length in bits. */
    unsigned i2s_n_bits;
} dxio_mc_3w_config_t;

/**
 * @brief Starts an I2C master task. Must be started from tile[0] *after* dxio_mc_3w_board_setup()
 * and *before* and tile[1] HW calls.
 *
 *  \param   i2c        client side of I2C master interface connection.
 */
void dxio_mc_3w_i2c_master(SERVER_INTERFACE(i2c_master_if, i2c[1]));

/**
 * @brief Initialises the audio hardware ready for a configuration. Must be called once *after*
 * dxio_mc_3w_board_setup().
 *
 *  \param   config     Reference to the fc_audio_device_config_t hardware configuration struct.
 */
void dxio_mc_3w_AudioHwInit(CLIENT_INTERFACE(i2c_master_if, i2c),
                            const REFERENCE_PARAM(fc_audio_device_config_t, config));

/**
 * @brief Configures the audio hardware following initialisation. This is typically called each time
 * a sample rate or stream format change occurs.
 *
 *  \param   config         Reference to the fc_audio_device_config_t hardware configuration struct.
 *  \param   samFreq        The sample rate in Hertz.
 *  \param   mClk           The master clock rate in Hertz.
 *  \param   dsdMode        Controls whether the DAC is to be set into DSD mode (1) or PCM mode (0).
 *  \param   sampRes_DAC    The sample resolution of the DAC output in bits. Typically 16, 24 or 32.
 *  \param   sampRes_ADC    The sample resolution of the ADC input in bits. Typically 16, 24 or 32.
 */
void dxio_mc_3w_AudioHwConfig(CLIENT_INTERFACE(i2c_master_if, i2c),
                              const REFERENCE_PARAM(fc_audio_device_config_t, config), unsigned samFreq,
                              unsigned mClk, unsigned dsdMode, unsigned sampRes_DAC,
                              unsigned sampRes_ADC);
