on tile[XUA_XUD_TILE_NUM]:
{
    // TODO: Check if functions should and can be called from a "par {}" inside this "on tile{}"
    
    // Fuegocable audio device main function
    fc_audio_device_main();

    // Fuegocable ui refresh main thread (leds, display)
    fc_ui_refresh_thread();
}
