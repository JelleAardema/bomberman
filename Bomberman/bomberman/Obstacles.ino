void bombs(struct BOMB *bomb,Adafruit_ILI9341 *pen,struct DIMENSION screen){
  int i;
  for(i=0;i<MAXBOMBS;i++)
  {
   if(bomb[i].placed == 1)
   {
  uint16_t j = 25;
  bomb[i].fuse++;
    if(bomb[i].fuse > j){  
        bomb[i].placed = 2;
    }
     struct DIMENSION block;
       calcBlock(screen,&block,bomb[i].x,bomb[i].y);
        drawBlock(pen,block,4);
        //changeBlock(&screen,dimension,wrld,1,1,4);
    
   }
   if(bomb[i].placed ==2){
     struct DIMENSION block;
       calcBlock(screen,&block,bomb[i].x,bomb[i].y);
        drawBlock(pen,block,air);
        bomb[i].placed = 0;
        
   }
   
  }
}

void explosion(){
  
}
