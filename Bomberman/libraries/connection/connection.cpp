#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

#include <encodeData.h>
#include <ircc.h>

#include "connection.h"


// -----------------------------------------------------------------------------------------------------------------------
// setup
// -----------------------------------------------------------------------------------------------------------------------
void irccBegin(int host){
	transmitDataSetup(host);
}

// -----------------------------------------------------------------------------------------------------------------------
// handshake				type = 4			always first, also has initilize
// -----------------------------------------------------------------------------------------------------------------------
void startConnection(int host){
	int connection = 0;
	while(!connection){
		if(host){										// if your host send and search for other
			sendIRCC(encodeConnection(host));
		}
		int receiveByte = receiveIRCC(); 
		if(receiveByte){
			if(decodeMessageType(receiveByte) == 4){
				int otherHost;
				decodeConnection(&otherHost);
				if(otherHost != host){
					connection = 1;
				}
			}
		}
		_delay_ms(1);									// if removed it breaks
	}
	
	if(!host){		// if your not host send conformation
		sendIRCC(encodeConnection(host));
	}
	
	//connected
}

// -----------------------------------------------------------------------------------------------------------------------
// level					type = 2
// -----------------------------------------------------------------------------------------------------------------------
void sendLevel(int seed, int type){
	if(type){
		sendIRCC(encodeLevel(seed,type));	
	}else{
		sendIRCC(encodeLevel(TCNT2, type));
	}
}

void receiveLevel(int *seed, int *type){
	int level = 0;
	while(!level){
		int receiveByte = receiveIRCC(); 
		if(receiveByte){
			if(decodeMessageType(receiveByte) == 2){
				decodeLevel(seed,type);
				level = 1;
			}
		}
	}
}

// -----------------------------------------------------------------------------------------------------------------------
// confirm level loaded		type = 3
// -----------------------------------------------------------------------------------------------------------------------
void confirmLoad(int host){
	int loaded = 0;
	while(!loaded){
		if(host){										// if your host send and search for loaded
			sendIRCC(encodeStart());
		}
		int receiveByte = receiveIRCC(); 
		if(receiveByte){
			if(decodeMessageType(receiveByte) == 3){
				loaded = 1;
			}
		}
		_delay_ms(1);									// if removed it breaks
	}
	
	if(!host){		// if your not host send conformation
		sendIRCC(encodeStart());
	}
}

// -----------------------------------------------------------------------------------------------------------------------
// player status			type = 1
// -----------------------------------------------------------------------------------------------------------------------
void sendPlayerStatus(int xPos, int yPos, int lives, int bombPlaced){
	sendIRCC(encodeStatus(xPos, yPos, lives, bombPlaced));
}

void receivePlayerStatus(int *xPos, int *yPos, int *lives, int *bombPlaced){
	int receiveByte = receiveIRCC(); 
	if(receiveByte){
		if(decodeMessageType(receiveByte) == 1){
			decodeStatus(xPos, yPos, lives, bombPlaced);
		}
	}
}