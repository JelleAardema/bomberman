// generate world
void genWorld(uint8_t world[GRID_X][GRID_Y],int seed)
{
  int x,y,count;
        // init rand
        srand(seed);

        // fill world with ear
        for(x=0; x<GRID_X; x++)
        {
                for(y=0; y<GRID_Y; y++)
                {
                        world[x][y] = air;
                }
        }
        // place destructable blacks
        for(x=0; x<GRID_X; x++)
        {
                for(y=0; y<GRID_Y; y++)
                {
                        if( (rand()%100) < 35)
                                world[x][y] = destruct;
                }
        }
        // place random walls
        count = 0;
        for(x=0; x<GRID_X; x++)
        {
                for(y=0; y<GRID_Y; y++)
                {
                        if( !findBlock(world,wall,x,y))
                                setWall(world,x,y,rand()%2,rand()%5);
                }
        }
        // place spawn points
        for(x=0; x<2; x++)
        {
                for(y=0; y<2; y++)
                {
                        world[x][y]=air;
                }
        }
        for(x=GRID_X-2; x<GRID_X; x++)
        {
                for(y=GRID_Y-2; y<GRID_Y; y++)
                {
                        world[x][y]=air;
                }
        }

}

// find a block
int findBlock(uint8_t world[GRID_X][GRID_Y],uint8_t block, int x, int y)
{
  int p1x,p1y,p2x,p2y,i,q;
        // setup
        p1x=x;
        p2x=x;
        p1y=y;
        p2y=y;

        // calculate area
        if( (x>0)) p1x--;
        if( (y>0)) p1y--;
        if( (x < (GRID_X-1)) ) p2x++;
        if( (y < (GRID_Y-1)) ) p2y++;

        // find block in that area
        for(i=p1x; i<=p2x; i++)
        {
                for(q=p1y; q<=p2y; q++)
                {
                        // if block found stop search
                        if(world[i][q] == block)
                                return 1;
                }
        }
        return 0;
}

// set a wall
void setWall(uint8_t world[GRID_X][GRID_Y],int x, int y, int rot,int size)
{
  int i;
        for(i=0; (i<size) && (x<GRID_X) && (y<GRID_Y); i++)
        {
                // set wall
                world[x][y] = wall;

                // go right or down
                switch(rot)
                {
                        case 0:
                                x++;
                                break;
                        case 1:
                                y++;
                                break;
                        default:
                                y++;
                }

                // stop drawing wall if found a wall
                if((rot==0) && (world[x+1][y] == wall)) break;
                if((rot<=1) && (world[x][y+1] == wall)) break;
        }
}
