#include "audio_device.h"
#include "drivers/cs4384.h"
#include "drivers/cs5368.h"
#include "i2c-utils.h"
#include "i2c.h"
#include "xassert.h"
#include <assert.h>
#include <xs1.h>
#include "system.h"

#define DAC_REGWRITE(reg, val)                                                                     \
    {                                                                                              \
        result = i2c.write_reg(CS4384_I2C_ADDR, reg, val);                                         \
    }
#define ADC_REGWRITE(reg, val)                                                                     \
    {                                                                                              \
        result = i2c.write_reg(CS5368_I2C_ADDR, reg, val);                                         \
    }

// TODO: add main function
// // GPIOs must be low from the startup
// on tile[P_FC_GPIO_TILE_NUM]:
// {
//     fc_presonus_fsp_adc_dac_reset_hold();
// }

void fc_audio_device_hw_init(CLIENT_INTERFACE(i2c_master_if, i2c),
                             const fc_audio_device_config_t &config)
{
    fc_presonus_fsp_adc_dac_reset_hold(); // In case that ADC/DAC are not in reset state

    // TODO: Put /CS High
    // TODO: Wait a little
    fc_presonus_fsp_adc_dac_reset_release();
    // TODO: Wait another little
    // TODO: Put /CS low
    // TODO: Wait another little

    // From ADC/DAC datasheet: SPI Mode is selected if there is ever a high-to-low transition on the
    // AD0/CS pin after the RST pin has been restored high.

    // We enabled SPI
    // TODO: Made initial config
}

void fc_audio_device_hw_config_prepare(CLIENT_INTERFACE(i2c_master_if, i2c),
                                       const fc_audio_device_config_t &config, unsigned samFreq,
                                       unsigned mClk, unsigned dsdMode, unsigned sampRes_DAC,
                                       unsigned sampRes_ADC)
{
    // TODO: Mute
}

void fc_audio_device_hw_config(CLIENT_INTERFACE(i2c_master_if, i2c),
                               const fc_audio_device_config_t &config, unsigned samFreq,
                               unsigned mClk, unsigned dsdMode, unsigned sampRes_DAC,
                               unsigned sampRes_ADC)
{
    // TODO: Do whatever is needed to configure the device for the given sample rate, MCLK, DSD
    // mode, and sample resolutions

    // TODO: Unmute
}
