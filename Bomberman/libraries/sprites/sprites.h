// header file mainMenu
#ifndef SPRITES_h
#define SPRITES_h

// For the Adafruit shield, these are the default.
#define TFT_DC 9
#define TFT_CS 10


//Functions used by mainMenu

void spriteInit();

void spritePlayer(int posX, int posY);

void spriteAir(int posX, int posY);

void spriteWall(int posX, int posY);

void spriteBox(int posX,int posY);

void spriteBomb(int posX, int posY);

void spriteExplosion(int posX,int posY);

#endif