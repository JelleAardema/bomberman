#include <Arduino.h>
#include <Adafruit_ILI9341.h>
#include <Adafruit_GFX.h>
#include <stdint.h>

// aansluiting spi op scherm
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
	uint16_t length;
};

// functies
void drawGrid(Adafruit_ILI9341 *,struct DIMENSION,uint8_t grid[GRID_X][GRID_Y]); 
void drawBlock(Adafruit_ILI9341 *,uint16_t,uint16_t,uint16_t,uint16_t,uint8_t);


// hoofd programa
int main()
{
	// setup
	init();
	Adafruit_ILI9341 screen = Adafruit_ILI9341(TFT_CS, TFT_DC);
	screen.begin();

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
	


	// zet cordinate system
  	screen.setRotation(2);	

	// draw start screen
	struct DIMENSION dimension = {10,10,219,200};
	screen.fillScreen(0x0000);
	drawGrid(&screen,dimension,wrld);

	// loop
	while(1);

  return 0;
}

// 240x320
// tekent de hele veld
void drawGrid(Adafruit_ILI9341 *pen,struct DIMENSION d,uint8_t world[GRID_X][GRID_Y])
{
  uint16_t i,q,xar,yar,block_w,block_l;
  	// bereken groote blok
	block_w =d.width/GRID_X;
	block_l =d.length/GRID_Y;

  	// teken rand van speelveld
	pen->drawRect(d.x,d.y,d.width,d.length,0x003f);

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

