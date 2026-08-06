#pragma once

#define XUA_PCM_FORMAT XUA_PCM_FORMAT_TDM

#define MAX_FREQ (96000)

#define CODEC_MASTER 1

/* Identificates as Presonus AudioBox 1818 VSL */
#define VENDOR_ID (0x194f)
#define PID_AUDIO_2 (0x0103) 
#define PID_AUDIO_1 (0x0103)
#define VENDOR_STR "PreSonus"
#define PRODUCT_STR_A2 "AudioBox 1818 VSL"
#define PRODUCT_STR_A1 "AudioBox 1818 VSL"

#define PRESONUS_DEFAULT_SERIAL_STRING "1111"

// TODO: Define XUA configuration constants here (like XUA_MAX_CHAN_OUT, XUA_MAX_CHAN_IN, etc.)