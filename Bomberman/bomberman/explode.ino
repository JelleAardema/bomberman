// destructing wave
void bombWorld(uint8_t world[GRID_X][GRID_Y],int x, int y, int power)
{
  int i,q,calcX,calcY;
    // go trough all directions (left,right,up,down) of explosion
    for(q=0; q < 4; q++)
    {
      // go trough the blocks that are in explosion range
      for(i=1; i<power; i++)
      {
        // calculate which block is next and check of it can be destroyed
        if(bombNext(i,q,x,y,&calcX, &calcY,world))
        {
          // destroy the block
          world[calcX][calcY] = air;
        }  
    }
}

// calc next block to destroy and check if the block is within the world
int bombNext(int i, int q,int x, int y, int *calcX, int *calcY,uint8_t world[GRID_X][GRID_Y])
{
  // calculate which block is next
  *calcX = x + ((q==0)?i:0) - ((q==1)?i:0);
  *calcY = y + ((q==2)?i:0) - ((q==3)?i:0);
  
  // check if next block is in world, if not return false
  if(!((*calcX >= 0) && (*calcX < GRID_X) && (*calcY >= 0) && (*calcY < GRID_Y)))
    return 0;

  // check of block is destuctable, if not return false
  if(world[*calcX][*calcY] == wall)
    return 0;

  // if this point is reached, the block is destructuble and is in fire wave
  return 1;
}
