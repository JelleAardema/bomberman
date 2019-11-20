#include <Arduino.h>
#include <Adafruit_ILI9341.h>
#include <Adafruit_GFX.h>
#include <stdint.h>
#include <util/delay.h>
#include "grid.h"
#include "player.h"

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
	
	struct PLAYER player= {1,1}; 

	// zet cordinate system
  	screen.setRotation(2);	

	// draw start screen
	struct DIMENSION dimension = {10,10,219,200};
	screen.fillScreen(0x0000);
	drawGrid(&screen,dimension,wrld);

	// loop
	while(1)
	{
		// move test
		// change test
		changeBlock(&screen,dimension,wrld,4,4,1);
		_delay_ms(1000);
		changeBlock(&screen,dimension,wrld,4,4,0);
		_delay_ms(1000);
	}

  return 0;
}


