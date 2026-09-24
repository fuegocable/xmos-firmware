#pragma once

#define P_FC_GPIO_PORT          PORT_GPIO_0
#define P_FC_GPIO_TILE_NUM      PORT_GPIO_0_TILE_NUM
#define P_FC_GPIO_PORT_INSTANCE p_gpio_0

#define P_FC_GPIO_0_PORT_BIT 0
#define P_FC_GPIO_0          P_FC_GPIO_PORT_INSTANCE, (1 << P_FC_GPIO_0_PORT_BIT)

#define P_FC_GPIO_1_PORT_BIT 1
#define P_FC_GPIO_1          P_FC_GPIO_PORT_INSTANCE, (1 << P_FC_GPIO_1_PORT_BIT)

#define P_FC_GPIO_2_PORT_BIT 2
#define P_FC_GPIO_2          P_FC_GPIO_PORT_INSTANCE, (1 << P_FC_GPIO_2_PORT_BIT)

#define P_FC_GPIO_3_PORT_BIT 4
#define P_FC_GPIO_3          P_FC_GPIO_PORT_INSTANCE, (1 << P_FC_GPIO_3_PORT_BIT)

#define P_GPIO_SEL_MCLK_441 (1 << 3)
#define P_GPIO_SEL_MCLK_48  (1 << 7)

void enable_mclk(unsigned mClk);
