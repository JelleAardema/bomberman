#include "highscore.h"

void setup() {
  Serial.begin(9600);
  
  uint16_t score = calculateScore(2, 21);

  placeHighscore(score);

  // Print highscores
  for(int i = 0; i < 5; i++) {
    Serial.println(highscores[i]);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
