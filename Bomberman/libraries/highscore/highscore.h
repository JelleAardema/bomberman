#ifndef HIGHSCORE_h
#define HIGHSCORE_h

int highscores[5];

uint16_t calculateScore(int lifes, int amountDestroyed);
void placeHighscore(uint16_t newScore);
void updateHighscoreList();

#endif
