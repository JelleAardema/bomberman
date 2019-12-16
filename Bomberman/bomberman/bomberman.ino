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
#include <connection.h>
#include <globalTimer.h>
#include <explode.h>


int getDirection();
#define host 1

// test data
  Adafruit_ILI9341 screen = Adafruit_ILI9341(TFT_CS, TFT_DC);
  uint8_t wrld[GRID_X][GRID_Y];
  struct DIMENSION dimension = {10,10,220,220};
  struct PLAYER player1 = {1,1,PLAYER1,MAXLIFE};
  struct PLAYER player2 = {7,7,PLAYER2,MAXLIFE};
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
  loadWorld(wrld,5);
  //genWorld(wrld,1);
  //genWorld(wrld,random(1,200));
  drawGrid(&screen,dimension,wrld);


  int a;
  for(a=0;a<MAXBOMBS;a++)
  {
    bomb1[a].x = 0;
    bomb1[a].y = 0;
    bomb1[a].fuse = 0;
    bomb1[a].placed = 0;
    bomb1[a].player = PLAYER1;
  }

  irccBegin(host);
}

void loop() {
  // change test
  if(gameUpdate()){
    
    //drawGrid(&screen,dimension,wrld);
    Nunchuk.getState(0x52);
    if(stepper(&screen,dimension,wrld,(AIM)getDirection(),&player1,bomb1,Nunchuk.state.z_button)){
      drawPlayer(&screen,dimension,player1);
    }
    bombs(&screen,dimension,wrld,bomb1,&player1);
    // stepper(random(-1,5),wrld,&player2,dimension,&screen);
    //drawPlayer(player2,&screen,dimension);
  }
}
