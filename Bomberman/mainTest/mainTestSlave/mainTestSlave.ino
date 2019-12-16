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
#define host 0

Adafruit_ILI9341 screen = Adafruit_ILI9341(TFT_CS, TFT_DC);

int mainLevelSeed = 0;
int mainLevelType = 0;

int enableMenu = 1;
int enableBomberman = 1;
int endGameFlag = 0;

int main() {
	init();
	screen.begin();
	screen.setRotation(1);  
	irccBegin(host);
	Wire.begin();
	Nunchuk.begin(0x52); 
	Serial.begin(9600);
	Serial.println("Setup Done!");

	while(1){
		// WAIT FOR HOST TO PRESS Z
		startConnection(host);

		// WAIT FOR HOST TO SEND LEVEL
		receiveLevel(&mainLevelSeed, &mainLevelType);
		
		// LOAD LEVEL
		screen.fillScreen(0x0000);
		bombermanSetup(&screen, mainLevelSeed, mainLevelType);
		Serial.println("Bomberman Setup Done!");
		
		// make sure that both players have the game loaded
		confirmLoad(host);
		Serial.println("Level Loaded"); 
	  
		//!!!!!!!!!!!!!!!!!!!!!!!!
		//confirmLoad(host);
		//!!!!!!!!!!!!!!!!!!!!!!!!
		// make sure that both players have the game loaded
		// game loop
		while(!endGameFlag){
			if(enableBomberman){
				if(gameUpdate()){
				bombermanUpdate(&screen);
				endGameFlag = checkEndGame();
				Serial.println("l");
				}
			}else{
			Serial.println("Haha goeie");
			}
		}
	}
	return 0;
}
