#pragma once

#include <targets/mcu/stm32f030f4.h>

struct clock {
    const u32 address = AHB_BASE + 0x00001000UL;

    enum class port { a, b, c, d, e, f };

    struct  __attribute__((packed)) clock_reg {
        union { u32 RCC_CR; };
        union { u32 RCC_CFGR; };
        union { u32 RCC_CIR; };
        union { u32 RCC_APB2RSTR; };
        union { u32 RCC_APB1RSTR; };
        union { u32 RCC_AHBENR;
            struct {
                u32 DMAEN :1;
                u32 DMA2EN :1;
                u32 SRAMEN :1;
                u32 :1;
                u32 FLITFEN :1;
                u32 :1;
                u32 CRCEN :1;
                u32 :10;
                u32 IOPAEN :1;
                u32 IOPBEN :1;
                u32 IOPCEN :1;
                u32 IOPDEN :1;
                u32 IOPEEN :1;
                u32 IOPFEN :1;
                u32 :1;
                u32 TSCEN :1;
                u32 :7;
            };};
        union { u32 RCC_APB2ENR; 
            struct {
                u32 SYSCFGCOMPEN :1;
                u32 :4;
                u32 USART6EN :1;
                u32 USART7EN :1;
                u32 USART8EN :1;
                u32 :1;
                u32 ADCEN :1;
                u32 :1;
                u32 TIM1EN :1;
                u32 SPI1EN :1;
                u32 :1;
                u32 USART1EN :1;
                u32 :1;
                u32 TIM15EN :1;
                u32 TIM16EN :1;
                u32 TIM17EN :1;
                u32 :3;
                u32 DBGMCUEN :1;
                u32 :9;
            };};
        union { u32 RCC_APB1ENR;
            struct {
                u32 TIM2EN :1;
                u32 TIM3EN :1;
                u32 :2;
                u32 TIM6EN :1;
                u32 TIM7EN :1;
                u32 :2;
                u32 TIM14EN :1;
                u32 :2;
                u32 WWDGEN :1;
                u32 :2;
                u32 SPI2EN :1;
                u32 :2;
                u32 USART2EN :1;
                u32 USART3EN :1;
                u32 USART4EN :1;
                u32 USART5EN :1;
                u32 I2C1EN :1;
                u32 I2C2EN :1;
                u32 USBEN :1;
                u32 :1;
                u32 CANEN :1;
                u32 :1;
                u32 CRSEN :1;
                u32 PWREN :1;
                u32 DACEN :1;
                u32 CECEN :1;
                u32 :1;
            };};
        union { u32 RCC_BDCR; };
        union { u32 RCC_CSR; };
        union { u32 RCC_AHBRSTR; };
        union { u32 RCC_CFGR2; };
        union { u32 RCC_CFGR3; };
        union { u32 RCC_CR2; };
    };

    static inline volatile clock_reg& reg{ *reinterpret_cast<clock_reg *>(AHB_BASE + 0x00001000UL) };

    // TODO: This is not optimized!
    SCA enable_port(port p) {
        if(p == port::a) reg.IOPAEN = 1;
        else if(p == port::b) reg.IOPBEN = 1;
        else if(p == port::c) reg.IOPCEN = 1;
        else if(p == port::d) reg.IOPDEN = 1;
        else if(p == port::e) reg.IOPEEN = 1;
        else if(p == port::f) reg.IOPFEN = 1;
    }
};

namespace gpio {
    template <pin p>
    struct gpio {
       
        SCA pin_ { p % 16 };
        SCA port_ { AHB2_BASE + 0x400 * (p / 16) };

