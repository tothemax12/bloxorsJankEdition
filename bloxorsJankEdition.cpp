//Created by Max Anderson 2024

/* Dev log - 9/28/24:
* things to do:
* - reset the level when player fails
* - set it up so the player spawns in the level with the correct
* spawn cords and state
* - implement the fragile tiles that break when vertical
* - look into why it wraps back to level 1 in the array when you
* beat the levels
* 
* - A little ahead of myself but the main menu music should be mr ceo by thaiboy digital
* and the actual game (like when the user is playing it) can have just the instrumental
* 
* Dev log - 10/1/24
* - Added fragile tiles and their functionality
* - Cleaned up this file by removing map functionality (it's in the map class)
*/

#include <stdio.h>
#include <string>
#include <conio.h>
#include <stdlib.h>
#include "C:\Users\ander\source\repos\bloxorsJankEdition\bloxorsJankEdition\Player\Player.h"
#include "Map.h"
#include "Level.h"

//libraries for reading in a map
#include <fstream>
#include <iostream>

#define WIN 2
#define LOST 1

//map is 30x30
std::string map = "";
int mapRowSize = 60;
int currentLevel = 0;

//1 if you lost
int checkLevelLose(int cord1, int cord2) {
	int boundsCheck = (levels[currentLevel].mapObj.mapStr[cord1] == '#' || levels[currentLevel].mapObj.mapStr[cord2] == '#');
	
	//user falls if they are vertical on a fragile tile
	int fragileTileCheck = (levels[currentLevel].mapObj.mapStr[cord1] == 'W' && levels[currentLevel].mapObj.mapStr[cord2] == 'W' && (cord1 == cord2));

	return (boundsCheck || fragileTileCheck);
}

int checkLevelWin(int cord, int state) {
	//check if the player vertically fell into the hole
	return ((state == 0) && (levels[currentLevel].mapObj.mapStr[cord] == 'H'));
}

//modifies the map by adding walkable tiles when a button is pressed
//second arg is to be passed an array with -1 indicating the end is reached
void addBridge(std::string &map, int* cordsOfTilesToReplace, Level::bridge& relaventBridge) {
	//pressing the switch again will change the bridge
	for (int i = 0; *(cordsOfTilesToReplace + i) != -1; i++) {
		map[cordsOfTilesToReplace[i]] = relaventBridge.bridgeOn ? ('#') : ('X');
	}
	relaventBridge.bridgeOn = !relaventBridge.bridgeOn;
}

void handleMapTiles(int cord1, int cord2) {
	int cordsForBridge[3] = {245, 246, -1};
	int cordsForBridge2[3] = {251, -1};

	//handle if a button tile is pressed
	if (map[cord1] == 'B' || map[cord2] == 'B') {
		//first if we are on a bridge, we can search the current level for
		//the associated tile
		for (int i = 0; levels[currentLevel].levelBridges[i]->associatedTileOnMapCord != -1; i++) {
			//see if this is the bridge for the tile we are on
			if (levels[currentLevel].levelBridges[i]->associatedTileOnMapCord == cord1 || levels[currentLevel].levelBridges[i]->associatedTileOnMapCord == cord2) {
				//if we found the bridge then we can replace the tiles on the map
				addBridge(levels[currentLevel].mapObj.mapStr, levels[currentLevel].levelBridges[i]->cordsOfTilesToReplace, *levels[currentLevel].levelBridges[i]);
			}
		}

		//addBridge(map, cordsForBridge);
	}

	if (map[cord1] == 'S' && map[cord2] == 'S') {
		for (int i = 0; levels[currentLevel].levelBridges[i]->associatedTileOnMapCord != -1; i++) {
			//see if this is the bridge for the tile we are on
			if (levels[currentLevel].levelBridges[i]->associatedTileOnMapCord == cord1 || levels[currentLevel].levelBridges[i]->associatedTileOnMapCord == cord2) {
				//if we found the bridge then we can replace the tiles on the map
				addBridge(levels[currentLevel].mapObj.mapStr, levels[currentLevel].levelBridges[i]->cordsOfTilesToReplace, *levels[currentLevel].levelBridges[i]);
			}
		}
	}
}

int checkGameStatus(int cord1, int cord2, int state) {
	//0 is running, 1 is lost, 2 is win
	int statusFlag = 0;

	if (checkLevelLose(cord1, cord2)) {
		printf("You Fell!");
		statusFlag = 1;
	}

	if (checkLevelWin(cord1, state)) {
		system("CLS");
		levels[currentLevel].mapObj.mapStr[cord1] = 'H';
		levels[currentLevel].mapObj.printMapForAWin(levels[currentLevel].mapObj.mapStr);
		printf("You Won!");
		statusFlag = 2;
	}

	return statusFlag;
}

//reset everything in the level, bridges, e.t.c
void resetLevel() { 
	//for  (int i = 0; levels[currentLevel].levelBridges[i]->associatedTileOnMapCord != -1; i++) {
	//	//for each bridge
	//	//turn them all to true and then 
	//}

	//levels[currentLevel].levelBridges[i]
}

void handleWin(Player &player) {
	currentLevel++;
	player.cordinates[0] = levels[currentLevel].playerSpawnCords[0];
	player.cordinates[1] = levels[currentLevel].playerSpawnCords[1];
	player.state = levels[currentLevel].initialState;
	map = levels[currentLevel].mapObj.mapStr;
	//map = "";
}

void respawn(Player& player) {
	//put them back where they spawn
	player.cordinates[0] = levels[currentLevel].playerSpawnCords[0];
	player.cordinates[1] = levels[currentLevel].playerSpawnCords[1];
	player.state = levels[currentLevel].initialState;

	//have to reset all the bridges and stuff too
}

int main() {
	initializeLevels();

	//game loop
	map = levels[currentLevel].mapObj.mapStr;
	Player testPlayer = Player(mapRowSize);
	testPlayer.cordinates[0] = levels[currentLevel].playerSpawnCords[0];
	testPlayer.cordinates[1] = levels[currentLevel].playerSpawnCords[1];

	int gameStatus = -1;
	while (1) {
		//display
		levels[currentLevel].mapObj.printMap(map, testPlayer.cordinates);

		//get user input
		char input = _getch();
		testPlayer.updatePlayerCords(input);

		//see if the user won, lost or is still going
		gameStatus = checkGameStatus(testPlayer.cordinates[0], testPlayer.cordinates[1], testPlayer.state);
		if (gameStatus) {
			if (gameStatus == WIN) {
				handleWin(testPlayer);
			}
			else if (gameStatus == LOST) {
				respawn(testPlayer);
			}
		}

		handleMapTiles(testPlayer.cordinates[0], testPlayer.cordinates[1]);

		//clear the screen
		system("CLS");
	}

	return 0;
}