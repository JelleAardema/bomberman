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
                         "highscore",
                         "test"
                         
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
  irccBegin(1);


  // Experimental pointer option
  ptrArray = itemsMain;
  //Setting text size and array item count
  size = 5;
  offsetY = 75;
  currentPage = 2;
  //currentPage = sizeof(ptrArray[0])/sizeof(ptrArray[0][0]);         

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
  
    //START DE CONNECTIE MET ANDERE ARDUINO
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
    z_buttonState = 1;
    menuSetter(i);
  }

  if(Nunchuk.state.c_button == 1){
    ptrArray = itemsMain;
    Serial.println("c button down");
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
      switch (currentHighlight){
        case 0 : 
          ptrArray = itemsPlay;  
          Serial.println("play");
          currentPage = 1;
          size = 5;
          offsetY = 75;
          break;
        case 1 :
          ptrArray = itemsHighscore;  
          Serial.println("highscore");
          currentPage = 5;
          size = 2;
          offsetY = 30;
          break;
        }    
    }
    
    //Play menu 
    else if(ptrArray == itemsPlay){
      switch (currentHighlight){
        case 0 : 
          ptrArray =  itemsLevel;  
          Serial.println("Start");
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
          Serial.println("level - 1");
          sendLevel(1,1);
          break;
        case 1 :  
          Serial.println("Level - 2");
          sendLevel(2,1);
          break;
        case 2 :  
          Serial.println("Level - 3");
          sendLevel(3,1);
          break;
        case 3 :  
          Serial.println("Level - 4");
          sendLevel(4,1);
          break;
        case 4 :  
          Serial.println("Level - 5");
          sendLevel(5,1);
          break;
        case 5 :  
          Serial.println("Generate random");
          sendLevel(0,0);
          break;
        }    
    }

    //Highscore menu
    else if(ptrArray == itemsHighscore){
      switch (currentHighlight){
        case 0 : 

        }    
    }
    prevPtrArray = ptrArray;
    highlight(size, offsetY);
}

