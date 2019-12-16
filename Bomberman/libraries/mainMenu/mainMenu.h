// header file mainMenu
#ifndef MAINMENU_h
#define MAINMENU_h

// For the Adafruit shield, these are the default.
#define TFT_DC 9
#define TFT_CS 10

//Functions used by mainMenu
void mainMenuSetup(Adafruit_ILI9341 *pen);

void logoDisplay();

void menu(int host);

void highlight(int size, int offsetY); 

void menuSetter(int currentHighlight);

void highscore(int size, int offsetY);
 
void loading();

void connecting();

void getLevel(int* seed, int* type);

#endif