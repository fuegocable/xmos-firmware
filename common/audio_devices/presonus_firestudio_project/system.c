#include "system.h"
#include "audio_device_ui.h"
#include "gpio_access.h"

#define LEDS_PER_CHANNEL 3

extern port_t P_FC_GPIO_PORT_INSTANCE;

void fc_presonus_fsp_adc_dac_reset_hold() { set_gpio(P_ADC_DAC_RESET_GPIO, 1); }

void fc_presonus_fsp_adc_dac_reset_release() { set_gpio(P_ADC_DAC_RESET_GPIO, 0); }

void fc_presonus_fsp_meters_output_enable() { set_gpio(P_METERS_OUTPUT_ENABLE_N_GPIO, 0); }

void fc_presonus_fsp_meters_output_disable() { set_gpio(P_METERS_OUTPUT_ENABLE_N_GPIO, 1); }

float fc_presonus_fsp_sample_to_dbfs(int32_t sample)
{
    const int32_t max_sample = 0x7fffff;
    if (sample == 0) {
        return -150.0f;
    }
    sample >>= 8;
    float ratio = (float)sample / (float)max_sample;
    return 20.0f * log10f(ratio);
}

uint8_t fc_presonus_fsp_sample_to_led_value(int32_t sample)
{
    float dbfs = fc_presonus_fsp_sample_to_dbfs(sample);

    if (dbfs < -40.0f) {
        return 0b000;
    }
    if (dbfs < -6.0f) {
        return 0b001;
    }
    if (dbfs < 0.0f) {
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
