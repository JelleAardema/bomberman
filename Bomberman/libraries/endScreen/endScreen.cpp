#include <Wire.h>
#include <Nunchuk.h>
#include <Adafruit_ILI9341.h>
#include <highscore.h>
#include "endScreen.h"


int z_buttonState,
    mainMenuFlag;

int getDirection();

                
// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
//Adafruit_ILI9341 screen = Adafruit_ILI9341(TFT_CS, TFT_DC);
// If using the breakout, change pins as desired
//Adafruit_ILI9341 screen = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);
Adafruit_ILI9341 *pScreen;


void endScreenSetup(Adafruit_ILI9341 *pen, int winState) {
  pScreen = pen;

  //Setting up display orientation and clearing
  pen->fillScreen(ILI9341_BLACK);
  pen->setRotation(1);
  
  //Display logo and wait for user input
  endScreenDisplay(winState);
}


void endScreenInput() {
  while(!mainMenuFlag){
  //Waiting for user input to setup initial connection over IR
  Nunchuk.getState(0x52);

  if(Nunchuk.state.z_button == 1 && z_buttonState != 1){
    z_buttonState = 1;
    mainMenuFlag = 1;
  }

  if(Nunchuk.state.z_button == 0){
    z_buttonState = 0;
  }
 }
}



//Function to display bomberman logo
void endScreenDisplay(int win){
  pScreen->setCursor(25,50);
  pScreen->setTextColor(ILI9341_WHITE);
  pScreen->setTextSize(5); 
  pScreen->println("YOU");
  pScreen->setCursor(50,50);
  
  if(win){
    pScreen->println("WIN");
  }
  else{
    pScreen->println("LOSE");
  }
  
  pScreen->setCursor(25,75);
  pScreen->println(getCurrentScore());
  pScreen->setCursor(60,150);
  pScreen->setTextColor(ILI9341_WHITE);
  pScreen->setTextSize(2);
  pScreen->println("press Z to return to main menu");
} 

