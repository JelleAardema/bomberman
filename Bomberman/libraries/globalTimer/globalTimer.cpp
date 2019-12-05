#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>

#include "globalTimer.h"

int gameUpdateFlag = 0;
int microTick = 0;
int maxMicroTick = 0;
int subTick = 0;

#define maxSubTick 255

// -----------------------------------------------------------------------------------------------------------------------
// timer2interrupts
// -----------------------------------------------------------------------------------------------------------------------

int gameUpdate(){
	if(gameUpdateFlag){
		gameUpdateFlag = 0;
		return 1;
	}
	return 0;
}


void timer2InterruptInit(int host) {
	if(host) {				//0 = 36 = 56kHz = toWhite; 1 = 52 = 38kHz = toBlack
		//timer2Top = 52;
		maxMicroTick = 173;		//9*52 = 468
	}else{
		//timer2Top = 36;
		maxMicroTick = 248; 	//13*36 = 468
	}  

	//TCCR2A |= (1 << WGM21) | (1 << WGM20);		//WGM = 111 = fast PWM, top OCRA
	//TCCR2B |= (1 << WGM22) | (1 << CS21);			//CS = 101 = prescaler 8
	//OCR2A = timer2Top;        					//make OCR2A the defined top
	//OCR2B = (OCR2A/2);        					//OCR2B is half of OCR2A, 50% duty-cycle
	//TCNT2 = 0;
	
	TIMSK2 |= (1<<OCIE2A);    	//enable interrupts on compare OCRA
	
}

ISR(TIMER2_COMPA_vect) {      						//interrupt on TCNT2 = OCR2A
	microTick++;
	if(microTick > maxMicroTick){
		microTick = 0;
    subTick++;
	}
  if(subTick > maxSubTick){
    subTick = 0;
    gameUpdateFlag = 1;
  }
}
