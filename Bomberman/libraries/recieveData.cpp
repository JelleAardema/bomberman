#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>

int button = PORTD2;
int led = PORTD3;
//volatile int count = 0;
volatile int buf = 0;     // buffer for recording the time between interrupts
volatile int bufFlag = 0; // mark if there is data coming in
volatile int breaker = 0; // mark if the counter for the interupts has overflown so it can be disabled
volatile uint8_t data = 0; // the complete set of of bits recieved to form a byte
volatile int x = 0;
void clearTimer1();
void setupTimer1();
void irSetup();
void convertBites();
// configure the time of interupt
// timeLow is the base and stands for a bit with a value of 0
// timeHigh is double the length of timeLow and has the bit value of 1
// timeBreak is three times the length of timeLow and is the minimum barrier to check if a set of bits is complete
#define timeLow 50
#define variation 5
#define timeHigh timeLow*2
#define timeBreak timeLow*3

ISR(INT0_vect){
    setupTimer1();
    buf = TCNT1;
    if (breaker){  // set the buffer to end so it can be formed to a byte
      buf = timeBreak + 1;
      breaker = 0;
    }
    TCNT1 = 0;
    bufFlag = 1;
   // Serial.println(buf);
}

ISR(TIMER1_OVF_vect){ // disable timer when it overflows
  clearTimer1();
  breaker = 1;
}

void clearTimer1(){
  TCCR1A = 0;
  TCCR1B = 0;
}
void setupTimer1(){
  TCCR1A = 0;
  TCCR1B = 0;
  TCCR1B |= (1<<CS12)|(1<<CS10);
}

void irSetup(){
  cli();                          //disable global interrupts
  DDRD &= ~(1 << button);         //set button to INPUT
  DDRD |= (1<<led);               //set led to output;
  PORTD |= (1 << button);         //set button to pull-up

  EIMSK |= (1 << INT0);           //enable INT0 interrupts
  EICRA = (EICRA |(1 << ISC00))   //set ISC00 to 1,
  & (~(1 << ISC01));              //set ISC01 to 0, total interupt on change
  sei();                          //enable global interrupts

  TIMSK1 |= (1<<TOIE1);

  Serial.begin(9600);
  setupTimer1();

}

void setup() {
  irSetup();
}

void convertBites(){
  if(bufFlag){
    if((buf > (timeBreak - variation)) && (buf < (timeBreak + variation))){
      if(data){
        Serial.println(data);
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




void loop() {
 convertBites();
}
