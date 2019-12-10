#include <stdint.h>
#include <avr/io.h>

// screen
#include <Adafruit_ILI9341.h>
#include <Adafruit_GFX.h>

// mainmenu
#include <mainMenu.h>

// nunchuck
#include <Wire.h>
#include <Nunchuk.h>

// bomberman
#include <player.h>
#include <bomb.h>
#include <grid.h>
#include <level.h>

// IR/timer
#include <connection.h>
#include <globalTimer.h>

int getDirection();
#define host 1

Adafruit_ILI9341 screen = Adafruit_ILI9341(TFT_CS, TFT_DC);
uint8_t wrld[GRID_X][GRID_Y];
struct DIMENSION dimension = {10,10,220,220};
struct PLAYER player1 = {1,1,3,0,4};
struct PLAYER player2 = {7,7,3,0,3};
struct BOMB bomb1[MAXBOMBS];
struct BOMB bomb2;

volatile int mainLevelSeed;
volatile int mainLevelType;

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
