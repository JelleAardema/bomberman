// header file mainMenu
#ifndef SPRITES_h
#define SPRITES_h

// For the Adafruit shield, these are the default.
#define TFT_DC 9
#define TFT_CS 10


//Functions used by mainMenu

void spritePlayer(int posX, int posY, Adafruit_ILI9341 *tft);

void spriteAir(int posX, int posY, Adafruit_ILI9341 *tft);

void spriteWall(int posX, int posY, Adafruit_ILI9341 *tft);

void spriteBox(int posX,int posY, Adafruit_ILI9341 *tft);

void spriteBomb(int posX, int posY, Adafruit_ILI9341 *tft);

void spriteExplosion(int posX,int posY, Adafruit_ILI9341 *tft);

#endif