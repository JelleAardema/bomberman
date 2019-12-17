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

#define host 1

Adafruit_ILI9341 screen = Adafruit_ILI9341(TFT_CS, TFT_DC);

int mainLevelSeed = 0;
int mainLevelType = 0;

int endGameFlag = 0;

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
    if(host){
      // MAINMENU Setup
  		mainMenuSetup(&screen);
  		Serial.println("Host pressed Z.");
  		
  		// MAINMENU Loop
  		menu(host);
  		Serial.println("Level selected");
  		mainLevelSeed = getLevelSeed();
  		mainLevelType = getLevelType();
    }else{
      Serial.println("Waiting for host, press Z.");
      startConnection(host);
    
      // WAIT FOR HOST TO SEND LEVEL
      Serial.println("Waiting for host, level select.");    
      receiveLevel(&mainLevelSeed, &mainLevelType);
    }
		
		//Print level
		Serial.print("seed:  ");
		Serial.print(mainLevelSeed);
		Serial.print("  type:  ");
		Serial.println(mainLevelType);

		// BOMBERMAN Setup
		screen.fillScreen(0x0000);
		bombermanSetup(&screen, mainLevelSeed, mainLevelType);
		Serial.println("Bomberman Setup Done!");
		
		// Make sure that both players have the game loaded
		confirmLoad(host);
		Serial.println("Level Loaded"); 
	
		// BOMBERMAN Loop
		Serial.println("Starting loop");
		while(!endGameFlag){					      	// check if nobody is dead			
			if(gameUpdate()){					        // only update bomberman after a sertain time
			bombermanUpdate(&screen);			    	// update player pos en 
			endGameFlag = checkEndGame();
			unsetBomb();                        //resets player1.bombPlaced to 0
			// HUD
			drawInfo(&screen, score, "score", getCurrentScore());
			drawInfo(&screen, life1, "lifes1", getPlayer1Life());
			drawInfo(&screen, life2, "lifes2", getPlayer2Life());
			}
		}
	}
}
