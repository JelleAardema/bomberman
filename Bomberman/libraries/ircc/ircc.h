// header file grid system
#ifndef IRCC_h
#define IRCC_h

// timings
// configure the time of interupt
// timeLow is the base and stands for a bit with a value of 0
// timeHigh is double the length of timeLow and has the bit value of 1
// timeBreak is three times the length of timeLow and is the minimum barrier to check if a set of bits is complete
#define timeLow 60
#define variation timeLow/3
#define timeHigh timeLow*2
#define timeBreak timeLow*3


// function send
void sendIRCC(uint16_t data);
void sendBit();
void transmitDataSetup(int host);
void timer2Init();
void timer0Init();

// function receive
uint16_t receiveIRCC();
void timer1Init();
void pinInit();
void receiveBit();
void clearTimer1();

#endif
