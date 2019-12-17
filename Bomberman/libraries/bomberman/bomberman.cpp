#include <stdint.h>
#include <avr/io.h>

// screen
#include <Adafruit_ILI9341.h>
#include <Adafruit_GFX.h>

// nunchuck
#include <Wire.h>
#include <Nunchuk.h>

// bomberman
#include <player.h>
#include <bomb.h>
#include <grid.h>
#include <level.h>
#include <highscore.h>

// IR/timer
#include <connection.h>
#include <globalTimer.h>

#include "bomberman.h"

int getDirection();
//Adafruit_ILI9341 screen = Adafruit_ILI9341(TFT_CS, TFT_DC);
uint8_t wrld[GRID_X][GRID_Y];
struct DIMENSION dimension = {10,10,220,220};
struct PLAYER player1 = {1,1,MAXLIFE,0,4};
struct PLAYER player2 = {7,7,MAXLIFE,0,4};
struct BOMB bomb1[MAXBOMBS];
struct BOMB bomb2;

void bombermanSetup(Adafruit_ILI9341 *pen, int seed, int type){
	player1 = {1,1,MAXLIFE,0,4};
	player2 = {7,7,MAXLIFE,0,3};
	if(type){
		loadWorld(wrld,seed);		// load standard level
	}else{
		genWorld(wrld,seed);		// load random level
	}
    drawGrid(pen,dimension,wrld);
    
    // set all bombs to 0
    for(int a=0; a<MAXBOMBS; a++)
    {
      bomb1[a].x = 0;
      bomb1[a].y = 0;
      bomb1[a].fuse = 0;
      bomb1[a].placed = 0;
    }
}
void bombermanUpdate(Adafruit_ILI9341 *pen){
    Nunchuk.getState(0x52);
    if(stepper(pen,dimension,wrld,(AIM)getDirection(),&player1,bomb1,Nunchuk.state.z_button)){
      drawPlayer(pen,dimension,player1);
    }
    bombs(pen,dimension,wrld,bomb1,&player1);
  	sendPlayerStatus(player1.x, player1.y, player1.life, player1.bombPlaced);
  	receivePlayerStatus(&player2.x, &player2.y, &player2.life, &player2.bombPlaced);
  	drawPlayer(pen,dimension,player2);
}

int checkEndGame(){    
	// Save highscore if 1 of the players reaches 0 lifes
    if(player1.life <= 0 || player2.life <= 0) {
		uint16_t finalScore = calculateScore(player1.life);
		placeHighscore(finalScore);
		return 1;
	}
	return 0;
}

uint8_t getPlayer1Life(){
	return player1.life;
}

uint8_t getPlayer2Life(){
	return player2.life;
}
// reset bombPlaced after sending the data
void unsetBomb(){
  player1.bombPlaced = 0;
}