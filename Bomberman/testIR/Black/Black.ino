//test file for IRCC and encodeData

#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>

#include <encodeData.h>
#include <ircc.h>


volatile uint16_t incomingByte = 0;// for serial port 
volatile uint16_t receiveByte = 0;
int type = 0;

int x1 = 6;
int y1 = 7;
int l1 = 5;
int b1 = 0;

int x2 = 0;
int y2 = 0;
int l2 = 0;
int b2 = 0;

//wit = 1 = 38kHz
//black = 0 = 56kHz
#define host 0

int main() {
	//setup
	Serial.begin(9600);     //temp; to start serial monitor
	transmitDataSetup(host);
  Serial.println("Loaded");
  
	while(1) {
    if (Serial.available() > 0) {
      incomingByte = Serial.read();
      sendIRCC(encodeMovement(x1,y1,l1,b1));
    }
		receiveByte = receiveIRCC();
		
		if(receiveByte){
			type = decodeMessageType(receiveByte);
			
			Serial.print("type: ");
			Serial.println(type,BIN);
			
			decodeMovement(&x2,&y2,&l2,&b2);
			
			Serial.print("x2:  ");
			Serial.print(x2,DEC);
			Serial.print("   ");
			Serial.print("y2:  ");
			Serial.print(y2,DEC);
			Serial.print("   ");
			Serial.print("l2:  ");
			Serial.print(l2,DEC);
			Serial.print("   ");
			Serial.print("b2:  ");
			Serial.println(b2,DEC);
		}
	}
  return 0;
}
