#include "Move.h"
#include "grid.h"
#include <stdint.h>
enum AIM{UP, DOWN, LEFT, RIGHT};

uint8_t move(enum AIM direction,uint8_t world[GRID_X][GRID_Y],struct player p1){
  uint16_t X = p1.x;
  uint16_t Y = p1.y;
	switch(direction){ // decides new coordinates based on previous x and y position
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
	if(((X>=0)&&(X<=GRID_X))&&((Y>=0)&&(Y<=GRID_Y))){
		p1.y = Y;
		p1.x = X;
		return 1;
	}
		return 0;
}
