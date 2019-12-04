#include <avr/io.h>
#include <stdint.h>
#include "globalTimer.h"
#include <connection.h>

//wit = 1 = 38kHz
//black = 0 = 56kHz
#define host 0
uint32_t loops = 0;

int main() {
	//setup
	Serial.begin(9600);     //temp; to start serial monitor
	timer2InterruptInit(host);
	irccBegin(host);
	Serial.println("Loaded");
	
	
	while(1) {
		if(gameUpdate()){
      loops++;
			Serial.println(loops);
		}
    _delay_ms(1);
	}

 
  return 0;
}
