//include screen specifications
#include <arduino.h>
#include <Adafruit_ILI9341.h>
#include <Adafruit_GFX.h>
#include "grid.h"
#include "bomb.h"
#include <stdint.h>
#include <avr/io.h>
#include <explode.h>

/*
  function for bomb functionalities
  the bomb state will be changed everytime the function is called
  state 1: bomb is placed and is counting time till explosion (state 2)
  state 2: bomb explosion is turned on and state is changed to state 3
  state 3: bomb explosion is counting so it will stay for a while and then fade away
*/

void bombs(Adafruit_ILI9341 *pen,struct DIMENSION dimension,uint8_t world[9][9],struct BOMB *b1,struct PLAYER *p1){
int i;
  for(i=0;i<MAXBOMBS;i++)
  {
    if(b1[i].placed == 1)
    {
      uint16_t j = 15;
      b1[i].fuse++;

      if(b1[i].fuse > j)
      {
        b1[i].placed = 2;
      }
      struct DIMENSION block;
      calcBlock(dimension,&block,b1[i].x,b1[i].y);
      drawBlock(pen,block,bomb);
      changeBlock(pen,dimension,world,b1[i].x,b1[i].y,bomb);
      }
      if(b1[i].placed == 2)
      {
        struct DIMENSION block;
        calcBlock(dimension,&block,b1[i].x,b1[i].y);
        drawBlock(pen,block,air);
        b1[i].placed = 3;
        b1[i].fuse = 0;
        changeBlock(pen,dimension,world,b1[i].x,b1[i].y,air);
        bombWorld(pen,dimension,world,b1[i].x,b1[i].y,FIRE,p1);
      }
      if(b1[i].placed == 3)
      {
          uint16_t fire = 3;
          b1[i].fuse++;
          if(b1[i].fuse > fire)
          {
              clearWave(pen,dimension,world,b1[i].x,b1[i].y,FIRE);
              b1[i].placed = 0;

          }
      }
  }
}
