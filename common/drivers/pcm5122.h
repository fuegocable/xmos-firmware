#pragma once

// PCM5122 (2-channel audio DAC) I2C Slave Addresses
#define PCM5122_I2C_DEVICE_ADDR (0x4C)

/*! @brief Page 0 Register Addresses */
#define PCM5122_REG_PAGE_SELECT        0x00 ///< Page select register
#define PCM5122_REG_RESET              0x01 ///< Reset register
#define PCM5122_REG_STANDBY            0x02 ///< Standby and powerdown requests
#define PCM5122_REG_MUTE               0x03 ///< Mute control
#define PCM5122_REG_PLL                0x04 ///< PLL enable and lock status
#define PCM5122_REG_SPI_MISO           0x06 ///< SPI MISO function select
#define PCM5122_REG_DEEMPHASIS         0x07 ///< De-emphasis and SDOUT select
#define PCM5122_REG_GPIO_ENABLE        0x08 ///< GPIO output enables
#define PCM5122_REG_BCK_LRCLK          0x09 ///< BCK and LRCLK configuration
#define PCM5122_REG_DSP_GPIO           0x0A ///< DSP GPIO input
#define PCM5122_REG_MASTER_MODE_RST    0x0C ///< Master mode BCK/LRCLK reset
#define PCM5122_REG_PLL_REF            0x0D ///< PLL clock source select
#define PCM5122_REG_DAC_CLK_SRC        0x0E ///< DAC clock source
#define PCM5122_REG_GPIO_PLL_REF       0x12 ///< GPIO source for PLL reference
#define PCM5122_REG_SYNC_REQ           0x13 ///< Sync request
#define PCM5122_REG_PLL_P              0x14 ///< PLL P divider
#define PCM5122_REG_PLL_J              0x15 ///< PLL J divider
#define PCM5122_REG_PLL_D_MSB          0x16 ///< PLL D divider MSB
#define PCM5122_REG_PLL_D_LSB          0x17 ///< PLL D divider LSB
#define PCM5122_REG_PLL_R              0x18 ///< PLL R divider
#define PCM5122_REG_DSP_CLK_DIV        0x1B ///< DSP clock divider
#define PCM5122_REG_DAC_CLK_DIV        0x1C ///< DAC clock divider
#define PCM5122_REG_NCP_CLK_DIV        0x1D ///< NCP clock divider
#define PCM5122_REG_OSR_CLK_DIV        0x1E ///< OSR clock divider
#define PCM5122_REG_MASTER_BCK_DIV     0x20 ///< Master mode BCK divider
#define PCM5122_REG_MASTER_LRCK_DIV    0x21 ///< Master mode LRCLK divider
#define PCM5122_REG_FS_SPEED           0x22 ///< FS speed mode
#define PCM5122_REG_IDAC_MSB           0x23 ///< IDAC MSB
#define PCM5122_REG_IDAC_LSB           0x24 ///< IDAC LSB
#define PCM5122_REG_ERROR_DETECT       0x25 ///< Error detection control
#define PCM5122_REG_I2S_CONFIG         0x28 ///< I2S configuration
#define PCM5122_REG_I2S_OFFSET         0x29 ///< I2S offset
#define PCM5122_REG_I2S_UPSAMPLE       0x2A ///< I2S upsampling
#define PCM5122_REG_DSP_PROGRAM        0x2B ///< DSP program selection
#define PCM5122_REG_CLK_MISSING        0x2C ///< Clock missing detection
#define PCM5122_REG_AUTO_MUTE_TIME     0x3B ///< Auto mute time
#define PCM5122_REG_DIGITAL_VOLUME_CTL 0x3C ///< Digital volume control
#define PCM5122_REG_DIGITAL_VOLUME_L   0x3D ///< Digital volume left channel
#define PCM5122_REG_DIGITAL_VOLUME_R   0x3E ///< Digital volume right channel
#define PCM5122_REG_VOLUME_FADE        0x3F ///< Volume fade control
#define PCM5122_REG_VOLUME_FADE_EMRG   0x40 ///< Emergency volume fade
#define PCM5122_REG_AUTO_MUTE          0x41 ///< Auto mute control
#define PCM5122_REG_GPIO1_OUTPUT       0x50 ///< GPIO1 output selection
#define PCM5122_REG_GPIO2_OUTPUT       0x51 ///< GPIO2 output selection
#define PCM5122_REG_GPIO3_OUTPUT       0x52 ///< GPIO3 output selection
#define PCM5122_REG_GPIO4_OUTPUT       0x53 ///< GPIO4 output selection
#define PCM5122_REG_GPIO5_OUTPUT       0x54 ///< GPIO5 output selection
#define PCM5122_REG_GPIO6_OUTPUT       0x55 ///< GPIO6 output selection
#define PCM5122_REG_GPIO_CONTROL       0x56 ///< GPIO control
#define PCM5122_REG_GPIO_INVERT        0x57 ///< GPIO invert
#define PCM5122_REG_DSP_OVERFLOW       0x5A ///< DSP overflow flags
#define PCM5122_REG_RATE_DETECT_1      0x5B ///< Sample rate detection 1
#define PCM5122_REG_RATE_DETECT_2      0x5C ///< Sample rate detection 2
#define PCM5122_REG_RATE_DETECT_3      0x5D ///< Sample rate detection 3
#define PCM5122_REG_RATE_DETECT_4      0x5E ///< Sample rate detection 4
#define PCM5122_REG_CLOCK_STATUS       0x5F ///< Clock status
#define PCM5122_REG_ANALOG_MUTE        0x6C ///< Analog mute monitor
#define PCM5122_REG_POWER_STATE        0x76 ///< Power state and DSP boot status
#define PCM5122_REG_GPIO_INPUT         0x77 ///< GPIO input
#define PCM5122_REG_AUTO_MUTE_FLAG     0x78 ///< Auto mute flags
