## Blink Example

![Action Shot](https://github.com/serisman/Padauk/raw/master/examples/blink/action%20shots/blink.gif)

This is the obligatory blink example that can be useful to prove that we know how to:
- Compile code
- Program the MCU
- Set and calibrate the operating frequency of the MCU
- Work with timer interrupts
- Work with digital inputs and outputs

### Assumptions:
- Tested to work with PFS173 and PFS154.  Probably will also work with other MCUs as the code is fairly generic.
- LEDs are connected between pins PA3, PA4, and PA6 on one side and VDD on the other side (i.e. MCU pins sink current through the LEDs).
- A Button is connected between pin PA5 and GND.

### Features:
- Uses hardware Timer16 to generate an interrupt every quarter second or so.
- LEDs 1 and 2 (PA3, PA4) will alternate every quarter second or so.
- LED 3 (PA6) will light up whenever the Button (PA5) is pressed.
- NOTE: If using the pictured PDK Dev Board, LED 4 (PA5) will also light up whenever the Button is pressed as they share a common MCU pin.

### Customization:
Edit the options at the top of the Makefile to:
- Pick a different MCU
- Use a different frequency for the system clock (switches between the high speed internal oscillator 'IHRC', and the low speed internal oscillator 'ILRC'). 

### Toolchain:
- Compiler: Requires [SDCC 3.9.0](http://sdcc.sourceforge.net/) (or newer)
- Programmer: Requires [easy-pdk-programmer-software](https://github.com/free-pdk/easy-pdk-programmer-software)
- Also requires 'make' and other common build tools

### Build Commands:
```
make clean
make all
make program
make run
```

### Build Stats
- Code Size: ~ 190 bytes / 95 words (+/- a few bytes/words depending on the specific device choosen)
- RAM usage: 1 byte + stack
