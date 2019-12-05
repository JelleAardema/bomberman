/*
 * read data from nunchuk and write to Serial
 */
#include <avr/io.h>
#include <util/delay.h>
#include <Arduino.h>
#include <Wire.h>
#include "Nunchuk.h"

#define NUNCHUK_ADDRESS 0x52
#define WAIT	500
#define BAUDRATE 9600

int main(void) {
	// arduino init
	init();

	// use Serial for printing nunchuk data
	Serial.begin(BAUDRATE);

	// join I2C bus as master
	Wire.begin();

	// handshake with nunchuk
	Nunchuk.begin(NUNCHUK_ADDRESS);

	/*
	 * get identificaton (nunchuk should be 0xA4200000)
	 */
	Serial.print("Id: 0x");
	for (uint8_t i = 0; i < FRAMELEN; i++) {
		Serial.print(Nunchuk.id[i], HEX);
	}
	Serial.println("");

	_delay_ms(WAIT);

	// endless loop
	while(1) {
		Nunchuk.getState(NUNCHUK_ADDRESS);
		Serial.print("Joy X: ");
		Serial.print(Nunchuk.state.joy_x_axis, HEX);
		Serial.print(" Joy Y: ");
		Serial.println(Nunchuk.state.joy_y_axis, HEX);
		Serial.print("Accel X: ");
		Serial.print(Nunchuk.state.accel_x_axis, HEX);
		Serial.print(" Accel Y: ");
		Serial.print(Nunchuk.state.accel_y_axis, HEX);
		Serial.print(" Accel Z: ");
		Serial.println(Nunchuk.state.accel_z_axis, HEX);
		Serial.print("Button C: ");
		Serial.print(Nunchuk.state.c_button, HEX);
		Serial.print(" Button Z: ");
		Serial.println(Nunchuk.state.z_button, HEX);

		_delay_ms(WAIT);
	}

	return(0);
}
