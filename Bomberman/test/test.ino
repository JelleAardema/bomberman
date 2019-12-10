#include <mainMenu.h>

#define host 1

void setup() {
  // put your setup code here, to run once:
	Serial.begin(9600);
	initMainMenu(host);
	menu();
}


void loop() {
  // put your main code here, to run repeatedly:

	Serial.println("Haha goeie");
}