## Blink Example

This is the obligatory blink example that can be useful to prove that we know how to program the MCU,
and work with digital inputs and outputs.

### Assumptions:
- LEDs are connected between pins PA3, PA4, and PA6 on one side and VDD on the other side (i.e. MCU pins sink current through the LEDs)
- Button is connected between pin PA5 and GND

### Features:
- Uses hardware Timer16 to generate an interrupt every quarter second or so.
- LEDs 1 and 2 (PA3, PA4) will alternate every quarter second or so.
- LED 3 (PA6) will light up whenever the Button (PA5) is pressed.
- (if populated) LED 4 (PA5) will also light up whenever the Button is pressed as they share a common MCU pin.

### Action Shot:
![Action Shot](https://github.com/serisman/Padauk/raw/master/examples/blink/action%20shots/blink.gif)

### Toolchain:
- Requires [SDCC 3.9.0](http://sdcc.sourceforge.net/) (or newer)
- Requires [easy-pdk-programmer-software](https://github.com/free-pdk/easy-pdk-programmer-software)

### Customization:
Edit the options at the top of the Makefile to pick a different MCU, or use a different frequency for sysclock. 

### Build Commands:
```
make clean
make all
make program
make run
```
