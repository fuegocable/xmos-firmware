#include "i2c.h"

i2c_regop_res_t i2c_reg_write(CLIENT_INTERFACE(i2c_master_if, i2c), uint8_t device_addr,
                              uint8_t reg, uint8_t data)
{
    uint8_t a_data[2] = {reg, data};
    size_t n;

    unsafe { i2c.write(device_addr, a_data, 2, n, 1); }

    if (n == 0) {
        return I2C_REGOP_DEVICE_NACK;
    }
    if (n < 2) {
        return I2C_REGOP_INCOMPLETE;
    }

    return I2C_REGOP_SUCCESS;
}