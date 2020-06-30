#ifndef __PDKUINO_H__
#define __PDKUINO_H__

#include "pdk/io.h"
#include "util.h"

void setup();
void loop();

void main() {
	setup();
	while(1) {
		loop();
	}
}

#endif /* __PDKUINO_H__ */
