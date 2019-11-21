// header file player
#ifndef PLAYER_H
#define PLAYER_H

// types
enum AIM
{
	UP, DOWN, LEFT, RIGHT
};

struct PLAYER
{
	uint16_t x,y;
};

// functions
uint8_t step(enum AIM direction,uint8_t world[9][9],struct player p1);


#endif
