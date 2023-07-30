#define F_CPU 1000000UL

#include <util/delay.h>
#include <avr/io.h>

int main() {
    DDRB |= _BV(DDB0); // set as output

    while (1) {
        PORTB &= ~_BV(PORTB0); // turn off
        _delay_ms(3000);

        PORTB |= _BV(PORTB0); // turn on
        _delay_ms(3000);
    }

    return 0;
}
