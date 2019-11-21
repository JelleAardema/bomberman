#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>

// setup send
void sendIR(uint16_t data);
void sendBit();
void transmitDataSetup();
void timer2Init();
void timer0Init();

volatile uint16_t sendData = 0;
volatile int sendDataFlag = 0;
//volatile uint16_t incomingByte = 0;// for serial port 

// setup receive
void timer1Init();
void pinInit();
void convertBites();
void clearTimer1();

volatile uint16_t buf = 0;     	// buffer for recording the time between interrupts
volatile int bufFlag = 0; 		// mark if there is data coming in
volatile uint16_t data = 0; 	// the complete set of of bits recieved to form a byte
volatile int x = 0;				//steps to left when writing bit

// used pins
int sensorOutput = PORTD2;		// sensor pin2
int led = PORTD3;				// IR led pin3

// configure the time of interupt
// timeLow is the base and stands for a bit with a value of 0
// timeHigh is double the length of timeLow and has the bit value of 1
// timeBreak is three times the length of timeLow and is the minimum barrier to check if a set of bits is complete
#define timeLow 60
#define variation timeLow/3
#define timeHigh timeLow*2
#define timeBreak timeLow*3

int timer2Top = 52;         //36 = 56kHz; 52 = 38kHz. default 38kHz

// interrupts

ISR(INT0_vect){
    timer1Init();
    buf = TCNT1;
    TCNT1 = 0;
    bufFlag = 1;
}

ISR(TIMER1_OVF_vect){ // disable timer when it overflows
	clearTimer1();
	buf = timeBreak + 1;
}

ISR(TIMER0_COMPA_vect) {      //interrupt on TCNT0 = OCR0A
	sendBit();
}

// sendData

void sendIR(uint16_t data){
	if(!sendDataFlag) { 
		sendDataFlag = 1;
		sendData = data;
		TCCR0B |= (1 << CS01) | (1 << CS00);  //enable timer0
		sendBit();
	}else {
		Serial.println("busy");
	}
}

void sendBit(){
  TCCR2A ^= (1 << COM2B1);    //toggle output
  if(sendData){       //check if there is data
    if(sendData & 1){   //if the last bit of the data = 1
      OCR0A = timeHigh;
    }else{        //if last bit of data = 0
      OCR0A = timeLow;  
    }
  }else{
    if(OCR0A == timeBreak){   //after a breaktime disable timer0
      TCCR0B &= ~((1 << CS02) | (1 << CS01) | (1 << CS00));
      sendDataFlag = 0;
    }else{        //if no more data
      OCR0A = timeBreak;
    }
  }
  sendData = (sendData >> 1);   //shift data to right
}

//receiveData

void convertBites(){
  if(bufFlag){
    if((buf > (timeBreak - variation)) && (buf < (timeBreak + variation))){
      if(data){
        Serial.print("received: ");
        Serial.println(data);
        decodeMessage(data);
        data = 0;
        x = 0;
      }

    }
    if((buf > (timeHigh - variation)) && (buf < (timeHigh + variation))){
      data |= (1<<x);
      x++;
    }
    if((buf > (timeLow - variation)) && (buf < (timeLow + variation))){
      x++;
    }
    bufFlag = 0;
  }
}

// setup

void transmitDataSetup(){     //mode = 36 = 56kHz; mode = 52 = 38kHz.
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
  //OCR0A = timeBreak;        //make OCR2A the defined top
  TCNT0 = 0;          //set timer to 0;
}

void timer1Init(){
  TCCR1A = 0;
  TCCR1B = 0;
  TCCR1B |= (1<<CS11)| (1 << CS10);
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