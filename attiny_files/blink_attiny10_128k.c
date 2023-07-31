#define F_CPU 128000UL

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

int main() {

    DDRB |= _BV(DDB0); // set as output

    cli();
    
    CCP = 0xD8; //unlock config change protection register
    CLKMSR = (0<<CLKMS1) | (1<<CLKMS0); // set clock to 128kHz
    CCP = 0xD8;
    CLKPSR = 0; // set clock divider to 1 (run at clock rate)
    
    sei();

    while (1) {
        PORTB |= _BV(PORTB0); // turn on
        _delay_ms(3000);

        PORTB &= ~_BV(PORTB0); // turn off
        _delay_ms(3000);
    }

    return 0;
}
