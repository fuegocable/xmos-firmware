#include "board/gpio_access.h"
#include <swlock.h>
#include <xcore/port.h>
#include <xs1.h>

static swlock_t gpo_swlock = SWLOCK_INITIAL_VALUE;
extern port_t p_gpio_0;

void p_gpio_lock() { swlock_acquire(&gpo_swlock); }
void p_gpio_unlock() { swlock_release(&gpo_swlock); }

unsigned p_gpio_peek()
{
    unsigned portId, x;

    asm("ldw %0, dp[p_gpio_0]" : "=r"(portId));
    asm volatile("peek %0, res[%1]" : "=r"(x) : "r"(portId));

    return x;
}

void p_gpio_out(unsigned x)
{
    unsigned portId;

    asm("ldw %0, dp[p_gpio_0]" : "=r"(portId));
    asm volatile("out res[%0], %1" ::"r"(portId), "r"(x));
}

void set_gpio(unsigned bit, unsigned value)
{
    // Wrapped in lock to ensure it's safe from multiple logical cores
    swlock_acquire(&gpo_swlock);
    unsigned port_shadow;
    port_shadow = p_gpio_peek(); // Read port pin value
    if (value == 0)
        port_shadow &= ~bit; // If writing a 0, generate mask and AND with current val
    else
        port_shadow |= bit;  // Else use mask and OR to set bit
    p_gpio_out(port_shadow); // Write back to port. Will make port an output if not already
    // Wrapped in lock to ensure it's safe from multiple logical cores
    swlock_release(&gpo_swlock);
}
