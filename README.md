# avr_experiments
Learning and testing out various AVR MCUs

Experiment 1:  The "blink" sketch, measuring power consumption by an ATtiny10.  Blink is 3 seconds on, 3 seconds off.  Measurement taken with an inline multimeter.  Since the MCU is powering a load (LED and resistor) I'm only taking the measurement when the load is off.

* blink_attiny10.c (Standard blink sketch, 1MHz default (8MHz prescaled by 1/8), no other optimizations): 493uA
* blink_attiny10_128k.c (128KHz internal clock, no other optimizations): 172uA
* blink_attiny10_sleep.c (128KHz internal clock, "SLEEP_MODE_PWR_DOWN" using watchdog timer instead of _delay_ms): 4uA
* blink_attiny10_sleep_opt.c (Clocked down as low as 8KHz, disabled analog comparator): 4uA

I've seen others report power consumption down into the hundreds of nanoamps with a low clock and ADC/ACD disabled.  I suspect that my Craftsman home/automotive multimeter is just at the end of its range.  (The smallest range is labelled '2000uA').  I will endeavor to find or borrow a better meter to continue these experiments.

Experiment 2:  The DC512 2023 shitty add-on.  This cool design has two bright red LEDs that shine through from the back of the board and give "eyes" to the graphic on the front of the board.  My goal here was to somehow shoehorn a micro into the positive trace to make the eyes have a random "blinking" effect.

I started with a compact LFSR-based PRNG I found on GitHub.  However, it produced 16-bit integers and was a bit overkill for my needs.  I ended up discarding the PRNG and precomputing 50 pairs of 4-bit values (one for the 'on' time and one for the 'blinking' time) that were suitable for feeding straight into the watchdog timer.  These are stored in a const uint8 array in the program.  Overall I saved 22 bytes vs. keeping the PRNG but the code is far less complicated and the micro spends less time awake breaking a uint8 into nybbles than it would doing exponents for a PRNG.  The pattern repeats every 50 blinks but that's probably somewhere around 5 minutes so I'm not too worried about it.

The badge in stock form consumes 11.5mA.  So for every second the LEDs are not lit, enough power is saved to run the micro for about 45 minutes!  (Waiting
for a PR with a math check.)