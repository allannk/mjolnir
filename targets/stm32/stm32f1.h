#pragma once

// Base peripheral address
#define PERIPH_BASE           0x40000000UL

// Base ... addresses
#define APB_BASE        PERIPH_BASE
#define AHB_BASE        (PERIPH_BASE + 0x00020000UL)
#define AHB2_BASE       (PERIPH_BASE + 0x08000000UL)

