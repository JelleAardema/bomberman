#include <endScreen.h>
#include <Adafruit_ILI9341.h>
// For the Adafruit shield, these are the default.
#define TFT_DC 9
#define TFT_CS 10
Adafruit_ILI9341 screen = Adafruit_ILI9341(TFT_CS, TFT_DC);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  screen.begin();
  endScreenSetup(screen,1); 
}

void loop() {
  // put your main code here, to run repeatedly:
  endScreenInput();
  Serial.print("test");
}