        struct __attribute__((packed)) pinregister {
            union { 
                u32 MODER;
                struct { u32 : 2 * pin_; u32 MODERb : 2; u32 : 30 - 2 * pin_; };
            };
            union {
                u32 OTYPER;
                struct { u32 : pin_; u32 OTYPERb : 1; u32 : 31 - pin_; };
            };
            union {
                u32 OSPEEDR;
                struct { u32 : 2 * pin_; u32 OSPEEDRb : 2; u32 : 30 - 2 * pin_; };
            };
            union {
                u32 PUPDR;
                struct { u32 : 2 * pin_; u32 PUPDRb : 2; u32 : 30 - 2 * pin_; };
            };
            union {
                u32 IDR;
                struct { u32 : pin_; u32 IDRb : 1; u32 : 31 - pin_; };
            };
            union {
                u32 ODR;
                struct { u32 : pin_; u32 ODRb : 1; u32 : 31 - pin_; };
            };
            union {
                u32 BSRR;
                struct { u16 BSRR_SET; u16 BSRR_RESET; };
                struct {
                    u32 : pin_;
                    u32 BSRR_SETb : 1;
                    u32 : 15;
                    u32 BSRR_RESETb : 1;
                    u32 : 15 - pin_;
                };
            };
            union { 
                u32 LCKR;
                struct { u32:pin_; u32 LCKRb :1;    u32:31-pin_;}; 
            };
            union {
                u64 AFR;
                struct {u64:4 * pin_; u64 AFRb : 4; u64:60-4*pin_; };
                struct {
                    union { // WARNING: AFRL is *ONLY* for pin 0-7
                        u32 AFRL;
                        struct {u32:4*(pin_%8); u32 AFRLb :4; u32:28-4*(pin_%8); };
                    };
                    union { // WARNING: AFRH is *ONLY* for pin 8-15
                        u32 AFRH;
                        struct {u32:4*(pin_%8); u32 AFRHb :4; u32:28-4*(pin_%8); };
                    };
                };
            };
            union {
                u32 BRR;
                struct { u32:pin_; u32 BRRb :1; u32:31-pin_; };
            };
        };

        static inline volatile pinregister& reg{ *reinterpret_cast<pinregister *>(port_) };

      private:
        // Constructor functions
        template <typename ...ts> SCA conf_(pinregister &it, mode v, ts... t) { it.MODERb = v; conf_(it, t...); }
        template <typename ...ts> SCA conf_(pinregister &it, otype v, ts... t) { it.OTYPERb = v; conf_(it, t...); }
        template <typename ...ts> SCA conf_(pinregister &it, speed v, ts... t) { it.OSPEEDRb = v; conf_(it, t...); }
        template <typename ...ts> SCA conf_(pinregister &it, pull v, ts... t) { it.PUPDRb = v; conf_(it, t...); }
        template <typename ...ts> SCA conf_(pinregister &it, value v, ts... t) { it.ODRb = v; conf_(it, t...); }
        template <typename ...ts> SCA conf_(pinregister &it, altfun v, ts... t) { it.AFRb = v; conf_(it, t...); }

        // No more values, perform actual initialization
        template <typename ...ts> SCA conf_(pinregister &it) {
            // TODO: Automatic port clock enable such as
            //       `power::enable(power::port::a);`

            // Step 1 -- essential pin setup
            reg.AFRb = it.AFRb;

            // Step 2 -- misc pin setup
            reg.OTYPERb = it.OTYPERb;
            reg.PUPDRb = it.PUPDRb;
            reg.OSPEEDRb = it.OSPEEDRb;
            reg.ODRb = it.ODRb;

            // Step 3 -- start pin
            reg.MODERb = it.MODERb;
        }


      public: // Utilization functions

        // Construction
        gpio() {}
        template<typename ...ts> gpio(ts... t) { configure(t...); }
        
        // Configuration
        template<typename... ts> auto configure(ts... t) { 
            pinregister pr;
            conf_(pr, t...);
        }
        SCA deinit() { reg.analog(); }

        SA pull_off() { reg.PUPDRb = pull::floating; }
        SA pull_up() { reg.PUPDRb = pull::up; }
        SA pull_down() { reg.PUPDRb = pull::down; }

        // General Purpose Input
        SA get() { return reg.IDRb; }
        SA is_on() { return reg.IDRb; }
        SA is_off() { return not reg.IDRb; }

        // General Purpose Output
        SA val(u8 v) { reg.ODRb = v & 0x01; }
        SA set(u8 v) { val(v); };
        SA set() { reg.BSRR_SETb = 1; }
        SA clear() { reg.BSRR_RESETb = 1; }
        SA high() { set(); }
        SA low() { clear(); }
        SA on() { set(); }
        SA off() { clear(); }
    };
}



// Check out https://github.com/cv007/C-PlusPlus-Peripheral-Style for inspiration




