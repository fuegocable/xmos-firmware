#include "fc_spi.h"
#include "spi.h"

unsafe client interface spi_master_if fc_spi_client;

void fc_spi_begin_transaction(unsigned device_index, unsigned speed_in_khz, fc_spi_mode_t mode)
{
    unsafe
    {
        // FIXME: translate fc_spi_mode_t
        fc_spi_client.begin_transaction(device_index, speed_in_khz, mode);
    }
}

void fc_spi_end_transaction(unsigned ss_deassert_time)
{
    unsafe { fc_spi_client.end_transaction(ss_deassert_time); }
}

uint8_t fc_spi_transfer8(uint8_t data)
{
    unsafe { return fc_spi_client.transfer8(data); }
}

uint32_t fc_spi_transfer32(uint32_t data)
{
    unsafe { return fc_spi_client.transfer32(data); }
}

void fc_spi_transfer_array(NULLABLE_ARRAY_OF(const uint8_t, data_out),
                           NULLABLE_ARRAY_OF(uint8_t, data_in), static_const_size_t num_bytes)
{
    unsafe
    {
        // FIXME: translate static_const_size_t
        fc_spi_client.transfer_array(data_out, data_in, num_bytes);
    }
}

void fc_spi_set_ss_port_bit(unsigned device_index, unsigned ss_port_bit)
{
    unsafe { fc_spi_client.set_ss_port_bit(device_index, ss_port_bit); }
}

void fc_spi_set_miso_capture_timing(unsigned device_index,
                                    fc_spi_master_miso_capture_timing_t miso_capture_timing)
{
    unsafe
    {
        // FIXME: implement
        // FIXME: translate fc_spi_master_miso_capture_timing_t
        // fc_spi_client.set_miso_capture_timing(device_index, miso_capture_timing);
    }
}

void fc_spi_set_ss_clock_timing(unsigned device_index, fc_spi_master_ss_clock_timing_t ss_clock_timing)
{
    unsafe
    {
        // FIXME: implement
        // FIXME: translate fc_spi_master_ss_clock_timing_t
        // fc_spi_client.set_ss_clock_timing(device_index, ss_clock_timing);
    }
}

void fc_spi_shutdown()
{
    unsafe { fc_spi_client.shutdown(); }
}
