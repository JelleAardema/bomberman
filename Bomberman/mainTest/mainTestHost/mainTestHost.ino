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

int mainLevelSeed = 0;
int mainLevelType = 0;

int enableMenu = 1;
int enableBomberman = 0;

void setup(){
  init();
  irccBegin(host);
  Wire.begin();
  Nunchuk.begin(0x52); 
  Serial.begin(9600);
  Serial.println("Setup Done!");

  // MAINMENU START
  if(enableMenu){
    initMainMenu(host);
    Serial.println("Mainmenu Setup Done!");
    // mainmenu loop  
    menu();
    Serial.println("Mainmenu Loop Done!");
  }

  // BOMBERMAN START
  if(enableBomberman){
    bombermanSetup();
    Serial.println("Bomberman Setup Done!");
  }
  
  Serial.println("Starting loop");
}
void loop(){
  if(enableBomberman){
  	if(gameUpdate()){
      bombermanUpdate();
  	}
  }else{
    Serial.println("Haha goeie");
  }
}
