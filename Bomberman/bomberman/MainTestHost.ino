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
struct PLAYER player1 = {1,1,4};
struct PLAYER player2 = {7,7,3};
struct BOMB bomb1[MAXBOMBS];
struct BOMB bomb2;

int levelSeed;
int levelType;

int main() {
	// setup
	screen.begin();
	init();
	Wire.begin();
	Nunchuk.begin(0x52);
	irccBegin(host);
	Serial.begin(9600);
	Serial.println("Loaded");
  
	menu();		// mainmenu loop

	// load level
	screen.fillScreen(0x0000);
	// receiveLevel(&levelSeed, &levelType);
	if(levelType){
		genWorld(wrld,levelSeed);		// select random level
	}else{
		loadWorld(wrld,levelSeed);		// select standard level
	}
	drawGrid(&screen,dimension,wrld);
	// load bombs
	for(int a=0;a<MAXBOMBS;a++)
	{
		bomb1[a].x = 0;
		bomb1[a].y = 0;
		bomb1[a].fuse = 0;
		bomb1[a].placed = 0;
	}
	// make sure that both players have the game loaded
	confirmLoad(host);
	Serial.println("Level Loaded"); 
  

	// SEARCHING PLAYER STATUS
	while(1){
		if(gameUpdate()){
			Serial.println("1");
			Nunchuk.getState(0x52);
			if(stepper((AIM)getDirection(),wrld,&player1,dimension,&screen,bomb1,Nunchuk.state.z_button)){
				drawPlayer(player1,&screen,dimension);
			}
			sendPlayerStatus(player1.x, player1.y, player1.l, player1.b);
			bombs(bomb1,&screen,dimension,wrld);
			receivePlayerStatus(&player2.x, &player2.y, &player2.l, &player2.b);
			drawPlayer(player2,&screen,dimension);
		}
	}
	return 0;
}
