//test file for IRCC and encodeData

#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>

#include <encodeData.h>
#include <ircc.h>
#include <connection.h>


volatile uint16_t incomingByte = 0;// for serial port

int x1 = 6;
int y1 = 7;
int l1 = 5;
int b1 = 0;

int x2 = 0;
int y2 = 0;
int l2 = 0;
int b2 = 0;

int seed = 100;
int type = 1;

//wit = 1 = 38kHz
//black = 0 = 56kHz
#define host 1

int main() {
	//setup
	Serial.begin(9600);     //temp; to start serial monitor
	Serial.println("Loaded");
 
  // SEARCHING FOR OTHER ARDUINO
  startConnection(host);
  Serial.println("Connected");
  _delay_ms(1000);
  
  // SEND SEED
  sendLevel(seed, type);
  Serial.println("Send level");

  // LOADING LEVEL
  confirmLoad(host);
  Serial.println("Level Loaded"); 
  
  // SEARCHING PLAYER STATUS
  while(1){
      sendPlayerStatus(x1, y1, l1, b1);
      Serial.println("Send status"); 
      _delay_ms(500);
      receivePlayerStatus(&x2, &y2, &l2, &b2);
      Serial.print("x2:"); 
      Serial.print(x2);
      Serial.print("  y2:"); 
      Serial.print(y2);
      Serial.print("  l2:"); 
      Serial.print(l2);
      Serial.print("  b2:"); 
      Serial.println(b2);
      _delay_ms(500);
  }
  return 0;
}
