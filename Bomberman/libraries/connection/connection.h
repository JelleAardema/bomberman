// header file connection
#ifndef CONNECTION_h
#define CONNECTION_h

void startConnection(int host);
void sendLevel(int seed, int type);
void receiveLevel(int *seed, int *type);


#endif
