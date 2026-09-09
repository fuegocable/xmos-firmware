#include "system.h"
#include "audio_device_ui.h"
#include "gpio_access.h"
#include <math.h>

#define LEDS_PER_CHANNEL 3

extern port_t P_FC_GPIO_PORT_INSTANCE;

void fc_presonus_fsp_adc_dac_reset_hold() { set_gpio(P_ADC_DAC_RESET_GPIO, 1); }

void fc_presonus_fsp_adc_dac_reset_release() { set_gpio(P_ADC_DAC_RESET_GPIO, 0); }

void fc_presonus_fsp_meters_output_enable() { set_gpio(P_METERS_OUTPUT_ENABLE_N_GPIO, 0); }

void fc_presonus_fsp_meters_output_disable() { set_gpio(P_METERS_OUTPUT_ENABLE_N_GPIO, 1); }

int32_t fc_presonus_fsp_sample_to_dbfs(int32_t sample)
{
    const int32_t max_sample = 8388607;
    if (sample == 0) {
        return -150;
    }
    return 20 * log10f((float)sample / (float)max_sample);
}

uint8_t fc_presonus_fsp_sample_to_led_value(int32_t sample)
{
    /**
     * The VU meter on this audio device measures -40 dB, -6 dB, and 0 dB. We don't use exactly
     * those values ​​here because, in principle, it involves True Peak, and the information
     * perceived from the VU meter in that case doesn't align very closely with the signal's actual
     * energy.
     */
    int32_t dbfs = fc_presonus_fsp_sample_to_dbfs(sample);

    if (dbfs < -28) {
        return 0b000;
    }
    if (dbfs < -12) {
        return 0b001;
    }
    if (dbfs < -2) {
        return 0b011;
    }
    return 0b111;
}

void fc_presonus_fsp_meters_update(char channel_leds[8])
{
    uint32_t transfer =
        channel_leds[7] << (7 * LEDS_PER_CHANNEL) | channel_leds[6] << (6 * LEDS_PER_CHANNEL) |
        channel_leds[5] << (5 * LEDS_PER_CHANNEL) | channel_leds[4] << (4 * LEDS_PER_CHANNEL) |
        channel_leds[3] << (3 * LEDS_PER_CHANNEL) | channel_leds[2] << (2 * LEDS_PER_CHANNEL) |
        channel_leds[1] << (1 * LEDS_PER_CHANNEL) | channel_leds[0] << (0 * LEDS_PER_CHANNEL);
    fc_spi_begin_transaction(METERS_SPI_DEVICE, METERS_SPI_SPEED_IN_KHZ, METERS_SPI_MODE);
    fc_spi_transfer8((transfer >> 16) & 0xFF);
    fc_spi_transfer8((transfer >> 8) & 0xFF);
    fc_spi_transfer8(transfer & 0xFF);
    fc_spi_end_transaction(METERS_SPI_SS_DELAY);
}
