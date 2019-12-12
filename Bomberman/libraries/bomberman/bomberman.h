// header file encodeData
#ifndef BOMBERMAN_h
#define BOMBERMAN_h

void bombermanSetup(Adafruit_ILI9341 *pen, int seed, int type);
void bombermanUpdate(Adafruit_ILI9341 *pen);
void endGame();

#endif
