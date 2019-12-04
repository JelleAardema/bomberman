#include <EEPROM.h>

uint16_t addr;

void setup() {
  Serial.begin(9600);
  
  uint16_t score = 7;

  placeHighscore(score);
  getHighscores();
}

void placeHighscore(uint16_t newScore) {

  addr = 256;
  
  // Loop through the 5 old highscores
  for(int i = 0; i < 5; i++) {

    uint16_t oldScore, lowerScore;
    EEPROM.get(addr, oldScore);

    if(newScore > oldScore) {
      // Loop through the scores that would be below the new high score
      for(int j = 0; j < 5 - i; j++) {

        // Move all the highscores 1 place down
        EEPROM.get(addr + 16 * j, lowerScore);
        EEPROM.put(addr + 16 + 16 * j, lowerScore);  
      }

      // Place the new highscore
      EEPROM.put(addr, newScore);
      break;
    }

    addr += 16;
  }
}

void getHighscores() {

  addr = 256;
  uint16_t score;
  
  for(int i = 0; i < 5; i++) {
    EEPROM.get(addr, score);
    Serial.println(score);
    addr += 16;
  }
}

void loop() { 
  
}
