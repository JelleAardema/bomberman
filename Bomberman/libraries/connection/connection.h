// header file connection
#ifndef CONNECTION_h
#define CONNECTION_h

// Setup
void irccBegin(int host);

// player status			type = 1
void sendPlayerStatus(uint8_t xPos, uint8_t yPos, uint8_t lives, uint8_t bombPlaced);
void receivePlayerStatus(uint8_t *xPos, uint8_t *yPos, uint8_t *lives, uint8_t *bombPlaced);

// level					type = 2
void sendLevel(int seed, int type);
void receiveLevel(int *seed, int *type);

// confirm level loaded		type = 3
void confirmLoad(int host);

// handshake				type = 4			always first, also has initilize
void startConnection(int host);

#endif

