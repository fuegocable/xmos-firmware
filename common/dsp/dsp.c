#include <xua_audiohub.h>
#include <math.h>
#include <stdint.h>

// TODO: no usar un número fijo, usar I2S_CHANS_ADC. hay que definirlo en el audio_device
#define VUMETER_NUM_CHANNELS 8

int32_t inputVumeter[VUMETER_NUM_CHANNELS];

void UserBufferManagementInit(unsigned sampFreq)
{
    for(unsigned i = 0; i < VUMETER_NUM_CHANNELS; i++) {
        inputVumeter[i] = 0;
    }
}

void UserBufferManagement(unsigned sampsFromUsbToAudio[], unsigned sampsFromAudioToUsb[])
{
    int32_t currentSample;
    for(unsigned i = 0; i < VUMETER_NUM_CHANNELS; i++) {
        currentSample = ((int32_t *)sampsFromAudioToUsb)[i];
        currentSample = currentSample > 0 ? currentSample : -currentSample;
        inputVumeter[i] = (inputVumeter[i] > currentSample) ? inputVumeter[i] : currentSample;
    }
}