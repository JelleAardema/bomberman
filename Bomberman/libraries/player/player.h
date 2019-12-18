#ifndef PLAYER_H_
#define PLAYER_H_
#include <arduino.h>
#include <Adafruit_ILI9341.h>
#include <Adafruit_GFX.h>
#include "grid.h"
#include <stdint.h>
#include <avr/io.h>


#define FUSETIME 300      // Fuse time in ms
#define WALKSPEED 100     // time before next step can be taken
#define MAXBOMBS 3        // maximum amount of bombs per player
#define MAXLIFE 3         // maximum life (hearts) per player

#define PLAYER1 4         // Player number based on color enum 
#define PLAYER2 5

enum AIM
{
  NEUTRAL, LEFT, DOWN, RIGHT,UP, BOMB
};


uint8_t stepper(Adafruit_ILI9341 *pen, struct DIMENSION dimension, uint8_t world[9][9], enum AIM direction, struct PLAYER *p1, struct BOMB *b1, int bomb);
void drawPlayer(Adafruit_ILI9341 *pen,struct DIMENSION screen,struct PLAYER p1);
uint8_t placeBomb(struct BOMB *b1,uint8_t x,uint8_t y,uint8_t block);
void clearLastPos(Adafruit_ILI9341 *pen,struct DIMENSION screen,struct PLAYER p1);

struct PLAYER
{
  uint8_t x,y,life,bombPlaced,color;
};




#endif
