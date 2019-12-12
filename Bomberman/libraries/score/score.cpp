#include <Adafruit_ILI9341.h>
#include <Adafruit_GFX.h>
#include <grid.h>
#include <string.h>
#include "score.h"

// draw the core on screen
void drawScore(Adafruit_ILI9341 *pen,struct DIMENSION dimension,int score)
{
  const char title[] = "score";
  int size,lenx,leny,x,y;
	
	// calculate sizes and places
	lenx = 5*strlen(title);
	size = dimension.width/(lenx);
	x= (dimension.width-(lenx*size))/4;
	leny = 7;
	y= (dimension.height-(leny*size))/2;
	
	// ---- draw
	// draw box
	pen->drawRect(dimension.x,dimension.y,dimension.width,dimension.height,0xff00);
	
	// draw title
	pen->setCursor(dimension.x+x,dimension.y);
	pen->setTextSize(size);
	pen->print(title);
	
	// draw score
	pen->setTextSize(size-1);
	pen->setCursor(dimension.x+x,dimension.y+y);
	pen->print(score);
}