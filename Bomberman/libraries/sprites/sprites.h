// header file mainMenu
#ifndef SPRITES_h
#define SPRITES_h

// For the Adafruit shield, these are the default.
#define TFT_DC 9
#define TFT_CS 10


//Functions used by mainMenu

void spriteInit();

void player(int posX, int posY);

void tile(int posX, int posY);

void box(int posX,int posY);

void bomb(int posX, int posY);

void explosion(int posX,int posY);

#endif