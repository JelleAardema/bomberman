#include <Adafruit_ILI9341.h>
#include <Adafruit_GFX.h>
#include <stdint.h>
#include "grid.h"

// Draw whole grid
void drawGrid(Adafruit_ILI9341 *pen,struct DIMENSION d,uint8_t world[GRID_X][GRID_Y])
{
  uint16_t i,q,xar,yar,block_w,block_l;
  	// calculate size of block
	block_w =d.width/GRID_X;
	block_l =d.length/GRID_Y;

  	// Draw border of grid
	pen->drawRect(d.x,d.y,d.width,d.length,BLUE);

	// Draw grid
	for(i=d.x,xar=0; i<=d.width; i+=block_w,xar++)
	{
		for(q=d.y,yar=0; q<=d.length; q+=block_l,yar++)
		{
			drawBlock(pen,i,q,block_w,block_l,world[xar][yar]);
		}
	}
}	

// Draw a block
void drawBlock(Adafruit_ILI9341 *pen,uint16_t x,uint16_t y,uint16_t width, uint16_t length,uint8_t type)
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
	pen->fillRect(x,y,width,length,color);
}

// changeBlock type and Draw change to screen
void changeBlock(Adafruit_ILI9341 *pen,struct DIMENSION d,uint8_t grid[GRID_X][GRID_Y],uint16_t x,uint16_t y,uint8_t newtype)
{
  uint16_t block_w,block_l,blockX,blockY;
	// change type of block
	grid[x][y] = newtype;
	
	// calculate the position and size of block on screen
	block_w = d.width/GRID_X;
	block_l = d.length/GRID_Y;
	blockX = d.x + block_w*x;
	blockY = d.y + block_l*y;

	// Redraw block
	drawBlock(pen,blockX,blockY,block_w,block_l,grid[x][y]);	
}


