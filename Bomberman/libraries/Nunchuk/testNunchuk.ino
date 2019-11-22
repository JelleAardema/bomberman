#include <avr/io.h>
#include <util/delay.h>
#include <Arduino.h>
#include <Wire.h>
#include "nunchuk.h"

void setup() {
  init();

  // use Serial for printing nunchuk data
  Serial.begin(9600);

  // join I2C bus as master
  Wire.begin();

  // handshake with nunchuk
  Nunchuk.begin(0x52);
}

void loop() {
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

    _delay_ms(500);
}
