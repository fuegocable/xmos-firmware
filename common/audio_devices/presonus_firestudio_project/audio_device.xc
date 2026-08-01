#include "audio_device.h"
#include "drivers/cs4385.h"
#include "drivers/cs5368.h"
#include "i2c-utils.h"
#include "i2c.h"
#include "xassert.h"
#include <assert.h>
#include <xs1.h>
#include "system.h"
#include "codec_config.h"

// TODO: add main function
// // GPIOs must be low from the startup
// on tile[P_FC_GPIO_TILE_NUM]:
// {
//     fc_presonus_fsp_adc_dac_reset_hold();
// }

void fc_audio_device_hw_init(CLIENT_INTERFACE(i2c_master_if, i2c),
                             CLIENT_INTERFACE(spi_master_if, spi),
                             const fc_audio_device_config_t &config)
{
    fc_presonus_fsp_adc_dac_config_spi_bus(spi);

    // We enabled SPI
    // TODO: Made initial config

}

void fc_audio_device_hw_config_prepare(CLIENT_INTERFACE(i2c_master_if, i2c),
                                       CLIENT_INTERFACE(spi_master_if, spi),
                                       const fc_audio_device_config_t &config, unsigned samFreq,
                                       unsigned mClk, unsigned dsdMode, unsigned sampRes_DAC,
                                       unsigned sampRes_ADC)
{
    /* Mode Control 1 (Address: 0x02) */
    /* bit[7] : Control Port Enable (CPEN)     : Set to 1 for enable
        * bit[6] : Freeze controls (FREEZE)       : Set to 1 for freeze
        * bit[5] : PCM/DSD Selection (DSD/PCM)    : Set to 0 for PCM
        * bit[4:1] : DAC Pair Disable (DACx_DIS)  : All Dac Pairs enabled
        * bit[0] : Power Down (PDN)               : Powered down
        */
    fc_presonus_fsp_dac_write_reg(spi, CS4385_MODE_CTRL, 0b11000001);
}

void fc_audio_device_hw_config(CLIENT_INTERFACE(i2c_master_if, i2c),
                               CLIENT_INTERFACE(spi_master_if, spi),
                               const fc_audio_device_config_t &config, unsigned samFreq,
                               unsigned mClk, unsigned dsdMode, unsigned sampRes_DAC,
                               unsigned sampRes_ADC)
{
    /* Reg 0x01: (GCTL) Global Mode Control Register */
    /* Bit[7]: CP-EN: Manages control-port mode
    * Bit[6]: CLKMODE: Setting puts part in 384x mode
    * Bit[5:4]: MDIV[1:0]: Set to 01 for /2
    * Bit[3:2]: DIF[1:0]: Data Format: 0x01 for I2S, 0x02 for TDM
    * Bit[1:0]: MODE[1:0]: Mode: 0x03 Slave mode all speeds
    */
    fc_presonus_fsp_adc_write_reg(spi, CS5368_GCTL_MDE, 0b10010000 | (0x01 << 2) | 0x03);

    /* Reg 0x06: (PDN) Power Down Register */
    /* Bit[7:6]: Reserved
        * Bit[5]: PDN-BG: When set, this bit powers-own the bandgap reference
        * Bit[4]: PDM-OSC: Controls power to internal oscillator core
        * Bit[3:0]: PDN: When any bit is set all clocks going to that channel pair are turned off
        */
    fc_presonus_fsp_adc_write_reg(spi, CS5368_PWR_DN, 0b00000000);

    /* PCM Control (Address: 0x03) */
    /* bit[7:4] : Digital Interface Format (DIF) : 0b0001 for I2S up to 24bit
        * bit[3:2] : Reserved
        * bit[1:0] : Functional Mode (FM) : 0x00 - single-speed mode (4-50kHz)
        *                                 : 0x01 - double-speed mode (50-100kHz)
        *                                 : 0x10 - quad-speed mode (100-200kHz)
        *                                 : 0x11 - auto-speed detect (32 to 200kHz)
        *                                 (note, some Mclk/SR ratios not supported in auto)
        *
        */
    unsigned char regVal = 0;
    if(samFreq < 50000)
        regVal = 0b11000100;
    else if(samFreq < 100000)
        regVal = 0b11000101;
    else
        regVal = 0b11000110;

    fc_presonus_fsp_dac_write_reg(spi, CS4385_PCM_CTRL, regVal);

    /* Mode Control 1 (Address: 0x02) */
    /* bit[7] : Control Port Enable (CPEN)     : Set to 1 for enable
        * bit[6] : Freeze controls (FREEZE)       : Set to 0 for freeze
        * bit[5] : PCM/DSD Selection (DSD/PCM)    : Set to 0 for PCM
        * bit[4:1] : DAC Pair Disable (DACx_DIS)  : All Dac Pairs enabled
        * bit[0] : Power Down (PDN)               : Not powered down
        */
    fc_presonus_fsp_dac_write_reg(spi, CS4385_MODE_CTRL, 0b10000000);
}
