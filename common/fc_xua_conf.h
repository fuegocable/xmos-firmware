// Include audio_device specific xua conf
#include "audio_device_xua_conf.h"

#include "fc_version.h"

#ifndef BCD_DEVICE_J
#define BCD_DEVICE_J FC_VERSION_MAJOR
#endif
#ifndef BCD_DEVICE_M
#define BCD_DEVICE_M FC_VERSION_MINOR
#endif
#ifndef BCD_DEVICE_N
#define BCD_DEVICE_N FC_VERSION_PATCH
#endif
