void bombs(struct BOMB *bomb,Adafruit_ILI9341 *pen,struct DIMENSION screen){
  int i;
  for(i=0;i<MAXBOMBS;i++)
  {
   if(bomb[i].placed == 1)
   {
  uint16_t j = 25;
  bomb[i].fuse++;
    if(bomb[i].fuse > j){
      //start explosion 
      
       struct DIMENSION block;
       calcBlock(screen,&block,bomb[i].x,bomb[i].y);
        drawBlock(pen,block,5);
        bomb[i].placed = 0;
    }else{
       
   
    }
    
   }
   if(bomb[i].placed == 0){
     struct DIMENSION block;
       calcBlock(screen,&block,bomb[i].x,bomb[i].y);
        drawBlock(pen,block,3);
        
   }
   
  }
}

void explosion(){
  
}
