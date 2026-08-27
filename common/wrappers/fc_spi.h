#pragma once

/** This type indicates what clocking mode a SPI component should use */
typedef enum fc_spi_mode_t {
  FC_SPI_MODE_0 = 0, /**< SPI Mode 0 - Polarity = 0, Phase = 0 */
  FC_SPI_MODE_1 = 1, /**< SPI Mode 1 - Polarity = 0, Phase = 1 */
  FC_SPI_MODE_2 = 2, /**< SPI Mode 2 - Polarity = 1, Phase = 0 */
  FC_SPI_MODE_3 = 3, /**< SPI Mode 3 - Polarity = 1, Phase = 1 */
} fc_spi_mode_t;


/** This type contains timing settings for SS assert to clock delay and last 
 *  clock to SS de-assert delay. The unit is reference timer ticks which is 
 *  nominally 10 ns. The maximum setting is 65535 which equates to 655 us,
 *  over which the setting will overflow back to zero */
typedef struct fc_spi_master_ss_clock_timing_t {
  uint32_t cs_to_clk_delay_ticks;
  uint32_t clk_to_cs_delay_ticks;
} fc_spi_master_ss_clock_timing_t;


/**
 * Enum type representing the different options
 * for the SPI master sample delay.
 */
typedef enum {
    spi_master_sample_delay_1_2 = 0, /**< Samples 1/2 clock cycle after output from device */
    spi_master_sample_delay_3_4 = 1, /**< Samples 3/4 clock cycle after output from device */
    spi_master_sample_delay_1_0 = 2, /**< Samples 1 clock cycle after output from device */
    spi_master_sample_delay_5_4 = 3, /**< Samples 1 and 1/4 clock cycle after output from device */
    spi_master_sample_delay_3_2 = 4, /**< Samples 1 and 1/2 clock cycle after output from device */
} fc_spi_master_sample_delay_t;


/** This type contains timing settings for capturing the MISO pin for SPI master.
 *  When the SPI clock is above 20MHz it is usually necessary to delay the
 *  sampling of the MISO pin. These settings can be coarse grained using
 *  miso_sample_delay setting which increments in SPI half clocks or
 *  fine grained in units of core clock (eg. 600 MHz -> 1.66 ns) using the
 *  miso_pad_delay setting.
 *  
 *  See the following document for details on xcore.ai port timing:
 *  https://www.xmos.com/documentation/XM-014231-AN/html/rst/index.html */
typedef struct fc_spi_master_miso_capture_timing_t {
  fc_spi_master_sample_delay_t miso_sample_delay;
  uint32_t miso_pad_delay;
} fc_spi_master_miso_capture_timing_t;


void fc_spi_begin_transaction(unsigned device_index, unsigned speed_in_khz, fc_spi_mode_t mode);
void fc_spi_end_transaction(unsigned ss_deassert_time);
uint8_t fc_spi_transfer8(uint8_t data);
uint32_t fc_spi_transfer32(uint32_t data);
void fc_spi_transfer_array(NULLABLE_ARRAY_OF(const uint8_t, data_out), NULLABLE_ARRAY_OF(uint8_t, data_in), static_const_size_t num_bytes);
void fc_spi_set_ss_port_bit(unsigned device_index, unsigned ss_port_bit);
void fc_spi_set_miso_capture_timing(unsigned device_index, fc_spi_master_miso_capture_timing_t miso_capture_timing);
void fc_spi_set_ss_clock_timing(unsigned device_index, fc_spi_master_ss_clock_timing_t ss_clock_timing);
void fc_spi_shutdown(void);