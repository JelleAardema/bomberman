// header file mainMenu
#ifndef ENDSCREEN_h
#define ENDSCREEN_h

// For the Adafruit shield, these are the default.
#define TFT_DC 9
#define TFT_CS 10


void endScreenSetup(Adafruit_ILI9341 *pen, int winState);

void endScreenInput();

void endScreenDisplay(int win);

#endif