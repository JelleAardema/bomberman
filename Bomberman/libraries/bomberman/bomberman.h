// header file encodeData
#ifndef BOMBERMAN_h
#define BOMBERMAN_h

void bombermanSetup(Adafruit_ILI9341 *pen, int seed, int type, int host);
void bombermanUpdate(Adafruit_ILI9341 *pen);
int checkEndGame();
uint8_t getPlayer1Life();
uint8_t getPlayer2Life();
void unsetBomb();

#endif
