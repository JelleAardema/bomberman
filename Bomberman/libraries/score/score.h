#include <Adafruit_ILI9341.h>
#include <Adafruit_GFX.h>
#include <grid.h>

#ifndef SCORE_H
#define SCORE_H

// ---- functions
void drawInfo(Adafruit_ILI9341 *pen,struct DIMENSION dimension,const char *title,int value);

#endif