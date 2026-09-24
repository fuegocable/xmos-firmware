#include <platform.h>
#include "board_gpio.h"
#include <swlock.h>
#include <xcore/port.h>
#include <xs1.h>
#include "gpio_access.h"

extern port_t P_FC_GPIO_PORT_INSTANCE;

void enable_mclk(unsigned mClk) {
    set_gpio(P_FC_GPIO_PORT_INSTANCE, P_GPIO_SEL_MCLK_441, 0);
    set_gpio(P_FC_GPIO_PORT_INSTANCE, P_GPIO_SEL_MCLK_48, 0);
    delay_milliseconds(5);

    if (0 == mClk % 44100) {
        set_gpio(P_FC_GPIO_PORT_INSTANCE, P_GPIO_SEL_MCLK_441, 1);
    } else {
        set_gpio(P_FC_GPIO_PORT_INSTANCE, P_GPIO_SEL_MCLK_48, 1);
    }

    /* Allow MCLK to settle */
    delay_milliseconds(20);
}