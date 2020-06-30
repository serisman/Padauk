#include "pdk/io.h"
#include "util.h"
#include "i2c_master.h"

bool started;
uint8_t _tmp1, _tmp2;

// 3 cycles per loop, 4 cycles overhead
//#define HALF_DELAY_CTR    ((((1000/(2*I2C_FREQ_KHZ))*(F_CPU/1000000))-4)/3)

// TODO: re-implement this in a better (faster) way.  It is slowing transmission more than it should.
inline void i2c_master_half_delay() {
	// 2 cycles for the call
//__asm
// 	mov a, #(HALF_DELAY_CTR)    ;// 1 cycle
//00001$:                       ;// each loop is 3 cycles
// 	;sub a, #1
// 	;t1sn f,z
// 	dzsn  a
// 		goto 00001$
//__endasm;
	// 2 cycles for the ret, but -1 for the final dzsn
}

void i2c_master_start() {
  if (started) {
    setPinInput(PIN_I2C_SDA);
    i2c_master_half_delay();

    setPinInput(PIN_I2C_SCL);
    while (isPinLow(PIN_I2C_SCL)) {
      ; // add timeout?
    }
    i2c_master_half_delay();
  }

	setPinInput(PIN_I2C_SDA);
//	if (isPinLow(PIN_I2C_SDA)) {
//		; // Arbitration lost!
//	}

  setPinOutput(PIN_I2C_SDA);
  clearPin(PIN_I2C_SDA);
  i2c_master_half_delay();

  setPinOutput(PIN_I2C_SCL);
  clearPin(PIN_I2C_SCL);

  started = true;
}

void i2c_master_stop() {
  setPinOutput(PIN_I2C_SDA);
  clearPin(PIN_I2C_SDA);
  i2c_master_half_delay();

  setPinInput(PIN_I2C_SCL);
  while (isPinLow(PIN_I2C_SCL)) {
    ; // add timeout?
  }
  i2c_master_half_delay();

  setPinInput(PIN_I2C_SDA);
  i2c_master_half_delay();
//	if (isPinLow(PIN_I2C_SDA)) {
//		; // Arbitration lost!
//	}

  started = false;
}

void i2c_master_write_bit(bool bit) {
//  if (bit) {
//    setPinInput(PIN_I2C_SDA);
//  } else {
//    setPinOutput(PIN_I2C_SDA);
//    //clearPin(PIN_I2C_SDA);
//  }
//  i2c_master_half_delay();
//
//  setPinInput(PIN_I2C_SCL);
//  while (isPinLow(PIN_I2C_SCL)) {
//    ; // add timeout?
//  }
//  i2c_master_half_delay();
//
////	if (bit && isPinLow(PIN_I2C_SDA)) {
////		; // Arbitration lost!
////	}
//
//  setPinOutput(PIN_I2C_SCL);
//  //clearPin(PIN_I2C_SCL);
	bit; // Ignore unreferenced function argument warning
__asm
	//t0sn  _i2c_master_write_bit_PARM_1, #0
		set0  _REG_CTRL(PIN_I2C_SDA), #_BIT(PIN_I2C_SDA)
	t1sn  _i2c_master_write_bit_PARM_1, #0
		set1  _REG_CTRL(PIN_I2C_SDA), #_BIT(PIN_I2C_SDA)
	;// TODO... half delay needed?
	set0  _REG_CTRL(PIN_I2C_SCL), #_BIT(PIN_I2C_SCL)
00001$:
  t1sn  _REG(PIN_I2C_SCL), #_BIT(PIN_I2C_SCL)
    goto  00001$
	;// TODO... half delay needed?
	set1	_REG_CTRL(PIN_I2C_SCL), #_BIT(PIN_I2C_SCL)
__endasm;
}

bool i2c_master_read_bit() __naked {
//  bool bit;
//
//  setPinInput(PIN_I2C_SDA);
//  i2c_master_half_delay();
//
//  setPinInput(PIN_I2C_SCL);
//  while (isPinLow(PIN_I2C_SCL)) {
//    ; // add timeout?
//  }
//  i2c_master_half_delay();
//  bit = (isPinHigh(PIN_I2C_SDA));
//
//  setPinOutput(PIN_I2C_SCL);
//  //clearPin(PIN_I2C_SCL);
//
//  return bit;
__asm
	set0	_REG_CTRL(PIN_I2C_SDA), #_BIT(PIN_I2C_SDA)
	;// TODO... half delay needed?
	set0	_REG_CTRL(PIN_I2C_SCL), #_BIT(PIN_I2C_SCL)
00001$:
	t1sn  _REG(PIN_I2C_SCL), #_BIT(PIN_I2C_SCL)
		goto  00001$
	;// TODO... half delay needed?
	mov   a, #0
	t0sn  _REG(PIN_I2C_SDA), #_BIT(PIN_I2C_SDA)
		mov   a, #1
	set1	_REG_CTRL(PIN_I2C_SCL), #_BIT(PIN_I2C_SCL)
	ret
__endasm;
}

bool i2c_master_write_byte(uint8_t byte) __naked {
//  bool nack;
//	uint8_t ctr=8;
//	do {
//    i2c_master_write_bit(isBitSet(byte,7));
//    byte <<= 1;
//  } while (--ctr);
//  nack = i2c_master_read_bit();
//  return nack;
	byte; // Ignore unreferenced function argument warning
__asm
	mov   a, #8
	mov   __tmp1, a
00001$:
	clear _i2c_master_write_bit_PARM_1
	sl	  _i2c_master_write_byte_PARM_1
	t0sn  f, c
		set1  _i2c_master_write_bit_PARM_1, #0
	call	_i2c_master_write_bit
	dzsn  __tmp1
		goto  00001$
	call	_i2c_master_read_bit
	ret
__endasm;
}

uint8_t i2c_master_read_byte(bool nack) __naked {
//  uint8_t byte = 0;
//	uint8_t ctr=8;
//	do {
//    byte <<= 1;
//    byte |= i2c_master_read_bit();
//  } while (--ctr);
//  i2c_master_write_bit(nack);
//  return byte;
	nack; // Ignore unreferenced function argument warning
__asm
	mov   a, #8
 	mov   __tmp1, a
 	clear __tmp2
00001$:
	sl    __tmp2
	call	_i2c_master_read_bit
	ceqsn	a, #0x00
		set1  __tmp2, #0
	dzsn  __tmp1
		goto  00001$
	mov	  a, _i2c_master_read_byte_PARM_1
	mov	  _i2c_master_write_bit_PARM_1, a
	call	_i2c_master_write_bit
	mov   a, __tmp2
	ret
__endasm;
}
