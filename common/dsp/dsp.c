#include <xua_audiohub.h>

int32_t inputVumeter[I2S_CHANS_ADC];

void UserBufferManagement(unsigned *samplesFromUsbToAudio, unsigned *samplesFromAudioToUsb)
{
    /** Copy samples to vumeter array */
    int32_t currentSample;
    for(unsigned i = 0; i < I2S_CHANS_ADC; i++) {
        currentSample = ((int32_t *)samplesFromAudioToUsb)[i];
        currentSample = currentSample > 0 ? currentSample : -currentSample;
        inputVumeter[i] = (inputVumeter[i] > currentSample) ? inputVumeter[i] : currentSample;
    }
}