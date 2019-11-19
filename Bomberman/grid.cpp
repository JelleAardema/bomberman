#include <Adafruit_ILI9341.h>
#include <Adafruit_GFX.h>
#include <stdint.h>
#include "grid.h"

// de scherm groote is 240x320
// tekent de hele veld
void drawGrid(Adafruit_ILI9341 *pen,struct DIMENSION d,uint8_t world[GRID_X][GRID_Y])
{
  uint16_t i,q,xar,yar,block_w,block_l;
  	// bereken groote blok
	block_w =d.width/GRID_X;
	block_l =d.length/GRID_Y;

  	// teken rand van speelveld
	pen->drawRect(d.x,d.y,d.width,d.length,BLUE);

	// teken grid
	for(i=d.x,xar=0; i<=d.width; i+=block_w,xar++)
	{
		for(q=d.y,yar=0; q<=d.length; q+=block_l,yar++)
		{
			drawBlock(pen,i,q,block_w,block_l,world[xar][yar]);
		}
	}
}	

// tekent een blok
void drawBlock(Adafruit_ILI9341 *pen,uint16_t x,uint16_t y,uint16_t width, uint16_t length,uint8_t type)
{
  uint16_t color;
  	// bepaal welke kleur
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

  	// teken blok
	pen->fillRect(x,y,width,length,color);
}

// verandert een blok en tekent dat blok
void changeBlock(Adafruit_ILI9341 *pen,struct DIMENSION d,uint8_t grid[GRID_X][GRID_Y],uint16_t x,uint16_t y,uint8_t newtype)
{
  uint16_t block_w,block_l,blockX,blockY;
	// verander de type van opgageven blok
	grid[x][y] = newtype;
	
	// positie van blok op scherm berekenen
	block_w = d.width/GRID_X;
	block_l = d.length/GRID_Y;
	blockX = d.x + block_w*x;
	blockY = d.y + block_l*y;

	// herteken het nieuwe blok
	drawBlock(pen,blockX,blockY,block_w,block_l,grid[x][y]);	
}


