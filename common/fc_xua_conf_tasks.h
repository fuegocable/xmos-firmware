on tile[XUA_XUD_TILE_NUM]:
{
    // Fuegocable audio device main function
    fc_audio_device_main();
}

on tile[XUA_AUDIO_IO_TILE_NUM]:
{
    // Fuegocable ui refresh main thread (leds, display)
    fc_ui_refresh_thread();
}