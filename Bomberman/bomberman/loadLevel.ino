// load a level
void loadWorld(uint8_t world[GRID_X][GRID_Y],int level)
{
  // ---------- level data
  // level 1
  const uint8_t level1[GRID_X][GRID_Y]={
      {1,1,1,1,1,1,1,1,1},
      {1,0,0,0,0,0,0,0,1},
      {1,0,1,2,1,0,1,0,1},
      {1,0,0,0,0,0,0,0,1},
      {1,0,1,2,1,0,1,0,1},
      {1,0,0,0,2,0,0,0,1},
      {1,0,1,0,1,0,2,0,1},
      {1,0,0,2,0,0,0,0,1},
      {1,1,1,1,1,1,1,1,1}};

  // level 2
  const uint8_t level2[GRID_X][GRID_Y]={
      {1,1,1,1,1,1,1,1,1},
      {1,0,0,0,0,0,0,0,1},
      {1,0,1,2,1,0,1,0,1},
      {1,0,0,0,0,2,0,0,1},
      {1,0,1,0,1,0,1,0,1},
      {1,0,0,2,0,0,0,0,1},
      {1,0,1,0,1,2,1,0,1},
      {1,0,0,0,0,0,0,0,1},
      {1,1,1,1,1,1,1,1,1}};
  // level 3
  const uint8_t level3[GRID_X][GRID_Y]={
      {1,1,1,1,1,1,1,1,1},
      {1,0,0,0,0,0,0,0,1},
      {1,0,1,0,1,0,1,0,1},
      {1,0,2,0,0,0,0,0,1},
      {1,0,1,0,1,1,1,0,1},
      {1,0,0,0,0,2,0,0,1},
      {1,0,1,0,1,1,1,0,1},
      {1,0,2,0,0,0,0,0,1},
      {1,1,1,1,1,1,1,1,1}};
  // level 4
  const uint8_t level4[GRID_X][GRID_Y]={
      {1,1,1,1,1,1,1,1,1},
      {1,0,0,0,0,0,0,0,1},
      {1,0,1,2,1,0,1,0,1},
      {1,0,0,0,0,0,0,0,1},
      {1,0,1,2,1,0,1,0,1},
      {1,0,0,0,0,2,0,0,1},
      {1,0,1,2,1,0,1,0,1},
      {1,0,0,0,0,0,0,0,1},
      {1,1,1,1,1,1,1,1,1}};
  // level 5
  const uint8_t level5[GRID_X][GRID_Y]={
      {1,1,1,1,1,1,1,1,1},
      {1,0,0,0,0,0,0,0,1},
      {1,0,1,0,1,0,1,0,1},
      {1,0,0,2,0,0,0,0,1},
      {1,0,1,0,1,0,1,0,1},
      {1,0,0,0,0,0,0,0,1},
      {1,0,1,0,1,0,1,0,1},
      {1,0,0,0,0,0,0,0,1},
      {1,1,1,1,1,1,1,1,1}};

  // ------ load level
  // deside wich level must be loaded and load
  switch(level)
  {
    case 1:
      copyWorld(world,level1);
      break;
    case 2:
      copyWorld(world,level2);
      break;
    case 3:
      copyWorld(world,level3);
      break;
    case 4:
      copyWorld(world,level4);
      break;
    case 5:
      copyWorld(world,level5);
      break;
  }
}

// copy world arraw to another world array
void copyWorld(uint8_t out[GRID_X][GRID_Y],uint8_t in[GRID_X][GRID_Y])
{
  int x,y;
    for(x=0; x<GRID_X; x++)
    {
      for(y=0; y<GRID_Y; y++)
      {
        out[x][y] = in[x][y];
      }
    }
}
