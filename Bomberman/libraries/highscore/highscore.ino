#include "highscore.h"

void setup() {
  Serial.begin(9600);

  tileDestroyed();
  tileDestroyed();
  tileDestroyed();
  uint16_t score = getCurrentScore();

  placeHighscore(score);

  // Print highscores
  for(int i = 0; i < 5; i++) {
    Serial.println(highscores[i]);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
