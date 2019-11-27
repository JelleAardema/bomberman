// header file encodeData
#ifndef ENCODEDATA_h
#define ENCODEDATA_h

/*
Status		= 000
Level		= 001
Start		= 010
Connection	= 011
*/

// function encode
uint16_t encodeMovement(int x, int y, int lifes, int bombPlaced);
uint16_t encodeLevel(int seed, int type);
uint16_t encodeStart();
uint16_t encodeConnection(int host);

// function decode
int decodeMessageType(uint16_t message);
void decodeMovement(int *x, int *y, int *lifes, int *bombPlaced);
void decodeLevel(int *seed, int *type);
void decodeStart();
void decodeConnection(int *otherHost);

#endif
