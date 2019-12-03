#include <Wire.h>
#include <Nunchuk.h>
#include <Adafruit_ILI9341.h>
#include <connection.h>

int started,pos,i,xCoord,yCoord,currentDirection;

int currentPage;
int z_buttonState;
int getDirection();
int size = 5;
int offsetY = 75;

char itemsMain[2][10] = {
                         "play",
                         "highscore"
                     };

char itemsPlay[2][10] = {
                         "Level",
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

char itemsHighscore[3][10] = {
                         "highscore",
                         "test",
                         "godver"
                     };


// Pointer initialization

char (*ptrArray)[10];
char (*prevPtrArray)[10];
                

// For the Adafruit shield, these are the default.
#define TFT_DC 9
#define TFT_CS 10


#define host 1
// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
// If using the breakout, change pins as desired
//Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);


void setup() {
  Serial.begin(9600);
  Wire.begin();
  Nunchuk.begin(0x52); 
  tft.begin();


  // Experimental pointer option
  ptrArray = itemsMain;
  currentPage = sizeof(ptrArray);         

  //Setting up start screen
  tft.fillScreen(ILI9341_BLACK);
  tft.setRotation(1);
  // Setup loop here 
  logoDisplay();
}


void loop(void) {
  Nunchuk.getState(0x52);
   if (Nunchuk.state.z_button == 1 && started == 0 && z_buttonState != 1){
    z_buttonState = 1;
    started = 1;
    //start();
    //startConnection(host);
    tft.fillScreen(ILI9341_BLACK);
    highlight(size,offsetY);     
    // client side variant that display connection status
   }

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
    menuSetter(i);
  }

  if(Nunchuk.state.c_button == 1){
    ptrArray = itemsMain;
    Serial.println("c button down");
    tft.fillScreen(ILI9341_BLACK);
    highlight(size,offsetY);
  }

  if(Nunchuk.state.joy_y_axis == 128){
    currentDirection = 0;
  }

  if(Nunchuk.state.z_button == 0){
    z_buttonState = 0;
  }
}

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

void menuSetter(int currentHighlight){
    tft.fillScreen(ILI9341_BLACK);
    
    //Main menu 
    if(ptrArray == itemsMain){
      size = 5;
      offsetY = 75;
      switch (currentHighlight){
        case 0 : 
          ptrArray = itemsPlay;  
          Serial.println("play");
          break;
        case 1 :
          ptrArray = itemsHighscore;  
          Serial.println("highscore");
          break;
        }    
    }
    
    //Play menu
    if(ptrArray == itemsPlay){
      size = 5;
      offsetY = 75;
      switch (currentHighlight){
        case 0 : 
          ptrArray =  itemsLevel;  
          Serial.println("level");
          break;
        case 1 :
          ptrArray = itemsHighscore;  
          Serial.println("test");
          break;
        }    
    }

    //Level select
    if(ptrArray == itemsLevel){
      size = 2;
      offsetY = 30;
      switch (currentHighlight){
        case 0 :   
          Serial.println("level - 1");
          break;
        case 1 :  
          Serial.println("Level - 2");
          break;
        case 2 :  
          Serial.println("Level - 3");
          break;
        case 3 :  
          Serial.println("Level - 4");
          break;
        case 4 :  
          Serial.println("Level - 5");
          break;
        case 5 :  
          Serial.println("Generate random");
          break;
        }    
    }

    //Highscore menu
    if(ptrArray == itemsHighscore){
      size = 5;
      offsetY = 75;
      switch (currentHighlight){
        case 0 : 
          ptrArray = itemsPlay;  
          Serial.println("highscore");
          break;
        case 1 :
          ptrArray = itemsHighscore;  
          Serial.println("test");
          break;
        case 2 :
          ptrArray = itemsHighscore;  
          Serial.println("godver");
          break;
        }    
    }

    prevPtrArray = ptrArray;
    currentPage = sizeof(ptrArray);
    highlight(size, offsetY);
}

