#define F_CPU 128000UL

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <avr/sleep.h>

/* Function prototypes */
void wdt_delay (int);

/* main */
int main() {

    DDRB |= _BV(DDB0); // set as output

    cli();  // disable interupts while writing register values
    
    CCP = 0xD8; // unlock config change protection register
    CLKMSR = (0<<CLKMS1) | (1<<CLKMS0); // set clock to 128kHz
    CCP = 0xD8;
    CLKPSR = 0; // set clock divider to 1 (run at clock rate)
    
    RSTFLR &= ~(1<<WDRF);  // clear existing watchdog interrupt
    
    sei(); // enable interrupts

    while (1) {
        PORTB |= _BV(PORTB0); // turn on
        wdt_delay(7); // sleep for 2 seconds
        wdt_delay(6); // sleep for 1 second

        PORTB &= ~_BV(PORTB0); // turn off
        wdt_delay(7); // sleep for 2 seconds
        wdt_delay(6); // sleep for 1 second
    }

    return 0;
}

/* watchdog delay function */
void wdt_delay (int n) {
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);  // sets deepest sleep mode
    WDTCSR = 1<<WDIE | (n & 0x8)<<2 | (n & 0x7); // enables watchdog timer
    sleep_enable();  // enables sleep
    sleep_cpu(); // begins sleep
}

/* watchdog interrupt vector */
ISR(WDT_vect) {
  WDTCSR = 0<<WDIE; // disables watchdog timer
}