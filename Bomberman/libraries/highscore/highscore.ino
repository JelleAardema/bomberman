#include "highscore.h"

void setup() {
  Serial.begin(9600);
  
  uint16_t score = 4;
  placeHighscore(score);
  
  score = 2;
  placeHighscore(score);

  score = 1;
  placeHighscore(score);
  
  score = 3;
  placeHighscore(score);

  score = 5;
  placeHighscore(score);

  getHighscores();

  for(int i = 0; i < 5; i++) {
    Serial.println(highscores[i]);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
