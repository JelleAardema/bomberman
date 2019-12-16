#include <Adafruit_GFX.h>         // Core graphics library
#include <Adafruit_ILI9341.h>     // Hardware-specific library
#include "sprites.h" 

// For the Adafruit shield, these are the default.
#define TFT_DC 9
#define TFT_CS 10

// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
// If using the breakout, change pins as desired
//Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

void spritePlayer(int posX, int posY, Adafruit_ILI9341 *tft){
  tft->fillRect(posX+10, posY+2, 4, 4,ILI9341_GREEN);
  //body
  tft->fillRect(posX+8, posY+6, 8, 6,ILI9341_BLUE);
  //left arm
  tft->drawLine(posX+9, posY+7, posX+9, posY+12, ILI9341_BLACK);
  //right arm
  tft->drawLine(posX+14, posY+7, posX+14, posY+12, ILI9341_BLACK);
  //legs
  tft->fillRect(posX+9, posY+12, 6, 8,ILI9341_MAROON);
  //Leg line
  tft->drawLine(posX+11, posY+14, posX+11, posY+20, ILI9341_BLACK);
}

void spriteAir(int posX, int posY, Adafruit_ILI9341 *tft){
  //floor tile
  tft->fillRect(posX, posY, 24, 24,ILI9341_WHITE);
  //outline
  tft->drawRect(posX, posY, 24, 24,ILI9341_BLACK);
  //section line up
  tft->drawLine(posX+12, posY, posX+12, posY+24, ILI9341_BLACK);
  //section line side
  tft->drawLine(posX, posY+12, posX+24, posY+12, ILI9341_BLACK);
  //center dot
  tft->fillCircle(posX+12, posY+12, 2, ILI9341_BLACK);
}

void spriteWall(int posX, int posY, Adafruit_ILI9341 *tft){
  //Wall tile
  tft->fillRect(posX, posY, 24, 24,ILI9341_BLUE);
  //outline
  tft->drawRect(posX, posY, 24, 24,ILI9341_BLACK);
  //Stones row 1
  tft->drawRect(posX, posY, 10, 5,ILI9341_BLACK);
  tft->drawRect(posX+10, posY, 10, 5,ILI9341_BLACK);
  tft->drawRect(posX+20, posY, 4, 5,ILI9341_BLACK);
  //Stones row 2
  tft->drawRect(posX, posY+5, 4, 5,ILI9341_BLACK);
  tft->drawRect(posX+4, posY+5, 10, 5,ILI9341_BLACK);
  tft->drawRect(posX+14, posY+5, 10, 5,ILI9341_BLACK);
  //Stones row 3
  tft->drawRect(posX, posY+10, 10, 5,ILI9341_BLACK);
  tft->drawRect(posX+10, posY+10, 10, 5,ILI9341_BLACK);
  tft->drawRect(posX+20, posY+10, 4, 5,ILI9341_BLACK);
  //Stones row 4
  tft->drawRect(posX, posY+15, 4, 5,ILI9341_BLACK);
  tft->drawRect(posX+4, posY+15, 10, 5,ILI9341_BLACK);
  tft->drawRect(posX+14, posY+15, 10, 5,ILI9341_BLACK);
  //Stones row 5
  tft->drawRect(posX, posY+20, 10, 4,ILI9341_BLACK);
  tft->drawRect(posX+10, posY+20, 10, 4,ILI9341_BLACK);
  tft->drawRect(posX+20, posY+20, 4, 4,ILI9341_BLACK);
}

void spriteBox(int posX,int posY, Adafruit_ILI9341 *tft){
    //floor tile
  tft->fillRect(posX, posY, 24, 24,ILI9341_MAROON);
  //outline
  tft->drawRect(posX, posY, 24, 24,ILI9341_BLACK);
  //section line up
  tft->drawLine(posX+12, posY, posX+12, posY+24, ILI9341_BLACK);
  //1
  tft->drawLine(posX+7, posY, posX+7, posY+24, ILI9341_BLACK);
  //2
  tft->drawLine(posX+17, posY, posX+17, posY+24, ILI9341_BLACK);
  //section line side
  //1
  tft->drawLine(posX, posY+7, posX+24, posY+7, ILI9341_BLACK);
  //2
  tft->drawLine(posX, posY+17, posX+24, posY+17, ILI9341_BLACK);
}

