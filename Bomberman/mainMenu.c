#include <Wire.h>
#include <Nunchuk.h>
#include <Adafruit_ILI9341.h>

int started,pos;


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
  
  tft.fillScreen(ILI9341_BLACK);
  tft.setRotation(1);
  logoDisplay();
}

void loop(void) {
  Nunchuk.getState(0x52);
  Serial.println(Nunchuk.state.joy_y_axis);
  if (Nunchuk.state.z_button == 1 && started == 0){
    start();
    selectPlay();
  }
  if(started == 1){
    if(Nunchuk.state.joy_y_axis > 148){
       selectPlay();
    }
    if(Nunchuk.state.joy_y_axis > 148){
       selectPlay();
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


void selectPlay(){
  tft.setCursor(110,50);
  tft.setTextColor(ILI9341_YELLOW);
  tft.setTextSize(5); 
  tft.println("PLAY");
  tft.setCursor(10,150);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(5); 
  tft.println("HIGHSCORES");
}

void selectHigh(){
  tft.setCursor(10,150);
  tft.setTextColor(ILI9341_YELLOW);
  tft.setTextSize(5); 
  tft.println("HIGHSCORES");
  tft.setCursor(110,50);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(5); 
  tft.println("PLAY");
}




