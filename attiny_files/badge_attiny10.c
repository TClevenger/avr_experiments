#define F_CPU 128000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <avr/sleep.h>

/* Function prototypes */
void wdt_delay(uint8_t);

/* const declarations */
const uint8_t rando[50] = {
        132, 149, 117, 133, 116,
        148, 133, 149, 133, 117,
        132, 133, 149, 132, 148,
        117, 148, 132, 133, 116,
        148, 116, 116, 148, 133,
        148, 149, 117, 148, 132,
        133, 116, 132, 132, 149,
        117, 132, 132, 149, 148,
        116, 132, 132, 149, 132,
        117, 117, 116, 132, 149}; // "random" number array

int main()
{

    uint8_t index = 0; // index into array
    
    DDRB |= _BV(DDB0); // set as output

    cli(); // disable interupts while writing register values

    CCP = 0xD8;                             // unlock config change protection register
    CLKMSR = (0 << CLKMS1) | (1 << CLKMS0); // set clock to 128kHz
    CCP = 0xD8;
    CLKPSR = 0; // set clock divider to 1 (run at full clock speed)

    RSTFLR &= ~(1 << WDRF); // clear existing watchdog interrupt

    ACSR = (1 << ACD); // disable analog comparator for power savings
    VLMCSR = 0;        // disable voltage level monitor

    sei(); // enable interrupts

    while (1)
    {
        PORTB |= _BV(PORTB0); // turn on
        wdt_delay((rando[index]) >> 4); // send watchdog top 4 bits

        PORTB &= ~_BV(PORTB0); // turn off
        wdt_delay((rando[index]) & 0x0F); // send watchdog bottom 4 bits

        index += 1;
        if (index == 50)
            index = 0; // back to top of array
    }

    return 0;
}

/* watchdog delay function */
void wdt_delay(uint8_t n)
{
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);             // sets deepest sleep mode
    WDTCSR = 1 << WDIE | (n & 0x8) << 2 | (n & 0x7); // enables watchdog timer
    sleep_enable();                                  // enables sleep
    sleep_cpu();                                     // begins sleep
}

/* watchdog interrupt vector */
ISR(WDT_vect)
{
    WDTCSR = 0 << WDIE; // disables watchdog timer
}