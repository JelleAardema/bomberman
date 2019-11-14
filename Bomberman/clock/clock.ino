void setup();
void loop();

int main() {
  setup();
  loop();

  return 0;
}

void setup() {
  DDRD |= (1 << PORTD3);
  
  TCCR2A = (1 << COM2A0) | (1 << COM2B1) | (1 << WGM21) | (1 << WGM20);
  TCCR2B = (1 << WGM22) | (1 << CS21);

//  58 kHz 
//  OCR2A = 33;
//  OCR2B = 16;

  // 38 kHz
  OCR2A = 52;
  OCR2B = 26;
}

void loop() {
  while(1) {
  
  }
}
