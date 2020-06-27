#ifndef __i2c_master_h_included__
#define __i2c_master_h_included__

#if !defined(PIN_I2C_SCL)
	#define PIN_I2C_SCL         PA,6
#endif
#if !defined(PIN_I2C_SDA)
	#define PIN_I2C_SDA         PA,7
#endif
//#if !defined(I2C_FREQ_KHZ)
//	#define I2C_FREQ_KHZ			  100
//#endif

void i2c_master_start();
void i2c_master_stop();

void i2c_master_write_bit(bool bit);
bool i2c_master_read_bit();

bool i2c_master_write_byte(uint8_t byte);
uint8_t i2c_master_read_byte(bool nack);

#endif /* __i2c_master_h_included__ */
