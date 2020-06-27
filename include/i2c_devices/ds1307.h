#ifndef __ds1307_h_included__
#define __ds1307_h_included__

#include "i2c_master.h"
#include "util.h"

#define DS1307_I2C_ADDRESS    0b11010000

inline void ds1307_set_address(uint8_t addr) {
  i2c_master_start();
  i2c_master_write_byte(DS1307_I2C_ADDRESS);
  i2c_master_write_byte(addr);
}

inline bool ds1307_write(uint8_t data) {
	return i2c_master_write_byte(data);
}

inline void ds1307_start_read() {
	i2c_master_start();
	i2c_master_write_byte(DS1307_I2C_ADDRESS | BV(0));
}

inline uint8_t ds1307_read(bool done) {
	return i2c_master_read_byte(done);
}

inline void ds1307_stop() {
	i2c_master_stop();
}

#endif /* __ds1307_h_included__ */
