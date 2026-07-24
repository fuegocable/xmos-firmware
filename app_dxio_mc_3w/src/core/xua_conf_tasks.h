on tile[PORT_I2C_TILE_NUM]:
{
    dxio_mc_3w_i2c_master(i2c);
}

on tile[XUA_AUDIO_IO_TILE_NUM]:
{
    unsafe { i_i2c_client = i2c[0]; }
}
