// destructing wave
void bombWorld(uint8_t world[GRID_X][GRID_Y],int x, int y, int power)
{
  int i,q,calcX,calcY;
  uint8_t *p;
    // go trough all directions (left,right,up,down) of explosion
    for(q=0; q < 4; q++)
  {
    // go trough the blocks that are in explosion range
      for(i=1; i<power; i++)
    {
      // calculate which block is next
      if(!bombNext(i,q,x,y,&calcX, &calcY))
        break;
      
      // get block adress
      p=&world[calcX][calcY];

      // detemnine if the block will be destroyed 
      if(*p != wall)
        *p = air;
      else
        break;
    }
  }
}

// calc next block to destroy and check if the block is within the world
int bombNext(int i, int q,int x, int y, int *calcX, int *calcY)
{
  // calculate which block is next
  *calcX = x + ((q==0)?i:0) - ((q==1)?i:0);
  *calcY = y + ((q==2)?i:0) - ((q==3)?i:0);
  // check if next block is in world, if not break
  if((*calcX >= 0) && (*calcX < GRID_X) && (*calcY >= 0) && (*calcY < GRID_Y))
    return 1;
  else
    return 0;
}
