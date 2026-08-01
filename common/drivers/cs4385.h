#pragma once

#define CS4385_I2C_ADDR (0x18)
#define CS4385_SPI_ADDR 0b0011000

// Register Addresess
#define CS4385_CHIP_REV  0x01
#define CS4385_MODE_CTRL 0x02
#define CS4385_PCM_CTRL  0x03
#define CS4385_DSD_CTRL  0x04
#define CS4385_FLT_CTRL  0x05
#define CS4385_INV_CTRL  0x06
#define CS4385_GRP_CTRL  0x07
#define CS4385_RMP_MUTE  0x08
#define CS4385_MUTE_CTRL 0x09
#define CS4385_MIX_PR1   0x0a
#define CS4385_VOL_A1    0x0b
#define CS4385_VOL_B1    0x0c
#define CS4385_MIX_PR2   0x0d
#define CS4385_VOL_A2    0x0e
#define CS4385_VOL_B2    0x0f
#define CS4385_MIX_PR3   0x10
#define CS4385_VOL_A3    0x11
#define CS4385_VOL_B3    0x12
#define CS4385_MIX_PR4   0x13
#define CS4385_VOL_A4    0x14
#define CS4385_VOL_B4    0x15
#define CS4385_CM_MODE   0x16
