#include <sprites.h>
int x,y,i;

void setup() {
  // put your setup code here, to run once:
  spriteInit();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  while(i < 2){
    x += 20;
    player(x,y);
    x += 20;
    tile(x,y);
    x += 20;
    box(x,y);
    x += 20;
    bomb(x,y);
    x += 20;
    explosion(x,y);
    i++; 
  }
  x = 0;
  y+= 20;  
  i = 0;
  
}
