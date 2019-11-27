//test file for IRCC and encodeData

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

#include <connection.h>


volatile uint16_t incomingByte = 0;// for serial port
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
#define host 1

int main() {
  //setup
  Serial.begin(9600);     //temp; to start serial monitor
  Serial.println("Loaded");
  // SEARCHING FOR OTHER ARDUINO

  startConnection(host);
  Serial.println("connected"); 

  // SEARCHING LEVEL
  //while(!receiveLevel(&seed, &type){
  //}

  // SEARCHING PLAYER STATUS
  // if(receivePlayerStatus(&x2, &y2, &l2, &b2){
  // //update player
  // }
  while(1){
    
  }
  return 0;
}
