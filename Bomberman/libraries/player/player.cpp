#include <arduino.h>
#include <Adafruit_ILI9341.h>
#include <Adafruit_GFX.h>
#include "player.h"
#include "bomb.h"
#include "grid.h"
#include <stdint.h>
#include <avr/io.h>

uint8_t stepper(Adafruit_ILI9341 *pen, struct DIMENSION dimension, uint8_t world[9][9], enum AIM direction, struct PLAYER *p1, struct BOMB *b1, int bomb)
{
  uint16_t X = p1->x;
  uint16_t Y = p1->y;

  // decides new coordinates based on previous x and y position
  switch(direction)
  {
    case NEUTRAL:
      break;
    case UP:
      X--;
      break;
    case DOWN:
      X++;
      break;
    case LEFT:
      Y--;
      break;
    case RIGHT:
      Y++;
      break;
  }
  if(bomb)
  {
    p1->bombPlaced = placeBomb(b1,p1->x,p1->y,world[p1->x][p1->y]);
  }
  // check if move is posible
  if( ((X>=0)&&(X<GRID_X)) && ((Y>=0)&&(Y<GRID_Y)) && (world[X][Y]==air) )
  {
    //clear the previous position of the player to remove the trace
    struct DIMENSION block;
    calcBlock(dimension,&block,p1->x,p1->y);
    drawBlock(pen,block,world[p1->x][p1->y]);
    // change player cordinate to new cordinate
    p1->y = Y;
    p1->x = X;
    // tell that the move was succesful
    return 1;
  }

  // tell that the move was a failure
  return 0;
}

// draw the player
void drawPlayer(Adafruit_ILI9341 *pen,struct DIMENSION screen,struct PLAYER p1)
{
  struct DIMENSION block;
  calcBlock(screen,&block,p1.x,p1.y);
  drawBlock(pen,block,p1.color);
}

// draw air over last position
void clearLastPos(Adafruit_ILI9341 *pen,struct DIMENSION screen, uint8_t world[GRID_X][GRID_Y], struct PLAYER p1)
{
  redrawBlock(pen, screen, world, p1.x, p1.y);
}

uint8_t placeBomb(struct BOMB *b1,uint8_t x,uint8_t y,uint8_t block)
{
  int i;
  //loop through all the bombs
  for(i=0; i<MAXBOMBS; i++)
  {
    //check if bomb can be placed on that position and if the bomb can be saved in array
    if(block==air)
    {
      if(!b1[i].placed )
      {

        b1[i].x = x;
        b1[i].y = y;
        b1[i].placed = 1;
        b1[i].fuse = 0;
        i=MAXBOMBS;
        return 1;

      }
    }
  }
  return 0;

}
