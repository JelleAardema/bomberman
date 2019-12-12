//include screen specifications
#include <arduino.h>
#include <Adafruit_ILI9341.h>
#include <Adafruit_GFX.h>
#include "grid.h"
#include "bomb.h"
#include <stdint.h>
#include <avr/io.h>
#include <explode.h>



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
        //b1[i].x = 0;
        //b1[i].y = 0;
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
