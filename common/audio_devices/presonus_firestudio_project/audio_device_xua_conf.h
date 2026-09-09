#pragma once

#define I2S_CHANS_DAC (8)
#define I2S_CHANS_ADC (8)
#define XUA_PCM_FORMAT XUA_PCM_FORMAT_TDM
#define MAX_FREQ (96000)
#define CODEC_MASTER 1
#define MIDI 1

/* Identificates as Presonus AudioBox 1818 VSL */
#define VENDOR_ID (0x194f)
#define PID_AUDIO_2 (0x0103) 
#define PID_AUDIO_1 (0x0103)
#define VENDOR_STR "PreSonus"
#define PRODUCT_STR_A2 "AudioBox 1818 VSL"
#define PRODUCT_STR_A1 "AudioBox 1818 VSL"
#define PRESONUS_DEFAULT_SERIAL_STRING "1818"
// BCD Version (presonus firmware version)
#define BCD_DEVICE_J (1)
#define BCD_DEVICE_M (4)
#define BCD_DEVICE_N (9)
