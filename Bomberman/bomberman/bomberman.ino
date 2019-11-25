#include <Adafruit_ILI9341.h>
#include <Adafruit_GFX.h>
#include <stdint.h>
#include <avr/io.h>
#include <Wire.h>
#include "nunchuk.h"

// screen conections spi
#define TFT_DC 9
#define TFT_CS 10

// grid size
#define GRID_X 9
#define GRID_Y 9

//game behavior rules
//#define FUSETIME 300     // Fuse time in ms
#define WALKSPEED 100     // time before next step can be taken
#define MAXBOMBS 3        // maximum amount of bombs per player
// colors
#define BLACK    0x0000
#define BLUE     0x001F
#define RED      0xF800
#define GREEN    0x07E0
#define CYAN     0x07FF
#define MAGENTA  0xF81F
#define YELLOW   0xFFE0 
#define WHITE    0xFFFF

// structs
struct DIMENSION
{
  uint16_t x;
  uint16_t y;
  uint16_t width;
  uint16_t height;
};
enum AIM
{
  NEUTRAL, LEFT, DOWN, RIGHT,UP, BOMB
};

struct PLAYER
{
  uint16_t x,y,color;
};

struct BOMB 
{
  uint8_t x[MAXBOMBS];
  uint8_t y[MAXBOMBS];
  uint8_t fuse[MAXBOMBS];
  uint8_t range;
  uint8_t placed;
};
// functions
void drawGrid(Adafruit_ILI9341 *,struct DIMENSION,uint8_t grid[GRID_X][GRID_Y]); 
void drawBlock(Adafruit_ILI9341 *,struct DIMENSION,uint8_t);
void changeBlock(Adafruit_ILI9341 *,struct DIMENSION,uint8_t grid[GRID_X][GRID_Y],uint16_t,uint16_t,uint8_t);
void calcBlock(struct DIMENSION screen,struct DIMENSION *block,uint16_t x,uint16_t y);
void redrawBlock(Adafruit_ILI9341 *pen,struct DIMENSION screen,uint8_t grid[GRID_X][GRID_Y],uint16_t x,uint16_t y);

uint8_t stepper(enum AIM direction,uint8_t world[9][9],struct PLAYER p1,struct DIMENSION scren); 
void drawPlayer(struct PLAYER p1, Adafruit_ILI9341 *pen,struct DIMENSION screen);

int getDirection();
// types



Adafruit_ILI9341 screen = Adafruit_ILI9341(TFT_CS, TFT_DC);
// test data
  uint8_t wrld[GRID_X][GRID_Y]={
      {1,1,1,1,1,1,1,1,1},
      {1,0,0,0,0,0,0,0,1},
      {1,0,1,0,1,0,1,0,1},
      {1,0,0,0,0,0,0,0,1},
      {1,0,1,0,1,0,1,0,1},
      {1,0,0,0,0,0,0,0,1},
      {1,0,1,0,1,0,1,0,1},
      {1,0,0,0,0,0,0,0,1},
      {1,1,1,1,1,1,1,1,1}};
  

  struct DIMENSION dimension = {10,10,220,220};
  struct PLAYER player1 = {1,1,2}; 
  struct PLAYER player2 = {7,7,3};
  struct BOMB bomb1;
  struct BOMB bomb2;
void setup() {
    // setup
    init();
    Wire.begin();
  screen.begin(); 
  Nunchuk.begin(0x52);
  // zet cordinate system
    screen.setRotation(1);  
Serial.begin(9600);
  // draw start screen
  screen.fillScreen(0x0000);
  drawGrid(&screen,dimension,wrld);

 
}

void loop() {
  // change test
    delay(200);
    Nunchuk.getState(0x52);
    stepper((AIM)getDirection(),wrld,&player1,dimension,&screen,&bomb1);
    drawPlayer(player1,&screen,dimension);
   // stepper(random(-1,5),wrld,&player2,dimension,&screen);
    //drawPlayer(player2,&screen,dimension);
     
}
