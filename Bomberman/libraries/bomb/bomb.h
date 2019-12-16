#ifndef BOMB_H_
#define BOMB_H_
#include <arduino.h>
#include <Adafruit_ILI9341.h>
#include <Adafruit_GFX.h>
#include "grid.h"
#include <stdint.h>
#include <avr/io.h>


#define MAXBOMBS 3        // maximum amount of bombs per player
#define FIRE 4
struct BOMB
{
  uint8_t x;
  uint8_t y;
  uint16_t fuse;
  uint8_t placed;
  uint8_t player;
};
void bombs(Adafruit_ILI9341 *pen,struct DIMENSION dimension,uint8_t world[9][9],struct BOMB *b1,struct PLAYER *p1);

#endif
