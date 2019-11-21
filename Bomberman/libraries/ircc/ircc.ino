#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>


#include "ircc.h"


volatile uint16_t incomingByte = 0;// for serial port 
volatile uint16_t receiveByte = 0;

#define host 0  //host = 1 = 38kHz; host = 0 = 56kHz

int main() {
	//setup
	Serial.begin(9600);     //temp; to start serial monitor
	transmitDataSetup(host);  
  
	while(1) {    
		if (Serial.available() > 0) {
			// read the incoming byte:
			incomingByte = Serial.read();
		
			// say what you got:
			Serial.print("send:    ");
			Serial.print(incomingByte, DEC);
			Serial.print("  ");
			Serial.println(incomingByte, BIN);
			sendIR(incomingByte);
		}
	
		receiveByte = receiveIR();
	
		if(receiveByte){
			Serial.print("receive: ");
			Serial.print(receiveByte, DEC);
			Serial.print("  ");
			Serial.println(receiveByte, BIN);
		}
	}
  return 0;
}
