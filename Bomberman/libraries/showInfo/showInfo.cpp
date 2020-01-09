#include <Adafruit_ILI9341.h>
#include <Adafruit_GFX.h>
#include <grid.h>
#include <string.h>
#include "showInfo.h"

// draw the core on screen
uint16_t drawInfo(Adafruit_ILI9341 *pen,struct DIMENSION dimension,const char *title,int value,int prev)
{
  if(value == prev)
    return value;

  int size,lenx,leny,x,y;

	// calculate sizes and places
	lenx = 5*strlen(title);
	size = dimension.width/(lenx);
	x= (dimension.width-(lenx*size))/4;
	leny = 7;
	y= (dimension.height-(leny*size))/2+3;

	// ---- draw
	// draw box
	pen->fillRect(dimension.x,dimension.y,dimension.width,dimension.height,0x0000);
	pen->drawRect(dimension.x,dimension.y,dimension.width,dimension.height,0xff00);

	// draw title
	pen->setCursor(dimension.x+x,dimension.y+3);
	pen->setTextSize(size);
	pen->print(title);

	// draw value
	pen->setTextSize(size-1);
	pen->setCursor(dimension.x+x,dimension.y+y);
	pen->print(value);
  return value;
}
