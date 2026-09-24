// Include fuegocable common xua conf globals
#include "fc_xua_conf_globals.h"

#include "board.h"

extern unsafe client interface i2c_master_if i_i2c_client;
extern unsafe client interface spi_master_if fc_spi_client;

#define USER_MAIN_DECLARATIONS interface i2c_master_if i2c[1]; interface spi_master_if spi[1];
