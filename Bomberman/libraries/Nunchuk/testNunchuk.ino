#include <avr/io.h>
#include <util/delay.h>
#include <Arduino.h>
#include <Wire.h>
#include "nunchuk.h"

int getDirection();


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
  Nunchuk.getState(0x52);
    Serial.print("direction: ");
    Serial.println(getDirection());

    Serial.print("Button C: ");
    Serial.print(Nunchuk.state.c_button);
    Serial.print(" Button Z: ");
    Serial.println(Nunchuk.state.z_button);

    _delay_ms(500);
}

int getDirection() {

  if(Nunchuk.state.joy_y_axis > 148) {
     return 1;
  }
  
  else if(Nunchuk.state.joy_x_axis > 148) {
    return 2;
  }

  else if (Nunchuk.state.joy_y_axis < 108) {
    return 3;
  }

  else if(Nunchuk.state.joy_x_axis < 108) {
    return 4;
  }

  else {
    return 0;
  }
}
