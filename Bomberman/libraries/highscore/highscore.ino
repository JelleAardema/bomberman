#include "highscore.h"

void setup() {
  Serial.begin(9600);

  // Place 5 scores in the EEPROM
  placeHighscore(56);
  placeHighscore(34);
  placeHighscore(4);
  placeHighscore(3);
  placeHighscore(70);

  // Print highscores
  for(int i = 0; i < 5; i++) {
    Serial.println(highscores[i]);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
