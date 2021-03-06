#ifndef GRID_H_
#define GRID_H_

#include <arduino.h>
#include <Adafruit_ILI9341.h>
#include <Adafruit_GFX.h>
#include <stdint.h>
#include <avr/io.h>
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

enum BLOCK_T
{
        air,
        wall,
        destruct,
        bomb
};

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
void redrawBlock(Adafruit_ILI9341 *pen,struct DIMENSION screen,uint8_t grid[GRID_X][GRID_Y],uint16_t x,uint16_t y);

#endif
