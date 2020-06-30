#include "pdk/hal.h"
#include "util.h"

#define PIN_LED1        PA,3
#define PIN_LED2        PA,4
#define PIN_LED3        PA,6

#define PIN_BTN         PA,5

// LEDs/Button are active low, so define helpers for better readability below
#define ledOn           clearPin
#define ledOff          setPin
#define isBtnPressed    isPinLow

volatile uint8_t quarter_seconds;

uint8_t prev_quarter_seconds;

// Main processing loop
inline void loop() {

	if (quarter_seconds != prev_quarter_seconds) {
	  // Alternate between the first two LEDs
	  if (quarter_seconds & 0b00000001) {
	    ledOff(PIN_LED2);
	    ledOn(PIN_LED1);
	  } else {
	    ledOff(PIN_LED1);
	    ledOn(PIN_LED2);
	  }
		prev_quarter_seconds = quarter_seconds;
	}

  // Light up the 3rd LED whenever the Button is pressed
	if (isBtnPressed(PIN_BTN)) {
	  ledOn(PIN_LED3);
	} else {
	  ledOff(PIN_LED3);
	}
}

// Setup/enable hardware
inline void setup() {
	// Set LEDs as outputs (all pins are input by default)
	setPinOutput(PIN_LED1);
	ledOff(PIN_LED1);
	setPinOutput(PIN_LED2);
	ledOff(PIN_LED2);
	setPinOutput(PIN_LED3);
	ledOff(PIN_LED3);

  // Set BTN as digital input with PullUp
  enableDigitalInput(PIN_BTN);
	setPinPullup(PIN_BTN);

	// Enable T16 timer to generate an interrupt every 1/4 seconds
	#if (F_CPU == 65536)
		T16M = 0b11010001;        // Use ILRC clock source (65.536 kHz), /16, Interrupt on (rising) Bit 9
	#elif (F_CPU == 524288)
		T16M = 0b00111010;        // Use System (IHRC) clock source (524.288 kHz), /64, Interrupt on (rising) Bit 10
	#endif
	T16C = 0;
	INTEN = INTEN_T16;

	// Enable interrupts
	INTRQ = 0;
	__engint();
}

void main() {
	setup();
	while(1) {
		loop();
	}
}

// Interrupt handler (kept as simple/minimalistic as possible)
//  - When T16 'ticks' - Increment our quarter_seconds 'register'
void interrupt(void) __interrupt(0) {
	if (INTRQ & INTRQ_T16) {
		quarter_seconds++;
		INTRQ &= ~INTRQ_T16;
	}
}

unsigned char _sdcc_external_startup(void) {
  // Calibrate IHRC or IRLC for values that work better for timekeeping.
  // Nowhere near accurate enough for actual timekeeping, but good enough for debugging (i.e. testing without a crystal).
  // For real timekeeping, use an external 32.768 kHz crystal as input to T16.
#if (F_CPU == 524288)
  EASY_PDK_INIT_SYSCLOCK_500KHZ();
  EASY_PDK_CALIBRATE_IHRC(524288, TARGET_VDD_MV);
#elif (F_CPU == 65536)
  EASY_PDK_INIT_SYSCLOCK_ILRC();
  EASY_PDK_CALIBRATE_ILRC(65536, TARGET_VDD_MV);
#else
# error "Unknown F_CPU"
#endif

  return 0;
}
