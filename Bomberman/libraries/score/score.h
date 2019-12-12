#include <Adafruit_ILI9341.h>
#include <Adafruit_GFX.h>
#include <grid.h>

#ifndef SCORE_H
#define SCORE_H

// ---- functions
void drawScore(Adafruit_ILI9341 *pen,struct DIMENSION dimension,int score);

#endif