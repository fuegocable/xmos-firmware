#include "audio_device.h"
#include "i2c-utils.h"
#include "i2c.h"
#include <xs1.h>
#include "xassert.h"
#include <assert.h>
#include <drivers/pcm5122.h>

static i2c_regop_res_t write_pcm5122_reg(CLIENT_INTERFACE(i2c_master_if, i2c), int regAddr,
                                         int regData)
{
    i2c_regop_res_t result;
    unsafe { result = i2c_reg_write(i2c, PCM5122_I2C_DEVICE_ADDR, regAddr, regData); }
    assert(result == I2C_REGOP_SUCCESS && msg("I2C write reg failed"));
    return result;
}

void fc_audio_device_hw_init(CLIENT_INTERFACE(i2c_master_if, i2c),
                             CLIENT_INTERFACE(spi_master_if, spi),
                             const fc_audio_device_config_t &config)
{
    delay_milliseconds(100);
    write_pcm5122_reg(i2c, PCM5122_REG_PAGE_SELECT, 0x00);
    write_pcm5122_reg(i2c, PCM5122_REG_STANDBY, 0x01);
    write_pcm5122_reg(i2c, PCM5122_REG_STANDBY, 0x10);
    write_pcm5122_reg(i2c, PCM5122_REG_RESET, 0x11);
    write_pcm5122_reg(i2c, PCM5122_REG_ERROR_DETECT, 0x08);
    write_pcm5122_reg(i2c, PCM5122_REG_PLL_REF, 0x10);

    int alen = 0b11;
    switch (config.i2s_n_bits) {
        case 16:
            alen = 0b00;
            break;
        case 24:
            alen = 0b10;
            break;
        case 32:
            alen = 0b11;
            break;
    }

    write_pcm5122_reg(i2c, PCM5122_REG_I2S_CONFIG, 0b00000000 | (alen));

    write_pcm5122_reg(i2c, PCM5122_REG_STANDBY, 0x00);
}

void fc_audio_device_hw_config_prepare(CLIENT_INTERFACE(i2c_master_if, i2c),
                                       CLIENT_INTERFACE(spi_master_if, spi),
                                       const fc_audio_device_config_t &config, unsigned samFreq,
                                       unsigned mClk, unsigned dsdMode, unsigned sampRes_DAC,
                                       unsigned sampRes_ADC)
{
    // Mute
}

void fc_audio_device_hw_config(CLIENT_INTERFACE(i2c_master_if, i2c),
                               CLIENT_INTERFACE(spi_master_if, spi),
                               const fc_audio_device_config_t &config, unsigned samFreq,
                               unsigned mClk, unsigned dsdMode, unsigned sampRes_DAC,
                               unsigned sampRes_ADC)
{
    // Config
    // Unmute
}
