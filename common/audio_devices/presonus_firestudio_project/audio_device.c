#include "audio_device.h"
#include "codec_config.h"
#include "drivers/cs4385.h"
#include "drivers/cs5368.h"
#include "i2c-utils.h"
#include "i2c.h"
#include "system.h"
#include "xassert.h"
#include <assert.h>
#include <xs1.h>
#include "xua_endpoint0.h"
#include "audio_device_ui.h"

extern int32_t inputVumeter[];
char channel_leds[8] = {0};
int is_ui_initialized = 0;

void fc_audio_device_main()
{
    XUA_Endpoint0_setSerialStr(PRESONUS_DEFAULT_SERIAL_STRING);
}

void fc_audio_device_ui_refresh()
{
    if (!is_ui_initialized) {
        return;
    }

    for (unsigned ch = 0; ch < I2S_CHANS_ADC; ch++) {
        int32_t peak = inputVumeter[ch];
        inputVumeter[ch] = 0;

        uint8_t led_value = fc_presonus_fsp_sample_to_led_value(peak);
        
        channel_leds[ch] = led_value;
    }
    
    fc_presonus_fsp_meters_update(channel_leds);
}

void fc_audio_device_hw_init(CLIENT_INTERFACE(i2c_master_if, i2c),
                             const REFERENCE_PARAM(fc_audio_device_config_t, config))
{
    fc_presonus_fsp_adc_dac_config_spi_bus();
    fc_presonus_fsp_adc_write_reg(CS5368_GCTL_MDE, 0b10000000);
    fc_presonus_fsp_dac_write_reg(CS4385_MODE_CTRL, 0b10000000);

    /** Leds **/
    fc_presonus_fsp_meters_output_enable();
    delay_milliseconds(10);
    fc_spi_set_ss_port_bit(METERS_SPI_DEVICE, METERS_SPI_SS_BIT);
    // TODO: Make init animation on leds (non-blocking)
    fc_presonus_fsp_meters_update((char[8]){0, 0, 0, 0, 0, 0, 0, 0});
    is_ui_initialized = 1;
}

void fc_audio_device_hw_config_begin(CLIENT_INTERFACE(i2c_master_if, i2c),
                                     const REFERENCE_PARAM(fc_audio_device_config_t, config), unsigned samFreq,
                                     unsigned mClk, unsigned dsdMode, unsigned sampRes_DAC,
                                     unsigned sampRes_ADC)
{
    // TODO: Mute
}

void fc_audio_device_hw_config(CLIENT_INTERFACE(i2c_master_if, i2c),
                               const REFERENCE_PARAM(fc_audio_device_config_t, config), unsigned samFreq,
                               unsigned mClk, unsigned dsdMode, unsigned sampRes_DAC,
                               unsigned sampRes_ADC)
{
    /**
     * ADC Config
     */

    /* Reg 0x01: (GCTL) Global Mode Control Register
     * Bit[7]:   CP-EN: Manages control-port mode
     * Bit[6]:   CLKMODE: Setting puts part in 384x mode
     * Bit[5:4]: MDIV[1:0]: Set to 01 for /2
     * Bit[3:2]: DIF[1:0]: Data Format: 0x01 for I2S, 0x02 for TDM
     * Bit[1:0]: MODE[1:0]: Mode: 0x03 Slave mode all speeds
     */

    // TODO: Calculate mdiv based on mClk and samFreq because each board can use different mClk
    unsigned char mlk_div     = 0b001; // Divide MCLK by 2
    unsigned char data_format = 0b10;  // TDM format

    unsigned char speed_mode = 0;
    if (samFreq < 54000) {
        speed_mode = 0b00;
    } else {
        speed_mode = 0b01;
    }
    fc_presonus_fsp_adc_write_reg(CS5368_GCTL_MDE,
                                  0b10000000 | (mlk_div << 4) | (data_format << 2) | speed_mode);

    /**
     * DAC Config
     */

    /* Reg 0x03: PCM Control */
    /* Bit[7:4] : Digital Interface Format (DIF) : 0b1100 for TDM
     * Bit[3:2] : Reserved
     * Bit[1:0] : Functional Mode (FM)
     */
    unsigned char format          = 0b1100; // TDM
    unsigned char functional_mode = 0b11;   // Auto-speed detect

    fc_presonus_fsp_dac_write_reg(CS4385_PCM_CTRL,
                                  (format << 4) | (0b00 << 2) | functional_mode);
}

void fc_audio_device_hw_config_end(CLIENT_INTERFACE(i2c_master_if, i2c),
                                   const REFERENCE_PARAM(fc_audio_device_config_t, config), unsigned samFreq,
                                   unsigned mClk, unsigned dsdMode, unsigned sampRes_DAC,
                                   unsigned sampRes_ADC)
{
    // Unmute

    /* Reg 0x06: Power Down */
    fc_presonus_fsp_adc_write_reg(CS5368_PWR_DN, 0b00000000);

    /* Reg 0x02: Mode Control */
    fc_presonus_fsp_dac_write_reg(CS4385_MODE_CTRL, 0b10000000);
}
