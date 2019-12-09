#ifndef LEVEL_H_
#define LEVEL_H_



void genWorld(uint8_t world[GRID_X][GRID_Y],int seed);
void setWall(uint8_t world[GRID_X][GRID_Y],int x, int y, int roti, int size);
int findBlock(uint8_t world[GRID_X][GRID_Y],uint8_t block, int x, int y);

void loadWorld(uint8_t world[GRID_X][GRID_Y],int level);
void copyWorld(uint8_t out[GRID_X][GRID_Y],uint8_t in[GRID_X][GRID_Y]);
// types



#endif
