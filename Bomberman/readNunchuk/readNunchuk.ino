#include <Wire.h>
#include "nunchuk.h"

void setup() {
    Serial.begin(9600);
    Wire.begin();
    // nunchuk_init_power(); // A1 and A2 is power supply
    nunchuk_init();

    /*
     * nunchuk_buttonZ(); 0 of 1
     * nunchuk_buttonC(); 0 of 1
     * nunchuk_joystickX(); -126 tot 127
     * nunchuk_joystickY(); -128 tot 126
     */
}

void loop() {
    // check if there's any data to read.
    if (nunchuk_read()) {
      
       // deadzones of 20, so you're not moving when you're not using the stick.
       if(nunchuk_joystickX() > 20) {
          Serial.println("rechts");
       }

       else if(nunchuk_joystickY() > 20) {
          Serial.println("omhoog");
       }

       else if(nunchuk_joystickY() < -20) {
          Serial.println("beneden");
       }

       else if(nunchuk_joystickX() < -20) {
          Serial.println("links");
       }

       // Z button
       if(nunchuk_buttonZ() == 1) {
          Serial.println("Z ingedrukt");
       }

       // C button
       if(nunchuk_buttonC() == 1) {
          Serial.println("C ingedrukt");
       }
       
    }
    delay(10);
}