void spriteBomb(int posX, int posY, Adafruit_ILI9341 *tft){
  //bomb
   tft->fillCircle(posX+12, posY+12, 5, ILI9341_BLUE);
   //highlight
   tft->fillCircle(posX+14, posY+12, 2, ILI9341_CYAN);
   //fuse body
   tft->fillCircle(posX+12, posY+7, 2, ILI9341_CYAN);
   //fuse body indent
   tft->fillCircle(posX+12, posY+12, 2, ILI9341_BLUE);
   //fuse
   tft->drawLine(posX+12, posY+7, posX+12, posY, ILI9341_MAROON);
   
}

void sptireExplosion(int posX,int posY, Adafruit_ILI9341 *tft){

  ///UUUUUH IDK ABOUT THIS BOYS 
  tft->fillRect(posX, posY, 24, 24,ILI9341_RED);

  tft->fillCircle(random(posX, posX+24), random(posY, posY+24), 2, ILI9341_RED);
  tft->fillCircle(random(posX, posX+24), random(posY, posY+24), 2, ILI9341_YELLOW);
  tft->fillCircle(random(posX, posX+24), random(posY, posY+24), 2, ILI9341_BLACK);
  
  tft->fillCircle(random(posX, posX+24), random(posY, posY+24), 2, ILI9341_RED);
  tft->fillCircle(random(posX, posX+24), random(posY, posY+24), 2, ILI9341_YELLOW);
  tft->fillCircle(random(posX, posX+24), random(posY, posY+24), 2, ILI9341_BLACK);

  tft->fillCircle(random(posX, posX+20), random(posY, posY+24), 2, ILI9341_RED);
  tft->fillCircle(random(posX, posX+24), random(posY, posY+24), 2, ILI9341_YELLOW);
  tft->fillCircle(random(posX, posX+24), random(posY, posY+24), 2, ILI9341_BLACK);
  //pas 1
  tft->drawLine(random(posX, posX+24), random(posY, posY+24), random(posX, posX+24), random(posY, posY+24), ILI9341_BLACK);
  tft->drawLine(random(posX, posX+24), random(posY, posY+24), random(posX, posX+24), random(posY, posY+24), ILI9341_YELLOW);
  tft->drawLine(random(posX, posX+24), random(posY, posY+24), random(posX, posX+24), random(posY, posY+24), ILI9341_RED);
  //pas 2
  tft->drawLine(random(posX, posX+24), random(posY, posY+24), random(posX, posX+24), random(posY, posY+24), ILI9341_BLACK);
  tft->drawLine(random(posX, posX+24), random(posY, posY+24), random(posX, posX+24), random(posY, posY+24), ILI9341_YELLOW);
  tft->drawLine(random(posX, posX+24), random(posY, posY+24), random(posX, posX+24), random(posY, posY+24), ILI9341_RED);
  //pas 3
  tft->drawLine(random(posX, posX+24), random(posY, posY+24), random(posX, posX+24), random(posY, posY+24), ILI9341_BLACK);
  tft->drawLine(random(posX, posX+24), random(posY, posY+24), random(posX, posX+24), random(posY, posY+24), ILI9341_YELLOW);
  tft->drawLine(random(posX, posX+24), random(posY, posY+24), random(posX, posX+24), random(posY, posY+24), ILI9341_RED);
  //pas 4
  tft->drawLine(random(posX, posX+24), random(posY, posY+24), random(posX, posX+24), random(posY, posY+24), ILI9341_BLACK);
  tft->drawLine(random(posX, posX+24), random(posY, posY+24), random(posX, posX+24), random(posY, posY+24), ILI9341_YELLOW);
  tft->drawLine(random(posX, posX+24), random(posY, posY+24), random(posX, posX+24), random(posY, posY+24), ILI9341_RED);
  //pas 5
  tft->drawLine(random(posX, posX+24), random(posY, posY+24), random(posX, posX+24), random(posY, posY+24), ILI9341_BLACK);
  tft->drawLine(random(posX, posX+24), random(posY, posY+24), random(posX, posX+24), random(posY, posY+24), ILI9341_YELLOW);
  tft->drawLine(random(posX, posX+24), random(posY, posY+24), random(posX, posX+24), random(posY, posY+24), ILI9341_RED);
  //pas 6
  tft->drawLine(random(posX, posX+24), random(posY, posY+24), random(posX, posX+24), random(posY, posY+24), ILI9341_BLACK);
  tft->drawLine(random(posX, posX+24), random(posY, posY+24), random(posX, posX+24), random(posY, posY+24), ILI9341_YELLOW);
  tft->drawLine(random(posX, posX+24), random(posY, posY+24), random(posX, posX+24), random(posY, posY+24), ILI9341_RED);
}
