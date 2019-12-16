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

#define host 1

Adafruit_ILI9341 screen = Adafruit_ILI9341(TFT_CS, TFT_DC);

int mainLevelSeed = 0;
int mainLevelType = 0;

int enableMenu = 1;
int enableBomberman = 1;
int endGameFlag = 0;

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
	// MAINMENU START
		if(enableMenu){
			mainMenuSetup(&screen);
			Serial.println("Mainmenu Setup Done!");
			// mainmenu loop  
			menu(host);
			Serial.println("Mainmenu Loop Done!");
			getLevel(&mainLevelSeed, &mainLevelType);
			Serial.print("seed:  ");
			Serial.print(mainLevelSeed);
			Serial.print("  type:  ");
			Serial.println(mainLevelType);
		}

		// BOMBERMAN START
		if(enableBomberman){
			screen.fillScreen(0x0000);
			bombermanSetup(&screen, mainLevelSeed, mainLevelType);
			Serial.println("Bomberman Setup Done!");
		}
		
		//!!!!!!!!!!!!!!!!!!!!!!!!
		//confirmLoad(host);
		//!!!!!!!!!!!!!!!!!!!!!!!!
		// make sure that both players have the game loaded
	
		Serial.println("Starting loop");
	  
		while(!endGameFlag){
			if(enableBomberman){
				if(gameUpdate()){
				bombermanUpdate(&screen);
				endGameFlag = checkEndGame();
				Serial.println(getLifes());
				}
			}else{
			Serial.println("Haha goeie");
			}
		}
	}
}


void loop(){
  if(enableBomberman){
  	if(gameUpdate()){
      bombermanUpdate(&screen);
      Serial.println("l");
  	}
  }else{
    Serial.println("Haha goeie");
  }
}
