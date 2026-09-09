#include <xua_audiohub.h>
#include <math.h>
#include <stdint.h>
#include "audio_device.h"

void UserBufferManagementInit(unsigned sampFreq)
{
    fc_audio_device_buffer_management_init(sampFreq);
}

void UserBufferManagement(unsigned sampsFromUsbToAudio[], unsigned sampsFromAudioToUsb[])
{
    fc_audio_device_buffer_management(sampsFromUsbToAudio, sampsFromAudioToUsb);
}