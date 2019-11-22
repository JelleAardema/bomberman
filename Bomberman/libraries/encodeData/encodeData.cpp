#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>

uint16_t message = 0;

// encode

uint16_t encodeMovement(int x, int y, int lifes, int bombPlaced) {
  uint16_t data = 0;
  data += bombPlaced & 0b1;
  
  data = data << 4;
  data += lifes & 0b1111;

  data = data << 4;
  data += y & 0b1111;
  
  data = data << 4;  
  data += x & 0b1111;

  data = data << 3;
  data += 0b000;

  return data;
}

uint16_t encodeLevel(int seed) {
    uint16_t data = 0;

    data += seed & 0b11111111;
    
    data = data << 3;
    data += 0b001;
      
    return data;
}

uint16_t encodeStart() {
  uint16_t data = 0;
  data = 0b010;

  return data;
}

uint16_t encodeConnection(int host) {
  uint16_t data = 0;

  data += host & 0b1;

  data = data << 3;
  data += 0b011;

  return data;
}

// decode

int decodeMessageType(uint16_t fullMessage){
	message = fullMessage >> 3;
	return fullMessage & 0b111;
}


void decodeMovement(int *x, int *y, int *lifes, int *bombPlaced){
	*x = message &      		0b1111;
	
    message = message >> 4;    		//remove x bits
    *y = message &      		0b1111;
	
    message = message >> 4;			//remove y bits
    *lifes = message &  		0b1111;
	
    message = message >> 4;			//remove life bits
    *bombPlaced = message &		0b1;
}

void decodeLevel(int *seed){
    *seed = message &    0b1111111111111;
}

void decodeStart(){
}

void decodeConnection(int *otherHost){
    *otherHost = message & 0b1;  
}
