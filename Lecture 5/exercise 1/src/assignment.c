#include <stdint.h>
#include <stdio.h>

///////////////////////////////////////////////////////////////////////////////
// Assignment 1
// ===========================================================================
// Write a function that configures pin 11 of GPIO port D as input with 
// pull-down resistor enabled.
// 
// ERIK: The test harness should set ODATA to 0xFFFF so it is pull up unless
//       they configure it. And give the hint, of course. 
//       It should also check that no other bits were changed. 
///////////////////////////////////////////////////////////////////////////////



// TODO: Macro definitions here
#define GPIO_D_BASE  0x40011400
#define GPIO_D_CFGLR ((volatile uint32_t *)(GPIO_D_BASE + 0x00))
#define GPIO_D_CFGHR ((volatile uint32_t *)(GPIO_D_BASE + 0x04))
#define GPIO_D_INDR  ((volatile uint32_t *)(GPIO_D_BASE + 0x08))
#define GPIO_D_OUTDR ((volatile uint32_t *)(GPIO_D_BASE + 0x0C))
#define GPIO_D_BSHR  ((volatile uint32_t *)(GPIO_D_BASE + 0x10))
#define GPIO_D_BCR   ((volatile uint32_t *)(GPIO_D_BASE + 0x14))

void assignment_1(void)
{
    //  ( 4 bits * pin number within register )
    //  Control program (main.c) is checking pin 12 and not 11?

    *GPIO_D_CFGHR &= ~(0xF << (4 * 5)); //  Clear pin config
    *GPIO_D_CFGHR |= (0x8 << (4 * 5));  //  Set pin config

    *GPIO_D_OUTDR &= ~(1 << 11);        //  Set pull-down to pin 11 (here it checks 11)
}

///////////////////////////////////////////////////////////////////////////////
// Assignment 2
// ===========================================================================
// Write a more general function that configures a pin of GPIO port D as
// input with pull up or down or floating.
// 
// ERIK: Test harness will make sure they only modified the relevant bits
//       and set them correctly. Need to check OUTDR as well for pull-up/down.
//       
//       Oh... for the keyboard, they really only need 8 pins... 
///////////////////////////////////////////////////////////////////////////////

void gpio_d_set_pin_input(
    int pin,    // The pin to configure (0-15)
    int mode    // 0 = PULLDOWN, 1 = PULLUP, 2 = FLOATING 
    )
{
    volatile uint32_t *reg;
    int conf = 0, outdr = 0;

    reg = (pin < 8) ? GPIO_D_CFGLR : GPIO_D_CFGHR;
    int regpin = pin % 8;

    switch (mode) {
    case 0: conf = 0x8; outdr = 0; break;
    case 1: conf = 0x8; outdr = 1; break;
    case 2: conf = 0x4; outdr = 0; break;
    default: printf("mode out of range\n"); return;
    }

    *reg &= ~(0xF << (4 * regpin));
    *reg |= (conf << (4 * regpin));

    *GPIO_D_OUTDR &= ~(1 << pin);
    *GPIO_D_OUTDR |= (outdr << pin);
}

///////////////////////////////////////////////////////////////////////////////
// Assignment 3
// ===========================================================================
// Write a function that configures a pin of GPIO port D as
// output with either push-pull or open-drain mode.
// The pin should be configured as output at 2 MHz.
///////////////////////////////////////////////////////////////////////////////
void gpio_d_set_pin_output( 
    int pin,    // The pin to configure
    int mode    // 0 = PUSHPULL, 1 = OPENDRAIN
    )
{
    volatile uint32_t *reg;
    int conf = 0;

    reg = (pin < 8) ? GPIO_D_CFGLR : GPIO_D_CFGHR;
    int regpin = pin % 8;

    switch (mode) {
    case 0: conf = 0x2; break;
    case 1: conf = 0x6; break;
    default: printf("mode out of range\n"); return;
    }

    *reg &= ~(0xF << (4 * regpin));
    *reg |= (conf << (4 * regpin));
}

///////////////////////////////////////////////////////////////////////////////
// Assignment 4
// ===========================================================================
// Write a function that sets one pin of GPIO port D high.
// The function should use the read-modify-write registers (BSHR or BCR)
///////////////////////////////////////////////////////////////////////////////
void gpio_d_set_pin_high(int pin)
{
    *GPIO_D_OUTDR |= (1 << pin);
}

///////////////////////////////////////////////////////////////////////////////
// Assignment 5
// ===========================================================================
// Write a function that sets one pin of GPIO port D low.
// The function should use the read-modify-write registers (BSHR or BCR)
void gpio_d_set_pin_low(int pin)
{   
    *GPIO_D_OUTDR &= ~(1 << pin);
}    

///////////////////////////////////////////////////////////////////////////////
// Assignment 6
// ===========================================================================
// In the simulator, connect the keyboard to GPIO port D (0-7)
// Write a function that returns the number of the button on the keyboard: 
//
// /-------------------\
// |  0 |  1 |  2 |  3 |
// |----|----|----|----|    
// |  4 |  5 |  6 |  7 |
// |----|----|----|----|
// |  8 |  9 | 10 | 11 |
// |----|----|----|----|
// | 12 | 13 | 14 | 15 |
// \-------------------/
// 
// Follow the instructions in comments
// You can the functions you have written above
///////////////////////////////////////////////////////////////////////////////
int get_keyboard_button(void)
{
    // Configure the row-selection pins (pins 4-7) as output, open drain, at 2 MHz
    for (int i = 4; i < 8; i++) {
        gpio_d_set_pin_output(i, 1);
    }

    // Configure the row-read pins (pins 0-3) as input with pull-up resistors
    for (int i = 0; i < 4; i++) {
        gpio_d_set_pin_input(i, 1);
    }

    // Deactivate all rows by setting pins the row selection pins  4-7 high
    // (remember that they are active low, so 0 selects a row)
    for (int i = 4; i < 8; i++) {
    gpio_d_set_pin_high(i);
    }

    for(int row = 0; row < 4; row++) {
        // Activate the current row by setting the corresponding pin low
        gpio_d_set_pin_low(row + 4);

        // Read the row (buttons 0-3, 4-7, 8-11, or 12-15) as the lower 4 bits of INDR
        uint32_t lower = *GPIO_D_INDR & 0xF;
        uint32_t value;

        // Check if any button in this row is pressed (low)

        if (lower != 15) {
            for (int i = 0; i < 4; i++) {
                if (!(lower & (1 << i))) { value = i + (row * 4); }
            }
        }
        //   and, if so, return the number of the button
        // Deactivate the current row by setting the corresponding pin high
        gpio_d_set_pin_high(row + 4);

        if (lower != 15) return value;
    }
    
    return -1; // No button pressed    return -1;  
}



