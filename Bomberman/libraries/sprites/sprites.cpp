#include <Adafruit_GFX.h>         // Core graphics library
#include <Adafruit_ILI9341.h>     // Hardware-specific library
#include "sprites.h" 

// For the Adafruit shield, these are the default.
#define TFT_DC 9
#define TFT_CS 10

// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
// If using the breakout, change pins as desired
//Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

void spriteInit() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("ILI9341 Test!"); 
 
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(ILI9341_BLACK);
}

void player(int posX, int posY){
  tft.fillRect(posX+8, posY, 4, 4,ILI9341_GREEN);
  //body
  tft.fillRect(posX+6, posY+4, 8, 6,ILI9341_BLUE);
  //left arm
  tft.drawLine(posX+7, posY+5, posX+7, posY+10, ILI9341_BLACK);
  //right arm
  tft.drawLine(posX+12, posY+5, posX+12, posY+10, ILI9341_BLACK);
  //legs
  tft.fillRect(posX+7, posY+10, 6, 8,ILI9341_MAROON);
  //Leg line
  tft.drawLine(posX+9, posY+12, posX+9, posY+18, ILI9341_BLACK);
}

void tile(int posX, int posY){
  //floor tile
  tft.fillRect(posX, posY, 20, 20,ILI9341_WHITE);
  //outline
  tft.drawRect(posX, posY, 20, 20,ILI9341_BLACK);
  //section line up
  tft.drawLine(posX+10, posY, posX+10, posY+20, ILI9341_BLACK);
  //section line side
  tft.drawLine(posX, posY+10, posX+20, posY+10, ILI9341_BLACK);
  //center dot
  tft.fillCircle(posX+10, posY+10, 2, ILI9341_BLACK);
}

void box(int posX,int posY){
    //floor tile
  tft.fillRect(posX, posY, 20, 20,ILI9341_MAROON);
  //outline
  tft.drawRect(posX, posY, 20, 20,ILI9341_BLACK);
  //section line up
  tft.drawLine(posX+10, posY, posX+10, posY+20, ILI9341_BLACK);
  //1
  tft.drawLine(posX+5, posY, posX+5, posY+20, ILI9341_BLACK);
  //2
  tft.drawLine(posX+15, posY, posX+15, posY+20, ILI9341_BLACK);
  //section line side
  //1
  tft.drawLine(posX, posY+5, posX+20, posY+5, ILI9341_BLACK);
  //2
  tft.drawLine(posX, posY+15, posX+20, posY+15, ILI9341_BLACK);
}

void bomb(int posX, int posY){
  //bomb
   tft.fillCircle(posX+10, posY+10, 5, ILI9341_BLUE);
   //highlight
   tft.fillCircle(posX+12, posY+10, 2, ILI9341_CYAN);
   //fuse body
   tft.fillCircle(posX+10, posY+5, 2, ILI9341_CYAN);
   //fuse body indent
   tft.fillCircle(posX+10, posY+10, 2, ILI9341_BLUE);
   //fuse
   tft.drawLine(posX+10, posY+5, posX+10, posY, ILI9341_MAROON);
   
}

void explosion(int posX,int posY){

  ///UUUUUH IDK ABOUT THIS BOYS 
  tft.fillRect(posX, posY, 20, 20,ILI9341_RED);

  tft.fillCircle(random(posX, posX+20), random(posY, posY+20), 2, ILI9341_RED);
  tft.fillCircle(random(posX, posX+20), random(posY, posY+20), 2, ILI9341_YELLOW);
  tft.fillCircle(random(posX, posX+20), random(posY, posY+20), 2, ILI9341_BLACK);
  
  tft.fillCircle(random(posX, posX+20), random(posY, posY+20), 2, ILI9341_RED);
  tft.fillCircle(random(posX, posX+20), random(posY, posY+20), 2, ILI9341_YELLOW);
  tft.fillCircle(random(posX, posX+20), random(posY, posY+20), 2, ILI9341_BLACK);

  tft.fillCircle(random(posX, posX+20), random(posY, posY+20), 2, ILI9341_RED);
  tft.fillCircle(random(posX, posX+20), random(posY, posY+20), 2, ILI9341_YELLOW);
  tft.fillCircle(random(posX, posX+20), random(posY, posY+20), 2, ILI9341_BLACK);
  //pas 1
  tft.drawLine(random(posX, posX+20), random(posY, posY+20), random(posX, posX+20), random(posY, posY+20), ILI9341_BLACK);
  tft.drawLine(random(posX, posX+20), random(posY, posY+20), random(posX, posX+20), random(posY, posY+20), ILI9341_YELLOW);
  tft.drawLine(random(posX, posX+20), random(posY, posY+20), random(posX, posX+20), random(posY, posY+20), ILI9341_RED);
  //pas 2
  tft.drawLine(random(posX, posX+20), random(posY, posY+20), random(posX, posX+20), random(posY, posY+20), ILI9341_BLACK);
  tft.drawLine(random(posX, posX+20), random(posY, posY+20), random(posX, posX+20), random(posY, posY+20), ILI9341_YELLOW);
  tft.drawLine(random(posX, posX+20), random(posY, posY+20), random(posX, posX+20), random(posY, posY+20), ILI9341_RED);
  //pas 3
  tft.drawLine(random(posX, posX+20), random(posY, posY+20), random(posX, posX+20), random(posY, posY+20), ILI9341_BLACK);
  tft.drawLine(random(posX, posX+20), random(posY, posY+20), random(posX, posX+20), random(posY, posY+20), ILI9341_YELLOW);
  tft.drawLine(random(posX, posX+20), random(posY, posY+20), random(posX, posX+20), random(posY, posY+20), ILI9341_RED);
  //pas 4
  tft.drawLine(random(posX, posX+20), random(posY, posY+20), random(posX, posX+20), random(posY, posY+20), ILI9341_BLACK);
  tft.drawLine(random(posX, posX+20), random(posY, posY+20), random(posX, posX+20), random(posY, posY+20), ILI9341_YELLOW);
  tft.drawLine(random(posX, posX+20), random(posY, posY+20), random(posX, posX+20), random(posY, posY+20), ILI9341_RED);
  //pas 5
  tft.drawLine(random(posX, posX+20), random(posY, posY+20), random(posX, posX+20), random(posY, posY+20), ILI9341_BLACK);
  tft.drawLine(random(posX, posX+20), random(posY, posY+20), random(posX, posX+20), random(posY, posY+20), ILI9341_YELLOW);
  tft.drawLine(random(posX, posX+20), random(posY, posY+20), random(posX, posX+20), random(posY, posY+20), ILI9341_RED);
  //pas 6
  tft.drawLine(random(posX, posX+20), random(posY, posY+20), random(posX, posX+20), random(posY, posY+20), ILI9341_BLACK);
  tft.drawLine(random(posX, posX+20), random(posY, posY+20), random(posX, posX+20), random(posY, posY+20), ILI9341_YELLOW);
  tft.drawLine(random(posX, posX+20), random(posY, posY+20), random(posX, posX+20), random(posY, posY+20), ILI9341_RED);
}
