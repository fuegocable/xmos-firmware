on tile[PORT_I2C_TILE_NUM]: { dxio_mc_3w_i2c_master(i2c); }

on tile[PORT_SPI_SCLK_TILE_NUM]: { dxio_mc_3w_spi_master(spi); }

on tile[XUA_AUDIO_IO_TILE_NUM]:
{
    unsafe
    {
        i_i2c_client = i2c[0];
        i_spi_client = spi[0];
    }
}

on tile[XUA_XUD_TILE_NUM]:
{
    // Fuegocable audio device main function
    fc_audio_device_main();
}