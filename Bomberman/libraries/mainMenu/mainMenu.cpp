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
    startGameFlag,
    levelSeed,
    levelType;

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


char itemsHighscore[1][10] = {
                      ""
                     };

// Pointer initialization
char (*ptrArray)[10];
                
// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
//Adafruit_ILI9341 screen = Adafruit_ILI9341(TFT_CS, TFT_DC);
// If using the breakout, change pins as desired
//Adafruit_ILI9341 screen = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);
Adafruit_ILI9341 *pScreen;


void mainMenuSetup(Adafruit_ILI9341 *pen) {

  pScreen = pen;
  //Setting pointer on first menu page
  ptrArray = itemsMain;

  //Setting text size and array item count
  size = 5;
  offsetY = 75;
  currentPage = 2;

  //Setting up display orientation and clearing
  pen->fillScreen(ILI9341_BLACK);
  pen->setRotation(1);
 
  //Display logo and wait for user input
  logoDisplay();
}


void menu(int host) {
  while(!startGameFlag){
  //Waiting for user input to setup initial connection over IR
  Nunchuk.getState(0x52);
   if (Nunchuk.state.z_button == 1 && started == 0 && z_buttonState != 1){
    z_buttonState = 1;
    started = 1;

    connecting();
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  //startConnection(host);
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    //Clearing screen and drawing the menu items
    pScreen->fillScreen(ILI9341_BLACK);
    highlight(size,offsetY);     
   }

   //Loop for navigation
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
    pScreen->fillScreen(ILI9341_BLACK);
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
  //Displaying loading screen and awaiting game start instructions
  started = 0;
  startGameFlag = 0;
  loading();
}



//Function to display bomberman logo
void logoDisplay(){
  pScreen->setCursor(25,50);
  pScreen->setTextColor(ILI9341_WHITE);
  pScreen->setTextSize(5); 
  pScreen->println("BOMBERMAN");
  pScreen->setCursor(60,150);
  pScreen->setTextColor(ILI9341_WHITE);
  pScreen->setTextSize(2);
  pScreen->println("press Z to start");
} 



//Drawing the menu items and highlighting the selected items
void highlight(int size, int offsetY){  
  if(ptrArray != itemsHighscore){
  pScreen->setTextColor(ILI9341_WHITE);
  pScreen->setTextSize(size); 
  xCoord = 25;
  yCoord = 25;
  for(int j = 0; j < currentPage; j++){
    pScreen->setCursor(xCoord,yCoord);
    for(int k = 0; k < 10; k++){
      if(j == i){
        pScreen->setTextColor(ILI9341_YELLOW);    
      }
      pScreen->setCursor(xCoord,yCoord);
      pScreen->println(ptrArray[j][k]);
      xCoord = xCoord + 30;  
    }
    pScreen->setTextColor(ILI9341_WHITE); 
    xCoord = 25;
    yCoord += offsetY;   
    }
  }
}


//Fucntion to select the coresponding menu page and binding behavior on menu items
void menuSetter(int currentHighlight){
    pScreen->fillScreen(ILI9341_BLACK);
    
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
          ptrArray = itemsHighscore;
          currentPage = 5;
          size = 3;
          offsetY = 35;
          highscore(size,offsetY);
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
      levelType = 1;
      switch (currentHighlight){
        case 0 :   
          levelSeed = 1;
          break;
        case 1 :  
          levelSeed = 2;
          break;
        case 2 :  
          levelSeed = 3;          
          break;
        case 3 :  
          levelSeed = 4;
          break;
        case 4 :  
          levelSeed = 5;
          break;
        case 5 :  
          levelType = 0;
          levelSeed = 0;
          break;
      }
      startGameFlag = 1;
      sendLevel(levelSeed,levelType);    
    }

    highlight(size, offsetY);
}


//Updating the highscores and displaying them 
void highscore(int size, int offsetY){
  updateHighscoreList();
  int * highscores;
  highscores = getHighscoreList();
  xCoord = 50;
  yCoord = 25;
  pScreen->setTextColor(ILI9341_WHITE);
  pScreen->setTextSize(size);
  for(int j = 0; j < currentPage; j++){
    pScreen->setCursor(xCoord,yCoord);
    pScreen->setTextColor(ILI9341_YELLOW);
    pScreen->println(j + 1);
    pScreen->setCursor(xCoord + 20,yCoord);
    pScreen->println(".");
    pScreen->setTextColor(ILI9341_WHITE);
    pScreen->setCursor(xCoord + 40,yCoord);
    pScreen->println(highscores[j]);
    yCoord += offsetY;  
  }
}

//Loading screen
void loading(){
  pScreen->fillScreen(ILI9341_BLACK);
  pScreen->setCursor(25,100);
  pScreen->setTextColor(ILI9341_WHITE);
  pScreen->setTextSize(4); 
  pScreen->println("LOADING");
}

//Connection screen
void connecting(){
  pScreen->fillScreen(ILI9341_BLACK);
  pScreen->setCursor(25,50);
  pScreen->setTextColor(ILI9341_WHITE);
  pScreen->setTextSize(4); 
  pScreen->println("CONNECTING");
}

void getLevel(int* seed,int* type){
  seed = &levelSeed;
  type = &levelType;   
}