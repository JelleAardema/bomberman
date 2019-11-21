#include <stdint.h>
#include "player.h"
#include "grid.h"
#include <Wire.h>
#include <nunchuk.h>


uint8_t step(enum AIM direction,uint8_t world[9][9],struct PLAYER p1,struct DIMENSION screen)
{
  uint16_t X = p1.x;
  uint16_t Y = p1.y;

	// decides new coordinates based on previous x and y position
  	switch(direction)
	{ 
		case UP:
			X--;
			break;
		case DOWN:
			X++;
			break;
		case LEFT:
			Y--;
			break;
		case RIGHT:
			Y++;
			break;
	}

	// check if move is posible
	if( ((X>=0)&&(X<=GRID_X)) && ((Y>=0)&&(Y<=GRID_Y)) && (!world[X][Y]) )
	{
		struct DIMENSION block;
		calcBlock(screen,&block,p1.x,p1.y);
		drawBlock(pen,block,0);
		// change player cordinate to new cordinate
		p1.y = Y;
		p1.x = X;
		// tell that the move was succesful
		return 1;
	}

	// tell that the move was a failure
	return 0;
}

void drawPlayer(struct PLAYER p1, struct DIMENSION d,Adafruit_ILI9341 *pen,struct DIMENSION screen)
{
	uint16_t block_w,block_l,blockX,blockY;
        // Redraw block

	struct DIMENSION block;
	calcBlock(screen,&block,p1.x,p1.y);
        drawBlock(pen,block,2);
}

void setupNunchuk() {
  nunchuk_init();
}

enum AIM readNunchuk() {
    // check if there's any data to read.
    if (nunchuk_read()) {

       // deadzones of 20, so you're not moving when you're not using the stick.
       if(nunchuk_joystickX() > 20) {
           return RIGHT;
       }

       else if(nunchuk_joystickY() > 20) {
           return UP;
       }

       else if(nunchuk_joystickY() < -20) {
           return DOWN;
       }

       else if(nunchuk_joystickX() < -20) {
           return LEFT;
       }

       // Z button
       if(nunchuk_buttonZ() == 1) {
           return BOMB;
       }

       // C button
       if(nunchuk_buttonC() == 1) {
           return BOMB;
       }

    }
}

