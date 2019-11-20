#include <stdint.h>
#include "player.h"

#define GRID_X 9
#define GRID_Y 9

uint8_t step(enum AIM direction,uint8_t world[9][9],struct PLAYER p1)
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
		// change player cordinate to new cordinate
		p1.y = Y;
		p1.x = X;


		// tell that the move was succesful
		return 1;
	}

	// tell that the move was a failure
	return 0;
}
