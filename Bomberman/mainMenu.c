#include <Wire.h>
#include <Nunchuk.h>
#include <Adafruit_ILI9341.h>


int started,pos,i,x,y,currentDirection,numMenuItems;
//int items[2]  {1,2};
int getDirection();

char items[2][10] = {
                         "play",
                         "highscore"
                     };

// For the Adafruit shield, these are the default.
#define TFT_DC 9
#define TFT_CS 10



// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
// If using the breakout, change pins as desired
//Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);


void setup() {
  Serial.begin(9600);
  Wire.begin();
  Nunchuk.begin(0x52); 
  tft.begin();

  //Init variables
  numMenuItems = 2;
 
  //Setting up start screen
  tft.fillScreen(ILI9341_BLACK);
  tft.setRotation(1);
  // Setup loop hier voor 
  logoDisplay();

}

void loop(void) {
  Nunchuk.getState(0x52);
   if (Nunchuk.state.z_button == 1 && started == 0){
    //start();
    started = 1;
    tft.fillScreen(ILI9341_BLACK);
    // client side variant die connectie zoekt maken
    highlight();
  }

  if(started == 1){
    if(getDirection() == 3 && currentDirection != 3){
         i++;
         currentDirection = getDirection();
         if(i > numMenuItems -1){
          i = numMenuItems -1;
         }
         highlight();
    }


    if(getDirection() == 1 && currentDirection != 1){
       i--;
        currentDirection = getDirection();
      if(i < 0){
          i = 0;
       }
       highlight();
    }
  }
  if(Nunchuk.state.z_button == 1){
    select();
  }

  if(Nunchuk.state.joy_y_axis == 128){
    currentDirection = 0;
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
void highlight(){  
  //Set text style
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(5); 
  x = 25;
  y = 25;
  for(int j = 0; j < numMenuItems; j++){
    tft.setCursor(x,y);
    if(j == i){
      tft.setTextColor(ILI9341_YELLOW);    
    }
    tft.println(items[j]);
    tft.setTextColor(ILI9341_WHITE);
    y = y +75;   
  }
}


void select(){ 
    switch (i) { 

      case 0 :
          //play();
          Serial.println("Play");
          break;

      case 1 : 
          //highscore();
          Serial.println("highscore");
          break;

      case 2 : 
          //highscore();
          Serial.println("lytse penor");
          break;    
    }
}
