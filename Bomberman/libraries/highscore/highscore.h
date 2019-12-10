#ifndef HIGHSCORE_h
#define HIGHSCORE_h

uint16_t currentScore;
int highscores[5];

uint16_t getCurrentScore();
void tileDestroyed();
void playerKilled();
void placeHighscore(uint16_t newScore);
void updateHighscoreList();

#endif
