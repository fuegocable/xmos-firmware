#pragma once

#include <xcore/port.h>

#ifdef __XC__
extern "C" {
#endif

void p_gpio_lock();
void p_gpio_unlock();

/// Read the port
unsigned p_gpio_peek(port_t port_gpio);

/// write to the port
void p_gpio_out(port_t port_gpio, unsigned x);

/// set individual bits
void set_gpio(port_t port_gpio, unsigned bit, unsigned value);

#ifdef __XC__
}
#endif
