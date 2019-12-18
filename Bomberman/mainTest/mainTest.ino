#include <stdint.h>
#include <avr/io.h>

// screen
#include <Adafruit_ILI9341.h>
#include <Adafruit_GFX.h>

// mainmenu
#include <highscore.h>
#include <mainMenu.h>

// nunchuck
#include <Wire.h>
#include <Nunchuk.h>

// bomberman
#include <bomberman.h>
#include <player.h>
#include <bomb.h>
#include <grid.h>
#include <level.h>

// IR/timer
#include <connection.h>
#include <globalTimer.h>

#include <showInfo.h>

#define host 0

Adafruit_ILI9341 screen = Adafruit_ILI9341(TFT_CS, TFT_DC);

int mainLevelSeed = 0;
int mainLevelType = 0;

int endGameFlag = 0;

//flags for refresh
uint16_t prevScore = 1;
uint8_t prev1 = 4;
uint8_t prev2 = 4;

// postion HUD elements
struct DIMENSION  score = {240,10,70,50};
struct DIMENSION  life1 = {240,70,70,50};
struct DIMENSION  life2 = {240,130,70,50};

void setup(){
	init();
	screen.begin();
	screen.setRotation(1);
	irccBegin(host);
	Wire.begin();
	Nunchuk.begin(0x52);
	Serial.begin(9600);
	Serial.println("Setup Done!");

	while(1){
		endGameFlag = 0;
		mainMenuSetup(&screen);
		//endScreenDisplay(1);
		
		if(host){	//HOST LOAD MAINMENU
			// MAINMENU Setup
			//mainMenuSetup(&screen);
			Serial.println("Host pressed Z.");
			// MAINMENU Loop
			menu(host);
			Serial.println("Level selected");
			mainLevelSeed = getLevelSeed();
			mainLevelType = getLevelType();
		}else{		//SLAVE WAITS
			// WAIT FOR HOST TO START
			connecting();				// screen shows Connecting...
			startConnection(host);
	
			// WAIT FOR HOST TO SEND LEVEL
			waitingForHost();			// screen shows Waiting for Host
			receiveLevel(&mainLevelSeed, &mainLevelType);
		}

		//Print level
		Serial.print("seed:  ");
		Serial.print(mainLevelSeed);
		Serial.print("  type:  ");
		Serial.println(mainLevelType);

		// BOMBERMAN Setup
		screen.fillScreen(0x0000);
		bombermanSetup(&screen, mainLevelSeed, mainLevelType,host);
		Serial.println("Bomberman Setup Done!");

		// Make sure that both players have the game loaded
		confirmLoad(host);
		Serial.println("Level Loaded");

		// BOMBERMAN Loop
		Serial.println("Starting loop");

		// reset flags for refresh
		prevScore = 1;
		prev1 = 4;
		prev2 = 4;
		while(!endGameFlag){					      	// check if nobody is dead
			if(gameUpdate()){					        // only update bomberman after a certain time
				bombermanUpdate(&screen);			    	// update player pos en
				endGameFlag = checkEndGame();
				unsetBomb();                        //resets player1.bombPlaced to 0
				// HUD
				prevScore = drawInfo(&screen, score, "score", getCurrentScore(),prevScore);
				prev1 = drawInfo(&screen, life1, "lifes1", getPlayer1Life(),prev1);
				prev2 = drawInfo(&screen, life2, "lifes2", getPlayer2Life(),prev2);
			}
		}
	}
}
