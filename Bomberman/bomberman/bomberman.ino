#include <Adafruit_ILI9341.h>
#include <Adafruit_GFX.h>
#include <stdint.h>
#include <avr/io.h>
#include <Wire.h>
#include <Nunchuk.h>
#include <player.h>
#include <bomb.h>
#include <grid.h>
#include <level.h>

int getDirection();
#define host 1

// test data
  Adafruit_ILI9341 screen = Adafruit_ILI9341(TFT_CS, TFT_DC);
  uint8_t wrld[GRID_X][GRID_Y];
  struct DIMENSION dimension = {10,10,220,220};
  struct PLAYER player1 = {1,1,4};
  struct PLAYER player2 = {7,7,3};
  struct BOMB bomb1[MAXBOMBS];
  struct BOMB bomb2;

void setup() {
  // setup
  init();
  Wire.begin();
  screen.begin();
  Nunchuk.begin(0x52);
  // zet cordinate system
  screen.setRotation(1);

  // draw start screen
  screen.fillScreen(0x0000);
  //genWorld(wrld,1);
  genWorld(wrld,random(1,200));
  drawGrid(&screen,dimension,wrld);
  

  int a;
  for(a=0;a<MAXBOMBS;a++)
  {
    bomb1[a].x = 0;
    bomb1[a].y = 0;
    bomb1[a].fuse = 0;
    bomb1[a].placed = 0;
  }
  
  irccBegin(host);
}

void loop() {
  // change test
  if(gameUpdate()){
    Nunchuk.getState(0x52);
    if(stepper((AIM)getDirection(),wrld,&player1,dimension,&screen,bomb1,Nunchuk.state.z_button)){
      drawPlayer(player1,&screen,dimension);
    }
    bombs(bomb1,&screen,dimension,wrld);
    // stepper(random(-1,5),wrld,&player2,dimension,&screen);
    //drawPlayer(player2,&screen,dimension);
  }
}
