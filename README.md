# avr_experiments
Learning and testing out various AVR MCUs

Experiment 1:  The "blink" sketch, measuring power consumption by an ATtiny10.  Blink is 3 seconds on, 3 seconds off.  Measurement taken with an inline multimeter.  Since the MCU is powering a load (LED and resistor) I'm only taking the measurement when the load is off.

* blink_attiny10.c (Standard blink sketch, 1MHz default (8MHz prescaled by 1/8), no other optimizations): 493uA
* blink_attiny10_128k.c (128KHz internal clock, no other optimizations): 172uA
* blink_attiny10_sleep.c (128KHz internal clock, "SLEEP_MODE_PWR_DOWN" using watchdog timer instead of _delay_ms): 4uA
* blink_attiny10_sleep_opt.c (Clocked down as low as 8KHz, disabled analog comparator): 4uA

I've seen others report power consumption down into the hundreds of nanoamps with a low clock and ADC/ACD disabled.  I suspect that my Craftsman home/automotive multimeter is just at the end of its range.  (The smallest range is labelled '2000uA').  I will endeavor to find or borrow a better meter to continue these experiments.

