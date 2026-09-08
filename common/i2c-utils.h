#pragma once

#include "i2c.h"

// TODO: Temp type definition copying sandbox/lib_i2c/lib_i2c/api/i2c.h. We need to revisiting it when making i2c wrapper
typedef enum {
  FC_I2C_REGOP_SUCCESS,     ///< the operation was successful
  FC_I2C_REGOP_DEVICE_NACK, ///< the operation was NACKed when sending the device address, so either the device is missing or busy
  FC_I2C_REGOP_INCOMPLETE   ///< the operation was NACKed halfway through by the slave
} fc_i2c_regop_res_t;

fc_i2c_regop_res_t i2c_reg_write(CLIENT_INTERFACE(i2c_master_if, i2c), uint8_t device_addr,
                              uint8_t reg, uint8_t data);