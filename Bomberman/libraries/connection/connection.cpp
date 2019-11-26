#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

#include <encodeData.h>
#include <ircc.h>

#include "connection.h"

int connection = 0;
uint16_t receiveByte;

void startConnection(int host){
	transmitDataSetup(host);
	while(!connection){
		if(host){										// if your host send and search for other
			sendIRCC(encodeConnection(host));
		}
		receiveByte = receiveIRCC(); 
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

void sendLevel(int seed, int type){
	sendIRCC(encodeLevel(seed,type);
}

void receiveLevel(int *seed, int *type){
	receiveByte = receiveIRCC(); 
	if(receiveByte){
		if(decodeMessageType(receiveByte) == 2){
			decodeLevel(seed,type);
		}
	}
}