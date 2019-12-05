// header file mainMenu
#ifndef MAINMENU_h
#define MAINMENU_h

// For the Adafruit shield, these are the default.
#define TFT_DC 9
#define TFT_CS 10

//Functions used by mainMenu
void init(int h);

void logoDisplay();

void menu();

void highlight(int size, int offsetY); 

void menuSetter(int currentHighlight);

//void highscore();

void loading();

void connecting();

#endif