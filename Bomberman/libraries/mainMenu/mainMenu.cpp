#include <Wire.h>
#include <Nunchuk.h>
#include <Adafruit_ILI9341.h>
#include <connection.h>
#include <highscore.h>
#include "mainMenu.h"


int started,
    pos,
    i,
    xCoord,
    yCoord,
    currentDirection,
    currentPage,
    z_buttonState,
    size,
    offsetY,
    host,
    startGameFlag;

int getDirection();

char itemsMain[2][10] = {
                         "play",
                         "highscore"
                     };

char itemsPlay[1][10] = {
                         "Start"
                     };

char itemsLevel[6][10] = {
                         "level - 1",
                         "level - 2",
                         "level - 3",
                         "level - 4",
                         "level - 5",
                         "Generate"
                     };                     

char itemsHighscore[5][10] = {
                         1,
                         2,
                         3,
                         4,
                         5
                     };

// Pointer initialization
char (*ptrArray)[10];
char (*prevPtrArray)[10];
                
// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
// If using the breakout, change pins as desired
//Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);


void init(int h) {
  host = h;
  Serial.begin(9600);
  Wire.begin();
  Nunchuk.begin(0x52); 
  tft.begin();
  irccBegin(host);

  //Setting pointer on first menu page
  ptrArray = itemsMain;

  //Setting text size and array item count
  size = 5;
  offsetY = 75;
  currentPage = 2;
 
  //Setting up display orientation and clearing
  tft.fillScreen(ILI9341_BLACK);
  tft.setRotation(1);
  // Setup loop here 
  logoDisplay();
}


void menu(void) {
  while(!startGameFlag){
  //Showing the start screen and setting up the initial connection over IR
  Nunchuk.getState(0x52);
   if (Nunchuk.state.z_button == 1 && started == 0 && z_buttonState != 1){
    z_buttonState = 1;
    started = 1;
  
    //Starting connection with other arduino
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    connecting();
    //startConnection(host);
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    tft.fillScreen(ILI9341_BLACK);
    highlight(size,offsetY);     
   }

   //Main navigation loop
  if(started == 1){
    if(getDirection() == 3 && currentDirection != 3){
         i++;
         currentDirection = getDirection();
         if(i > currentPage -1){
          i = currentPage -1;
         }
         highlight(size,offsetY);
    }


    if(getDirection() == 1 && currentDirection != 1){
        i--;
        currentDirection = getDirection();
      if(i < 0){
          i = 0;
       }
       highlight(size,offsetY);
    }
  }

  if(Nunchuk.state.z_button == 1 && z_buttonState != 1){
    z_buttonState = 1;
    menuSetter(i);
  }

  if(Nunchuk.state.c_button == 1){
    ptrArray = itemsMain;
    tft.fillScreen(ILI9341_BLACK);
    currentPage = 2;
    size = 5;
    offsetY = 75;
    highlight(size,offsetY);
  }

  if(Nunchuk.state.joy_y_axis == 128){
    currentDirection = 0;
  }

  if(Nunchuk.state.z_button == 0){
    z_buttonState = 0;
  }
 }
  loading();
}



//Function to display bomberman logo
void logoDisplay(){
  tft.setCursor(25,50);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(5); 
  tft.println("BOMBERMAN");
  tft.setCursor(60,150);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.println("press Z to start");
} 



//Drawing the menu items and highlighting the selected items
void highlight(int size, int offsetY){  
  //Set text style
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(size); 
  xCoord = 25;
  yCoord = 25;
  for(int j = 0; j < currentPage; j++){
    //Serial.println(currentPage);
    tft.setCursor(xCoord,yCoord);
    for(int k = 0; k < 10; k++){
      if(j == i){
        tft.setTextColor(ILI9341_YELLOW);    
      }
      tft.setCursor(xCoord,yCoord);
      tft.println(ptrArray[j][k]);
      xCoord = xCoord + 30;  
    }
    tft.setTextColor(ILI9341_WHITE); 
    xCoord = 25;
    yCoord += offsetY;   
  }
}


//Fucntion to select the coresponding menu page and binding behavior on menu items
void menuSetter(int currentHighlight){
    tft.fillScreen(ILI9341_BLACK);
    
    //Main menu 
    if(ptrArray == itemsMain){
      switch (currentHighlight){
        case 0 : 
          ptrArray = itemsPlay;  
          currentPage = 1;
          size = 5;
          offsetY = 75;
          break;
        case 1 :
          updateHighscoreList();
          Serial.println(highscores[0]);
          Serial.println(highscores[1]);
          Serial.println(highscores[2]);
          Serial.println(highscores[3]);
          Serial.println(highscores[4]);
          ptrArray = itemsHighscore;  
          currentPage = 5;
          size = 3;
          offsetY = 75;
          break;
        }    
    }
    
    //Play menu 
    else if(ptrArray == itemsPlay){
      switch (currentHighlight){
        case 0 : 
          ptrArray =  itemsLevel;  
          currentPage = 6;
          size = 2;
          offsetY = 30;
          break;
        }    
    }

    //Level select
    else if(ptrArray == itemsLevel){
      switch (currentHighlight){
        case 0 :   
          sendLevel(1,1);
          startGameFlag = 1;
          break;
        case 1 :  
          sendLevel(2,1);
          startGameFlag = 1;
          break;
        case 2 :  
          sendLevel(3,1);
          startGameFlag = 1;
          break;
        case 3 :  
          sendLevel(4,1);
          startGameFlag = 1;
          break;
        case 4 :  
          sendLevel(5,1);
          startGameFlag = 1;
          break;
        case 5 :  
          sendLevel(0,0);
          startGameFlag = 1;
          break;
        }    
    }
    prevPtrArray = ptrArray;
    highlight(size, offsetY);
}

/*
void highscore(){
  int yMan = 50;
  tft.setTextColor(ILI9341_WHITE);  
  for(int j = 0; j < 5; j++){
    tft.setCursor(25,yMan);
      tft.println(highscores[j]); 
    }
    yMan += 50;   
}
*/

void loading(){
  tft.fillScreen(ILI9341_BLACK);
  tft.setCursor(25,100);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(4); 
  tft.println("LOADING");
}

void connecting(){
  tft.fillScreen(ILI9341_BLACK);
  tft.setCursor(25,50);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(4); 
  tft.println("CONNECTING");
}