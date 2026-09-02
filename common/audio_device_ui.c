void fc_ui_refresh_thread()
{
    // register timer and add select

    // on timer:
        // read vumeter global variable and copy to other local var
        // set global vu to 0 (así sigue acumulando máximos el otro thread)
        // calc dbfs
        // call fc_audio_device_update_vumeter o algo así, definido en audio_device que llame a spi en presonus xejemplo
}
