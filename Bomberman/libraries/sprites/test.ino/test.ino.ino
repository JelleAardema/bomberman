#include <sprites.h>
int x,y,i;

void setup() {
  // put your setup code here, to run once:
  spriteInit();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  while(i < 2){
    x += 24;
    player(x,y);
    x += 24;
    tile(x,y);
    x += 24;
    box(x,y);
    x += 24;
    bomb(x,y);
    x += 24;
    explosion(x,y);
    x += 24;
    wall(x,y);
    i++; 
  }
  x = 0;
  y+= 24;  
  i = 0;
  
}
