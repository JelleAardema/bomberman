// header file connection
#ifndef CONNECTION_h
#define CONNECTION_h

// player status			type = 1
void sendPlayerStatus(int xPos, int yPos, int lives, int bombPlaced);
void receivePlayerStatus(int *xPos, int *yPos, int *lives, int *bombPlaced);

// level					type = 2
void sendLevel(int seed, int type);
void receiveLevel(int *seed, int *type);

// confirm level loaded		type = 3
void confirmLoad(int host);

// handshake				type = 4			always first, also has initilize
void startConnection(int host);

#endif

