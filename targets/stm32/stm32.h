#pragma once

// Base peripheral address
#define PERIPH_BASE 0x40000000UL

// Base ... addresses
#define APB_BASE PERIPH_BASE
#define AHB_BASE (PERIPH_BASE + 0x00020000UL)
#define AHB2_BASE (PERIPH_BASE + 0x08000000UL)

namespace gpio {
    enum mode { input, output, alternative, analog };
    enum otype { push_pull, open_drain };
    enum speed { slow, medium, fast = 0x11 };
    enum pull { floating, up, down };
    enum value { low, high };
    enum altfun { af0, af1, af2, af3, af4, af5, af6, af7, af8, af9, af10, af11, af12, af13, af14, af15 };
} // namespace gpio
