#include <Adafruit_ILI9341.h>
#include <Adafruit_GFX.h>
#include "grid.h"

#ifndef EXPLODE_H
#define EXPLODE_H

// functions
void bombWorld(Adafruit_ILI9341 *pen,struct DIMENSION screen,uint8_t world[GRID_X][GRID_Y],int x, int y, int power);
int bombNext(int i, int q,int x, int y, int *calcX, int *calcY,uint8_t world[GRID_X][GRID_Y]);
void clearWave(Adafruit_ILI9341 *pen,struct DIMENSION screen,uint8_t world[GRID_X][GRID_Y],int x, int y, int power);

#endif
