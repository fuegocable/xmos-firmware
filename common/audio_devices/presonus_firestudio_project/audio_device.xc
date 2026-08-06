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
    fc_presonus_fsp_adc_write_reg(spi, CS5368_GCTL_MDE, 0b10000000);
    fc_presonus_fsp_dac_write_reg(spi, CS4385_MODE_CTRL, 0b10000000);
}

void fc_audio_device_hw_config_prepare(CLIENT_INTERFACE(i2c_master_if, i2c),
                                       CLIENT_INTERFACE(spi_master_if, spi),
                                       const fc_audio_device_config_t &config, unsigned samFreq,
                                       unsigned mClk, unsigned dsdMode, unsigned sampRes_DAC,
                                       unsigned sampRes_ADC)
{
    // TODO: Mute
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

    /* MCLK Divider */
    // TODO: Calculate mdiv based on mClk and samFreq because each board can use different mClk
    unsigned char mdiv = 0b001; // Divide MCLK by 2

    /* Data format */
    unsigned char dataFormat = 0b10; // TDM format

    /* Speed mode */
    unsigned char speedMode = 0;
    if(samFreq < 54000)
        speedMode = 0b00;
    else
        speedMode = 0b01;

    fc_presonus_fsp_adc_write_reg(spi, CS5368_GCTL_MDE, 0b10000000 | (mdiv << 4) | (dataFormat << 2) | speedMode);

    /* Reg 0x06: (PDN) Power Down Register */
    fc_presonus_fsp_adc_write_reg(spi, CS5368_PWR_DN, 0b00000000);

    /* PCM Control (Address: 0x03) */
    /* bit[7:4] : Digital Interface Format (DIF) : 0b0001 for I2S up to 24bit
        * bit[3:2] : Reserved
        * bit[1:0] : Functional Mode (FM) : 0b00 - single-speed mode (4-50kHz)
        *                                 : 0b01 - double-speed mode (50-100kHz)
        *                                 : 0b10 - quad-speed mode (100-200kHz)
        *                                 : 0b11 - auto-speed detect (32 to 200kHz)
        *                                 (note, some Mclk/SR ratios not supported in auto)
        *
        */
    // unsigned char regVal = 0;
    // if(samFreq < 50000)
    //     regVal = 0b11000100;
    // else if(samFreq < 100000)
    //     regVal = 0b11000101;
    // else
    //     regVal = 0b11000110;
    // fc_presonus_fsp_dac_write_reg(spi, CS4385_PCM_CTRL, regVal);




    // bit[7:4] 0b1100 for TDM
    // bit[3:0] 0b0011 Auto-speed
    // fc_presonus_fsp_dac_write_reg(spi, CS4385_PCM_CTRL, (0b1100 << 4) | 0b0011);

    /* Mode Control 1 (Address: 0x02) */
    /* bit[7] : Control Port Enable (CPEN)     : Set to 1 for enable
        * bit[6] : Freeze controls (FREEZE)       : Set to 0 for freeze
        * bit[5] : PCM/DSD Selection (DSD/PCM)    : Set to 0 for PCM
        * bit[4:1] : DAC Pair Disable (DACx_DIS)  : All Dac Pairs enabled
        * bit[0] : Power Down (PDN)               : Not powered down
        */
    // fc_presonus_fsp_dac_write_reg(spi, CS4385_MODE_CTRL, 0b10000000);



    // bit[7:4] 0b1100 for TDM
    // bit[3:0] 0b0011 Auto-speed
    fc_presonus_fsp_dac_write_reg(spi, CS4385_PCM_CTRL, (0b1100 << 4) | 0b0011);

    fc_presonus_fsp_dac_write_reg(spi, CS4385_MODE_CTRL, 0b10000000);

}
