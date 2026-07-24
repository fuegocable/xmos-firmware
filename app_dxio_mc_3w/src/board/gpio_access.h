#pragma once

#ifdef __XC__
extern "C" {
#endif

#define P_GPIO_SEL_MCLK_441 (1 << 3)
#define P_GPIO_SEL_MCLK_48  (1 << 7)

void p_gpio_lock();
void p_gpio_unlock();

/// Read the port
unsigned p_gpio_peek();

/// write to the port
void p_gpio_out(unsigned x);

/// set individual bits
void set_gpio(unsigned bit, unsigned value);

#ifdef __XC__
}
#endif
