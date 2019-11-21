#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>

// Host = 0 = 56 kHz, Host = 1 = 38 kHz
#define host 0

// setup
void decodeMessage(uint16_t data);
uint16_t encodeMovement(int x, int y, int lifes, int bombPlaced);
uint16_t encodeLevel(int seed);
uint16_t encodeConnection();
uint16_t encodeStart();

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

uint16_t encodeConnection() {
  uint16_t data = 0;

  data += host & 0b1;

  data = data << 3;
  data += 0b011;

  return data;
}

// decode

void decodeMessage(uint16_t message) {
  int type = message & 0b111;
  message = message >> 3;
  
    Serial.print("t: ");
    Serial.println(type,BIN);


  // Movement
  if(type == 0b000) {
    int xPlayer2 = message &      0b1111;
    message = message >> 4;    
    int yPlayer2 = message &      0b1111;
    message = message >> 4;
    int lifesPlayer2 = message &  0b1111;
    message = message >> 4;
    int bombPlaced = message &    0b1;

    Serial.print("x: ");
    Serial.println(xPlayer2,BIN);
    Serial.print("y: ");
    Serial.println(yPlayer2,BIN);
    Serial.print("l: ");
    Serial.println(lifesPlayer2,BIN);
    Serial.print("b: ");
    Serial.println(bombPlaced,BIN);
  }

  // Level
  if(type == 0b001) {
     uint16_t seed = message &    0b1111111111111;
  }

  // Start game
  if(type == 0b010) {
    
  }

  // Connection
  if(type == 0b011) {
    int otherHost = message & 0b1;
    
    // if host == 1 means I'm the host.
    Serial.print("h: ");
    Serial.println(otherHost, BIN);         
  }
}