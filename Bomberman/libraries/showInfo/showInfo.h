#include <Adafruit_ILI9341.h>
#include <Adafruit_GFX.h>
#include <grid.h>

#ifndef SHOW_INFO_H
#define SHOW_INFO_H

// ---- functions
uint16_t drawInfo(Adafruit_ILI9341 *pen,struct DIMENSION dimension,const char *title,int value,int prev);

#endif
