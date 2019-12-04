#include <EEPROM.h>

uint16_t addr = 256;

void setup() {
  Serial.begin(9600);
  
  uint16_t score = 300;
  uint16_t getScore = 0;

  placeHighscore(score);
}

void placeHighscore(uint16_t newScore) {
  
  for(int i = 0; i < 5; i++) {
    EEPROM.put(addr, newScore);

    uint16_t currentScore = 0;
    EEPROM.get(addr, currentScore);

    Serial.println(currentScore);
    
    addr += 16;
  }
}

void loop() { 
  
}
