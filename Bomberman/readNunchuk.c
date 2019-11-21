#include <Wire.h>
#include <nunchuk.h>

void setupNunchuk() {
  nunchuk_init();
}

int getInput() {
    // check if there's any data to read.
    if (nunchuk_read()) {
      
       // deadzones of 20, so you're not moving when you're not using the stick.
       if(nunchuk_joystickX() > 20) {
           return 1;
       }

       else if(nunchuk_joystickY() > 20) {
           return 2;
       }

       else if(nunchuk_joystickY() < -20) {
           return 3;
       }

       else if(nunchuk_joystickX() < -20) {
           return 4;
       }

       // Z button
       if(nunchuk_buttonZ() == 1) {
           return 5;
       }

       // C button
       if(nunchuk_buttonC() == 1) {
           return 6;
       }
       
    }
}
