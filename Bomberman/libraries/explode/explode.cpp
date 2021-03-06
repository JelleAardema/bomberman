#include <Adafruit_ILI9341.h>
#include <Adafruit_GFX.h>
#include <grid.h>
#include "explode.h"
#include <bomb.h>
#include <player.h>
#include <highscore.h>

// destructing wave
void bombWorld(Adafruit_ILI9341 *pen,struct DIMENSION screen,uint8_t world[GRID_X][GRID_Y],int x, int y, int power,struct PLAYER *p1,uint8_t bOm)
{
  int i,q,calcX,calcY;
  struct DIMENSION block;
	//subtract two lifes from player, if player is on center of explosion
    if((p1->x == x)&&(p1->y == y))
		p1->life -= 1;

	// draw destruction wave at bomb
	calcBlock(screen,&block,x,y);
    drawBlock(pen,block,5);

    // go trough all directions (left,right,up,down) of explosion
    for(q=0; q < 4; q++)
    {
      // go trough the blocks that are in explosion range
      for(i=1; i<power; i++)
      {
        // calculate which block is next and check of it can be destroyed
        if(bombNext(i,q,x,y,&calcX, &calcY,world,bOm))
        {
          // destroy the block
          world[calcX][calcY] = air;

          // draw destruction wave
          calcBlock(screen,&block,calcX,calcY);
          drawBlock(pen,block,5);

          //subtract life from player when in field
          if((p1->y == calcY)&&(p1->x == calcX))
            p1->life = p1->life - 1;
        }
        else break;
      }
    }
  }

// clear exploding cloud
void clearWave(Adafruit_ILI9341 *pen,struct DIMENSION screen,uint8_t world[GRID_X][GRID_Y],int x, int y, int power)
{
  int i,q,calcX,calcY;
	// redraw block in the middle
	redrawBlock(pen,screen,world,x,y);

    // go trough all directions (left,right,up,down) of explosion
    for(q=0; q < 4; q++)
    {
      // go trough the blocks that are in explosion range
      for(i=1; i<power; i++)
      {
        // calculate which block is next and check of it can be destroyed
        if(bombNext(i,q,x,y,&calcX, &calcY,world,0))
        {
          // redraw block
          redrawBlock(pen,screen,world,calcX,calcY);
        }

        else break;
    }
  }
}

// calc next block to destroy and check if the block is within the world
int bombNext(int i, int q,int x, int y, int *calcX, int *calcY,uint8_t world[GRID_X][GRID_Y],uint8_t bOm)
{
 static int explode=0;
  // if previous time, a block expode stop wave
  if(explode==1)
  {
	  explode=0;
    if(bOm == PLAYER1){
      // Add points for destroying a tile
     destroyTileScore();
    }

	  return 0;
  }

  // calculate which block is next
  *calcX = x + ((q==0)?i:0) - ((q==1)?i:0);
  *calcY = y + ((q==2)?i:0) - ((q==3)?i:0);

  // check if next block is in world, if not return false
  if(!((*calcX >= 0) && (*calcX < GRID_X) && (*calcY >= 0) && (*calcY < GRID_Y)))
    return 0;

  // check of block is destuctable, if not return false
  if(world[*calcX][*calcY] == wall) {
    return 0;
  }

  // check of block is air
  if(world[*calcX][*calcY] == air){
    explode = 0;
  }else{
    explode = 1;
  }
  // if this point is reached, the block is destructuble and is in fire wave
  return 1;
}
