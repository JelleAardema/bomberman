#include <Adafruit_ILI9341.h>
#include <Adafruit_GFX.h>
#include <stdint.h>

// screen conections spi
#define TFT_DC 9
#define TFT_CS 10

// grid size
#define GRID_X 9
#define GRID_Y 9

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

// functions
void drawGrid(Adafruit_ILI9341 *,struct DIMENSION,uint8_t grid[GRID_X][GRID_Y]); 
void drawBlock(Adafruit_ILI9341 *,struct DIMENSION,uint8_t);
void changeBlock(Adafruit_ILI9341 *,struct DIMENSION,uint8_t grid[GRID_X][GRID_Y],uint16_t,uint16_t,uint8_t);
void calcBlock(struct DIMENSION screen,struct DIMENSION *block,uint16_t x,uint16_t y);

// types
enum AIM
{
  UP, DOWN, LEFT, RIGHT
};

struct PLAYER
{
  uint16_t x,y;
};

// functions
uint8_t step(enum AIM direction,uint8_t world[9][9],struct player p1);

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
  

  struct DIMENSION dimension = {10,10,219,200};
  
void setup() {
    // setup
  screen.begin(); 

  // zet cordinate system
    screen.setRotation(2);  

  // draw start screen
  screen.fillScreen(0x0000);
  drawGrid(&screen,dimension,wrld);
}

void loop() {
  // change test
    changeBlock(&screen,dimension,wrld,4,4,1);
    delay(1000);
    changeBlock(&screen,dimension,wrld,4,4,0);
    delay(1000);
}
