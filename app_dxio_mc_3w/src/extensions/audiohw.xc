#include "xua.h"

#include <board/board.h>

static const fc_audio_device_config_t config = {
    // i2s_n_bits
    XUA_I2S_N_BITS,
};

unsafe client interface i2c_master_if i_i2c_client;
unsafe client interface spi_master_if i_spi_client;

void AudioHwInit()
{
    unsafe
    {
        /* Wait until global is set */
        while (!(unsigned)i_i2c_client)
            ;
        while (!(unsigned)i_spi_client)
            ;
        dxio_mc_3w_AudioHwInit((client interface i2c_master_if)i_i2c_client,
                               (client interface spi_master_if)i_spi_client, config);
    }
}

void AudioHwConfig(unsigned samFreq, unsigned mClk, unsigned dsdMode, unsigned sampRes_DAC,
                   unsigned sampRes_ADC)
{
    unsafe
    {
        dxio_mc_3w_AudioHwConfig((client interface i2c_master_if)i_i2c_client,
                                 (client interface spi_master_if)i_spi_client, config, samFreq,
                                 mClk, dsdMode, sampRes_DAC, sampRes_ADC);
    }
}
