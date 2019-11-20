#include <Adafruit_ILI9341.h>
#include <Adafruit_GFX.h>
#include <stdint.h>
#include "grid.h"

// Draw whole grid
void drawGrid(Adafruit_ILI9341 *pen,struct DIMENSION screen,uint8_t world[GRID_X][GRID_Y])
{
  uint16_t x,y;
  struct DIMENSION block;
  	// Draw border of grid
	pen->drawRect(screen.x,screen.y,screen.width,screen.length,BLUE);

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
  	// Decide wich collor is uded
	switch(type)
	{
		case 0:
			color=WHITE;
			break;
		case 1:
			color=GREEN;
			break;
		default:
			color=BLACK;
	}	

  	// Draw block
	pen->fillRect(block.x,block.y,block.width,block.length,color);
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

// calculate block
void calcBlock(struct DIMENSION screen,struct DIMENSION *block,uint16_t x,uint16_t y)
{ 
	// calculate the position and size of block on screen
	block->width = screen.width/GRID_X;
	block->length = screen.length/GRID_Y;
	block->x = screen.x + block->width*x;
	block->y = screen.y + block->length*y;

}
