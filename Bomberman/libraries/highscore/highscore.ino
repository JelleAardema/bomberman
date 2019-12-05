#include "highscore.h"

void setup() {
  Serial.begin(9600);
  
  uint16_t score = 360;
  placeHighscore(score);

  getHighscores();
}

void loop() {
  // put your main code here, to run repeatedly:

}
