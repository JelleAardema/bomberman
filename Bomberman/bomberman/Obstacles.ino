void bombs(struct BOMB *b1,Adafruit_ILI9341 *pen,struct DIMENSION dimension){
  int i;
  for(i=0;i<MAXBOMBS;i++)
  {
   if(b1[i].placed == 1)
   {
  uint16_t j = 25;
  b1[i].fuse++;
    if(b1[i].fuse > j){  
        b1[i].placed = 2;
    }
     struct DIMENSION block;
       calcBlock(dimension,&block,b1[i].x,b1[i].y);
        drawBlock(pen,block,bomb);

        changeBlock(&screen,dimension,wrld,b1[i].x,b1[i].y,bomb);
     
    
   }
   if(b1[i].placed ==2){
     struct DIMENSION block;
       calcBlock(dimension,&block,b1[i].x,b1[i].y);
        drawBlock(pen,block,air);
        b1[i].placed = 0;
        changeBlock(&screen,dimension,wrld,b1[i].x,b1[i].y,air);
        
   }
   
  }
}

void explosion(){
  
}
