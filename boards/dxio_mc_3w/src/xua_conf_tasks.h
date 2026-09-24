// Include fuegocable common xua conf tasks
#include "fc_xua_conf_tasks.h"

on tile[PORT_I2C_TILE_NUM]: { dxio_mc_3w_i2c_master(i2c); }

on tile[PORT_SPI_SCLK_TILE_NUM]: { dxio_mc_3w_spi_master(spi); }

on tile[XUA_AUDIO_IO_TILE_NUM]:
{
    unsafe
    {
        i_i2c_client = i2c[0];
        fc_spi_client = spi[0];
    }
}