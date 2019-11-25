uint8_t stepper(enum AIM direction,uint8_t world[9][9],struct PLAYER *p1,struct DIMENSION dimension,Adafruit_ILI9341 *pen,struct BOMB *b1)
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
  if(direction == BOMB){
    changeBlock(&screen,dimension,wrld,p1->x,p1->y,4);
    
  }
  // check if move is posible
  if( ((X>=0)&&(X<=GRID_X)) && ((Y>=0)&&(Y<=GRID_Y)) && (!world[X][Y]) )
  {
    struct DIMENSION block;
    calcBlock(dimension,&block,p1->x,p1->y);
    drawBlock(pen,block,0);
    // change player cordinate to new cordinate
    p1->y = Y;
    p1->x = X;
    // tell that the move was succesful
    return 1;
  }

  // tell that the move was a failure
  return 0;
}

void drawPlayer(struct PLAYER p1, Adafruit_ILI9341 *pen,struct DIMENSION screen)
{
  struct DIMENSION block;
  calcBlock(screen,&block,p1.x,p1.y);
        drawBlock(pen,block,p1.color);
}
