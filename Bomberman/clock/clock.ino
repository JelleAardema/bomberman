void setup();
void loop();

uint32_t i = 0;

int main() {
  setup();
  loop();

  return 0;
}

void setup() {

  Serial.begin(9600);
  Serial.println("start");
  
  // Set timer mode to CTC
  TCCR0A |= (1 << WGM01);

  // number of steps
  OCR0A = 63;

  TIMSK0 |= (1 << OCIE0A);

  // Set prescaler to 8
  TCCR0B |= (1 << CS01);

  // Enable interrupts  
  sei();

  delay(1000);
  TCCR0B &= ~(1 << CS01);
}

void loop() {
  while(1) {
    Serial.println(i);
  }
}

ISR(TIMER0_COMPA_vect) {
  i++;
}
