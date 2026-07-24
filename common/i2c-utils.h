#include "i2c.h"

i2c_regop_res_t i2c_reg_write(CLIENT_INTERFACE(i2c_master_if, i2c), uint8_t device_addr,
                              uint8_t reg, uint8_t data);