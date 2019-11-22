#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>


#include "encodeData.h"


volatile uint16_t incomingByte = 0;// for serial port 

//wit = 1 = 38kHz
//black = 0 = 56kHz
#define host 0

int x = 0;
int y = 0;
int l = 0;
int b = 0;



int main() {
	//setup
	Serial.begin(9600);     //temp; to start serial monitor 
  
	while(1) {
		Serial.print("type:	");
		Serial.println(decodeMessageType(6440),BIN);
		decodeMovement(&x,&y,&l,&b);
		Serial.print("x:  ");
		Serial.print(x,BIN);
    Serial.print("   ");
		Serial.print("y:  ");
		Serial.print(y,BIN);
    Serial.print("   ");
		Serial.print("l:  ");
		Serial.print(l,BIN);
    Serial.print("   ");
		Serial.print("b:	");
		Serial.print(b,BIN);
    Serial.print("   ");
	}
  return 0;
}
