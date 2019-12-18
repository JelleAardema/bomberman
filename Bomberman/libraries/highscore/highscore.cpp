#include <EEPROM.h>
#include "highscore.h"
#include <showInfo.h>

uint16_t addr;
uint16_t currentScore = 0;
int highscores[5];

// Values used to calculate the score
#define destroyTile 5
#define lifeLeft 200

void resetScore() {
  currentScore = 0;
}

void destroyTileScore() {
	currentScore += 10;
}

// Adds score for every life left and tile that is destroyed
uint16_t calculateScore(int lifes) {
	if(lifes < 10){
		currentScore += lifes * lifeLeft;
	}
	return currentScore;
}

uint16_t getCurrentScore() {
	return currentScore;
}

int * getHighscoreList() {
	return highscores;
}

// Places highscores in highscores array
void updateHighscoreList() {

	addr = 256;
	uint16_t score;

	// Get highscores from EEPROM and put it in the array
		for(int i = 0; i < 5; i++) {
		EEPROM.get(addr, score);
		highscores[i] = score;
		addr += 16;
	}
}

// places a new highscore
void placeHighscore(uint16_t newScore) {

	addr = 256;
  
	// Loop through the 5 old highscores
	for(int i = 0; i < 5; i++) {
	
		uint16_t oldScore, previousScore, tempScore;
		EEPROM.get(addr, oldScore);
	
		if(newScore > oldScore) {
		// Loop through the scores that would be below the new high score
		
			for(int j = 0; j < 6 - i; j++) {
				// Move all the highscores 1 place down and remember the old score
				EEPROM.get(addr + 16 + 16 * j, tempScore);
				EEPROM.put(addr + 16 + 16 * j, oldScore);
				oldScore = tempScore;  
			}

			// Place the new highscore
			EEPROM.put(addr, newScore);
	
			// Stop for loop so it doesn't overwrite
			break;
		}

		// Move 16 steps down the address
		addr += 16;
	}
	// Refresh list
	updateHighscoreList();
	resetScore();
}
