#include "highscore.h"

void setup() {
  Serial.begin(9600);

  // Test code
  placeHighscore(1);
  placeHighscore(5);
  placeHighscore(4);
  placeHighscore(2);
  placeHighscore(3);

  for(int i = 0; i < 5; i++) {
    Serial.println(highscores[i]);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
