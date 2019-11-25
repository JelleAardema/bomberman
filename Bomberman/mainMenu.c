#include <Wire.h>
#include <Nunchuk.h>
#include <Adafruit_ILI9341.h>

int started,pos,i,x,y;
int items[]  {1,2,3};

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
  

  //Setting up start screen
  tft.fillScreen(ILI9341_BLACK);
  tft.setRotation(1);
  logoDisplay();
}

void loop(void) {
  Nunchuk.getState(0x52);
   if (Nunchuk.state.z_button == 1 && started == 0){
    start();
    select();
    i = 1;
  }
  if(started == 1){
    if(Nunchuk.state.joy_y_axis > 148){
         i++;
         delay(200);
         if(i > 3){
          i = 3;
         }
         select();
         Serial.println(i);
    }
    if(Nunchuk.state.joy_y_axis < 108){
       i--;
       delay(200);
       if(i < 1){
        i = 1;
       }
       select();
       Serial.println(i);
 
    }
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

void start(){
  tft.fillScreen(ILI9341_BLACK);
  tft.setCursor(110,50);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(5); 
  tft.println("PLAY");
  tft.setCursor(10,150);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(5); 
  tft.println("HIGHSCORES");
  started = 1; 
}


void select(){
  //screen rolling clear
  tft.fillScreen(ILI9341_BLACK);
  
  //Set text style
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(5); 
  x = 110;
  y = 50;
  for(int j = 0; j<items; j++){
    tft.setCursor(x,y);
    if(items[j] == i){
      tft.setTextColor(ILI9341_YELLOW);    
    }
    tft.println(items[j]);
    tft.setTextColor(ILI9341_WHITE);
    y = y +50;   
  }
}



