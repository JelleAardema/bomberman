#ifndef PLAYER_H_
#define PLAYER_H_
#include <arduino.h>
#include <Adafruit_ILI9341.h>
#include <Adafruit_GFX.h>
#include "grid.h"
#include <stdint.h>
#include <avr/io.h>


#define FUSETIME 300     // Fuse time in ms
#define WALKSPEED 100     // time before next step can be taken
#define MAXBOMBS 3        // maximum amount of bombs per player


enum AIM
{
  NEUTRAL, LEFT, DOWN, RIGHT,UP, BOMB
};


uint8_t stepper(enum AIM direction,uint8_t world[9][9],struct PLAYER *p1,struct DIMENSION dimension,Adafruit_ILI9341 *pen,struct BOMB *b1, int bomb);
void drawPlayer(struct PLAYER p1, Adafruit_ILI9341 *pen,struct DIMENSION screen);


struct PLAYER
{
  uint16_t x,y,color;
};




#endif
