#include <xua_audiohub.h>
#include <math.h>
#include <stdint.h>
#include <xcore/hwtimer.h>
#include "audio_device_ui.h"

void fc_ui_refresh_thread()
{
    const uint32_t refresh_interval_ms = 500;
    const uint32_t ref_clock_freq = 100000000; // 100MHz reference clock
    const uint32_t refresh_interval_ticks = (refresh_interval_ms * ref_clock_freq) / 1000;
    
    while (1) {
        uint32_t next_update = get_reference_time() + refresh_interval_ticks;
        
        fc_audio_device_ui_refresh();
        
        while (get_reference_time() < next_update);
    }
}
