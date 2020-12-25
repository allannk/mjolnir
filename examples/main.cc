#pragma pack(1)
#include "targets/barden.h"

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//   Temporary, until we have RCC implemented..!
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

typedef struct {
    uint32_t CR;
    uint32_t CFGR;
    uint32_t CIR;
    uint32_t APB2RSTR;
    uint32_t APB1RSTR;
    uint32_t AHBENR;
    uint32_t APB2ENR;
    uint32_t APB1ENR;
    uint32_t BDCR;
    uint32_t CSR;
} RCC_TypeDef;

// typedef struct {
//     uint32_t MODER;
//     uint32_t OTYPER;
//     uint32_t OSPEEDR;
//     uint32_t PUPDR;
//     uint32_t IDR;
//     uint32_t ODR;
//     uint32_t BSRR;
//     uint32_t LCKR;
//     uint32_t AFR[2];
//     uint32_t BRR;
// } GPIO_TypeDef;

#define APB1PERIPH_BASE PERIPH_BASE
#define AHB2PERIPH_BASE (PERIPH_BASE + 0x08000000UL)
#define AHBPERIPH_BASE (PERIPH_BASE + 0x00020000UL)
#define RCC_BASE (AHBPERIPH_BASE + 0x00001000UL)
#define RCC ((RCC_TypeDef *) RCC_BASE)

// STM32F030:
#define RCC_AHBENR_GPIOAEN_Pos (17U)
#define RCC_AHBENR_GPIOAEN_Msk (0x1UL << RCC_AHBENR_GPIOAEN_Pos) /*!< 0x00020000 */
#define RCC_AHBENR_GPIOAEN RCC_AHBENR_GPIOAEN_Msk /*!< GPIOA clock enable */

// #define GPIOA_BASE (AHB2PERIPH_BASE + 0x00000000UL)
// #define GPIOA ((GPIO_TypeDef *) GPIOA_BASE)

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

int main() {
    // RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
//    power::power pwr();
    power::enable_port(power::port::a);
//    pwr.enable(power::port_a);


    gpio::gpio<pin::A4> led(gpio::mode::output);

    // osc::frequency(pll_mul_14, pll_div_8);
    // osc::source(osc::HSI);
    // osc::power(osc::gpioA); // Call this from gpio setup!
    
    // uart<pin::A9, pin::A10> console_uart(57000);
    // i2c<pin::A10, pin::A9> sensor_i2c(mode::host);
    // spi<pin::A5, pin::A6, pin::A7> screen_spi();
    // swd<pin::A13, pin::A14> debug_swd();
    // pwm<pin::A4> led_pwm(70);
    // gpio<pin::A0> lightsense_analog();

    while(1) {
        // Turn OFF LED
        // ────────────
        led.high();
        for(int i = 0; i < 300000; ++i);

        // Turn ON LED
        // ────────────
        led.low();
        for(int i = 0; i < 100000; ++i);
    }
}


// int main() {
//     // Misc conf:
//     RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

//     // GPIOA->MODER &= ~(0x03 << (4 * 2));
//     // GPIOA->MODER |=  (0x01 << (4 * 2));
//     // GPIOA->OTYPER &= ~(0x01 << 4);
//     // GPIOA->BSRR |= 0x01 << 4;

//     gpio::gpio<pin::A4> led(gpio::mode::output, gpio::value::high);//,
//     //    pins::pull::down,
//     //    pins::otype::push_pull,
//     //    pins::speed::low);

//     // led.on();

//     while(1) {
//         // GPIOA->ODR |= 1 << 4; // Turn OFF LED
//         // led.low();
//         for(int i=0; i<200000; ++i);


//         // GPIOA->ODR &= ~(1 << 4); // Turn ON LED
//         // led.high();
//         led.test_on();
//         for(int i=0; i<500000; ++i);

//     }
// }


// // Dream up

// int main(void) {
//     osc::


//     pin<A10> led {output, high_is_on}
//     pin<B3> sw {input, pullup, low_is_on}

//     led.off();

//     while(true) {
//         timer::sleep(100);
//         if(sw.is_on()) led.toggle();
//     }
// }


// // Working

// #include "main.h"

// class IO {
//   public:
//     IO();
//     virtual unsigned read() { return 0x00000000; }
//     virtual void write(unsigned) { return; }
//     virtual void enable_clock(void);
//     virtual void disable(void);
// }

// template <int pin, int bank> class GPIO : public IO {
//   public:
//     GPIO() {}
//     virtual unsigned read() { ; }
//     virtual void write(unsigned d){ d ? set() : clear(); }
//     virtual void set(void) { bank->BSRR |= 0x01 << pin; }
//     virtual void clear(void) { bank}>BRR |= 0x01 << pin; }
// }

// template <int pin> class GPIO {
//   public:
//     GPIO() {
//         GPIOA->MODER &= ~(0x03 << (pin * 2));
//         GPIOA->MODER |=  (0x01 << (pin * 2));
//         GPIOA->OTYPER &= ~(0x01 << pin);
//     }

//     void set(void) {
//         GPIOA->BSRR |= 0x01 << pin;
//     }

//     void reset(void) {
//         GPIOA->BRR |= 0x01 << pin;
//     }
// };


// controller::set_frequency();
// spi::setup<2>();
// gpio::setup<B13>();

// class Controller {
//     Controller();

//     bool set_frequency();

// };


// bool Controller::set_frequency() {

// }


// template <int pin> class GPIO {
//   public:
//     GPIO() {
//         GPIOA->MODER &= ~(0x03 << (pin * 2));
//         GPIOA->MODER |=  (0x01 << (pin * 2));
//         GPIOA->OTYPER &= ~(0x01 << pin);
//     }

//     void set(void) {
//         GPIOA->BSRR |= 0x01 << pin;
//     }

//     void reset(void) {
//         GPIOA->BRR |= 0x01 << pin;
//     }
// };


// Controller controller();

// int main(void) {
//     RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
//     GPIO<4> led;
    
//     led.reset();

//     while(1);
// }
