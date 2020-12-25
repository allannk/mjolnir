#pragma once

#include <stdint.h>
#include <targets/traits.h>

#if defined(STM32F030F4) || defined(STM32F030F6)
	#include <targets/mcu/stm32f030f4.h>
	#include <targets/stm32/stm32.h>
	#include <targets/stm32/stm32f0.h>
#elif defined(STM32F103C6)
	#include <targets/mcu/stm32f103c6.h>
	#include <targets/stm32/stm32.h>
	#include <targets/stm32/stm32f1.h>
#else
	#warning "Unknown MCU specified"
#endif