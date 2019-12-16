#ifndef HIGHSCORE_h
#define HIGHSCORE_h

void resetScore();
int * getHighscoreList();
void destroyTileScore();
uint16_t calculateScore(int lifes);
uint16_t getCurrentScore();
void placeHighscore(uint16_t newScore);
void updateHighscoreList();

#endif
