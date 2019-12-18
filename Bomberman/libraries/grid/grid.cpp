#include <Adafruit_ILI9341.h>
#include <Adafruit_GFX.h>
#include "grid.h"
#include <stdint.h>
#include <avr/io.h>
#include <arduino.h>
#include <sprites.h>


// Draw whole grid
void drawGrid(Adafruit_ILI9341 *pen,struct DIMENSION screen,uint8_t world[GRID_X][GRID_Y])
{
  uint16_t x,y;
  struct DIMENSION block;
    // Draw border of grid
  pen->drawRect(screen.x,screen.y,screen.width,screen.height,BLUE);

  // Draw grid
  for(x=0; x<GRID_X; x++)
  {
    for(y=0; y<GRID_Y; y++)
    {
      calcBlock(screen,&block,x,y);
      drawBlock(pen,block,world[x][y]);
    }
  }
}

// Draw a block
void drawBlock(Adafruit_ILI9341 *pen,struct DIMENSION block,uint8_t type)
{
	uint16_t color;
    // Decide wich color is used
	switch(type)
	{
		case 0:		// white, floor
			spriteFloor(block.x, block.y, pen);
			break;
		case 1:		// green, full wall
			spriteWall(block.x, block.y, pen);
			break;
		case 2:		// blue, break wall
			spriteBox(block.x, block.y, pen);
			break;
		case 3:		// red, bomb
			spriteBomb(block.x, block.y, pen);
			break;
		case 4:		// yellow, player
			spritePlayer(block.x, block.y,1, pen);
			break;
		case 5:		// destruction wave
			spriteExplosion(block.x, block.y, pen);
			break;
		case 6:		// yellow, player
			spritePlayer(block.x, block.y,0, pen);
			break;
		default:	// black
			color=BLACK;
			pen->fillRect(block.x,block.y,block.width,block.height,color);
  }
}

// changeBlock type and Draw change to screen
void changeBlock(Adafruit_ILI9341 *pen,struct DIMENSION screen,uint8_t grid[GRID_X][GRID_Y],uint16_t x,uint16_t y,uint8_t newtype)
{
  // change type of block
  grid[x][y] = newtype;

  // calculate the position and size of block on screen
  struct DIMENSION block;
  calcBlock(screen,&block,x,y);

  // Redraw block
  drawBlock(pen,block,grid[x][y]);
}

// redraw a block from grid
void redrawBlock(Adafruit_ILI9341 *pen,struct DIMENSION screen,uint8_t grid[GRID_X][GRID_Y],uint16_t x,uint16_t y)
{
  // calculate the position and size of block on screen
  struct DIMENSION block;
  calcBlock(screen,&block,x,y);

  // Redraw block
  drawBlock(pen,block,grid[x][y]);
}

// calculate block
void calcBlock(struct DIMENSION screen,struct DIMENSION *block,uint16_t x,uint16_t y)
{
  // calculate the position and size of block on screen
  block->width = screen.width/GRID_X;
  block->height = screen.height/GRID_Y;
  block->x = screen.x + block->width*x;
  block->y = screen.y + block->height*y;
}
