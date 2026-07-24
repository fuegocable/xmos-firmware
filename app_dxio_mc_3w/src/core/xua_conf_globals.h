#include <board/board.h>

/* Global to save I2C interface for configuring external audio hardware - used in
 * src/extensions/audiohw.xc */
extern unsafe client interface i2c_master_if i_i2c_client;

/* Note, this declaration could also have made in user_main_declarations.h */
#define USER_MAIN_DECLARATIONS interface i2c_master_if i2c[1];
