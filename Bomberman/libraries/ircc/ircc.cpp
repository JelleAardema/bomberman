#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include "ircc.h"

volatile uint16_t sendData = 0;
volatile int sendDataFlag = 0;

volatile uint16_t buf = 0;     			// buffer for recording the time between interrupts
volatile int receiveDataFlag = 0; 		// mark if there the data is complete
volatile uint16_t receiveData = 0; 		// the complete set of of bits recieved
volatile int x = 0;						// steps to left when writing bit

// used pins
int sensorOutput = PORTD2;		// sensor pin2
int led = PORTD3;				// IR led pin3

int timer2Top = 52;         //36 = 56kHz; 52 = 38kHz. default 38kHz

// interrupts

ISR(INT0_vect){
	if(!receiveDataFlag){		//only write data when the last receiveData was read
		buf = TCNT1;			//record time to last change
		timer1Init();			//start clock			
		receiveBit();			//check bit and add to receiveBit
	}
}

ISR(TIMER1_OVF_vect){ 		// disable timer when it overflows
	clearTimer1();
	buf = 0;
}

ISR(TIMER0_COMPA_vect) {      //interrupt on TCNT0 = OCR0A
	sendBit();
}

// sendData

void sendIRCC(uint16_t data){
	if(!sendDataFlag) { 
		sendDataFlag = 1;
		sendData = data;
		TCCR0B |= (1 << CS01) | (1 << CS00);  	//enable timer0
		sendBit();				//should be send start bit
	}
}

void sendBit(){
  TCCR2A ^= (1 << COM2B1);    					//toggle output
  if(sendData){       							//check if there is data
    if(sendData & 1){   						//if the last bit of the data = 1
      OCR0A = timeHigh;
    }else{        								//if last bit of data = 0
      OCR0A = timeLow;  
    }
  }else{
    if(OCR0A == timeStop){   					//after a timeStop disable timer0
      TCCR0B &= ~((1 << CS02) | (1 << CS01) | (1 << CS00));
      sendDataFlag = 0;
    }else{        								//if no more data
      OCR0A = timeStop;
    }
  }
  sendData = (sendData >> 1);   				//shift data to right
}

//receiveData

uint16_t receiveIRCC(){
	if(receiveDataFlag){
		int tempData = receiveData;
		receiveData = 0;
		receiveDataFlag = 0;
		x = 0;
		return tempData;
	}
	return 0;
}

void receiveBit(){	
    if((buf > (timeStop - variation)) && (buf < (timeStop + variation))){
		receiveDataFlag = 1;
    }
    if((buf > (timeHigh - variation)) && (buf < (timeHigh + variation))){
		receiveData |= (1<<x);
		x++;
    }
    if((buf > (timeLow - variation)) && (buf < (timeLow + variation))){
		x++;
    }
}

// setup

void transmitDataSetup(int host){     //mode = 36 = 56kHz; mode = 52 = 38kHz.

  
  if(host) {
    timer2Top = 52;
  }

  else {
    timer2Top = 36;
  }  
  timer0Init();
  timer1Init();
  timer2Init();
  pinInit();
  sei();
}

void pinInit(){
  DDRD &= ~(1 << sensorOutput);     //set sensorOutput to INPUT
  PORTD |= (1 << sensorOutput);     //set sensorOutput to pull-up
  
  EIMSK |= (1 << INT0);           	//enable INT0 interrupts
  EICRA = (EICRA |(1 << ISC00))   	//set ISC00 to 1,
  & (~(1 << ISC01));              	//set ISC01 to 0, total interupt on change

  TIMSK1 |= (1<<TOIE1);
}

// all timer initializes and commands

void timer0Init() {
  TCCR0A = 0;             //set entire TCCR0A register to 0
  TCCR0B = 0;             //set entire TCCR0B register to 0
  
  TCCR0A |= (1 << WGM01);       //WGM = 010 = Clear to Compare, top OCRA
  //TCCR0B |= (1 << CS02) | (1 << CS00);    //CS = 101 = prescaler 1024
  TIMSK0 |= (1<<OCIE0A);        //enable interrupts on compare OCRA
  //OCR0A = timeStop;        //make OCR2A the defined top
  TCNT0 = 0;          //set timer to 0;
}

void timer1Init(){
  TCCR1A = 0;
  TCCR1B = 0;
  TCCR1B |= (1<<CS11)| (1 << CS10);
  TCNT1 = 0;	
}

void clearTimer1(){
  TCCR1A = 0;
  TCCR1B = 0;
}

void timer2Init() {
  TCCR2A = 0;             //set entire TCCR2A register to 0
  TCCR2B = 0;             //set entire TCCR2B register to 0
  
  DDRD |= (1 << led);        //set pin 3 output
  TCCR2A |= (1 << WGM21) | (1 << WGM20);    //WGM = 111 = fast PWM, top OCRA
  TCCR2B |= (1 << WGM22) | (1 << CS21);   //CS = 101 = prescaler 8
  OCR2A = timer2Top;        //make OCR2A the defined top
  OCR2B = (OCR2A/2);        //OCR2B is half of OCR2A, 50% duty-cycle
  TCNT2 = 0;
}