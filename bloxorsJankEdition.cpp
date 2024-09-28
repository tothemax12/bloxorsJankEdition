//Created by Max Anderson 2024

/* Dev log - 9/28/24:
* things to do:
* - reset the level when player fails
* - set it up so the player spawns in the level with the correct
* spawn cords and state
* - implement the fragile tiles that break when vertical
* - look into why it wraps back to level 1 in the array when you
* beat the levels
*/

#include <stdio.h>
#include <string>
#include <conio.h>
#include <stdlib.h>
#include "C:\Users\ander\source\repos\bloxorsJankEdition\bloxorsJankEdition\Player\Player.h"
#include "C:\Users\ander\source\repos\bloxorsJankEdition\bloxorsJankEdition\Level\Level.h"

//libraries for reading in a map
#include <fstream>
#include <iostream>

#define WIN 2
#define LOST 1

//map is 30x30
std::string map = "";
int mapRowSize = 60;
int currentLevel = 0;

//map reading in functionality
std::string readInMap(std::string mapName) {
	std::string map;

	// Open the input file named "input.txt"
	std::ifstream inputFile(".\\maps\\" + mapName + ".txt");

	// Check if the file is successfully opened
	if (!inputFile.is_open()) {
		return "-1";
	}
	else {
		//read in the map
		getline(inputFile, map);
	}

	inputFile.close();

	return map;
}
//init levels
Level level1 = Level(readInMap("level1"), 122, 123, 2);
Level level2 = Level(readInMap("level2"), 122, 123, 2);
Level levels[2];

void initializeLevels() { 
	int* level1EndBridgeCords = new int[3]{0, 0, -1};
	Level::bridge* level1EndBridge = new Level::bridge{
	level1EndBridgeCords,//array for where to put the bridge
	-1,//associated tile on the map
	};

	Level::bridge** level1Bridges = new Level::bridge * [3];
	level1Bridges[0] = level1EndBridge;

	level1.levelBridges = level1Bridges;

	//Bridges related to level2
	int* level2Bridge1Cords = new int[3]{245, 246, -1 };
	Level::bridge* level2Bridge1 = new Level::bridge {
		level2Bridge1Cords,//array for where to put the bridge
		183,//associated tile on the map
	};

	int* level2Bridge2Cords = new int[2]{ 251, -1 };
	Level::bridge* level2Bridge2 = new Level::bridge {
		level2Bridge2Cords,//array for where to put the bridge
		129,//associated tile on the map
	};

	int* level2EndBridgeCords= new int[3]{0, 0, -1};
	Level::bridge* level2EndBridge = new Level::bridge{
	level2EndBridgeCords,//array for where to put the bridge
	-1,//associated tile on the map
	};

	Level::bridge** level2Bridges = new Level::bridge*[3];
	level2Bridges[0] = level2Bridge1;
	level2Bridges[1] = level2Bridge2;
	level2Bridges[2] = level2EndBridge;

	level2.levelBridges = level2Bridges;
}

//level[currentLevel].levelBridges[0]

//levels[currentLevel].levelBridges[i]->associatedTileOnMapCord

//parsing a map string
//if you come across an X, move back one char and print a new line.
//this is so we print the boundaries correctly
void printMap(std::string map, int playerCords[]) {
	map[playerCords[0]] = '0';
	map[playerCords[1]] = '0';

	int mapLen = map.length();
	for (int i = 0; i < mapLen; i++) {
		//new row
		if (map[i] == ',') {
			printf("\n");
			continue;
		}

		if (map[i] == '.') {
			continue;
		}

		printf("%c", map[i]);
	}
}

//print just the map so player is not on the hole
void printMapForAWin(std::string map) {
	for (int i = 0; i < map.length(); i++) {
		//new row
		if (!(i % 6)) {
			printf("\n");
		}

		printf("%c", map[i]);
	}
}

//1 if you lost
int checkLevelLose(int cord1, int cord2) {
	return (map[cord1] == '#' || map[cord2] == '#');
}

int checkLevelWin(int cord, int state) {
	//check if the player vertically fell into the hole
	return ((state == 0) && (map[cord] == 'H'));
}

//modifies the map by adding walkable tiles when a button is pressed
//second arg is to be passed an array with -1 indicating the end is reached
void addBridge(std::string &map, int* cordsOfTilesToReplace, Level::bridge& relaventBridge ) {
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
				addBridge(map, levels[currentLevel].levelBridges[i]->cordsOfTilesToReplace, *levels[currentLevel].levelBridges[i]);
			}
		}

		//addBridge(map, cordsForBridge);
	}

	if (map[cord1] == 'S' && map[cord2] == 'S') {
		for (int i = 0; levels[currentLevel].levelBridges[i]->associatedTileOnMapCord != -1; i++) {
			//see if this is the bridge for the tile we are on
			if (levels[currentLevel].levelBridges[i]->associatedTileOnMapCord == cord1 || levels[currentLevel].levelBridges[i]->associatedTileOnMapCord == cord2) {
				//if we found the bridge then we can replace the tiles on the map
				addBridge(map, levels[currentLevel].levelBridges[i]->cordsOfTilesToReplace, *levels[currentLevel].levelBridges[i]);
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
		map[cord1] = 'H';
		printMapForAWin(map);
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
	player.cordinate[0] = levels[currentLevel].playerSpawnCords[0];
	player.cordinate[1] = levels[currentLevel].playerSpawnCords[1];
	player.state = levels[currentLevel].initialState;
	map = levels[currentLevel].map;
}

void respawn(Player& player) {
	//put them back where they spawn
	player.cordinate[0] = levels[currentLevel].playerSpawnCords[0];
	player.cordinate[1] = levels[currentLevel].playerSpawnCords[1];
	player.state = levels[currentLevel].initialState;

	//have to reset all the bridges and stuff too
}

int main() {
	initializeLevels();
	levels[0] = level1;
	levels[1] = level2;

	//game loop
	map = levels[currentLevel].map;

	Player testPlayer = Player(mapRowSize);

	int gameStatus = -1;
	while (1) {
		//display
		printMap(map, testPlayer.cordinate);

		//get user input
		char input = _getch();
		testPlayer.updatePlayerCords(input);

		//see if the user won, lost or is still going
		gameStatus = checkGameStatus(testPlayer.cordinate[0], testPlayer.cordinate[1], testPlayer.state);
		if (gameStatus) {
			if (gameStatus == WIN) {
				handleWin(testPlayer);
			}
			else if (gameStatus == LOST) {
				respawn(testPlayer);
				//printMap(map, testPlayer.cordinate);
			}
			//map = readInMap("level2");
			//testPlayer.cordinate[0] = 164;
			//testPlayer.cordinate[1] = 165;
		}

		handleMapTiles(testPlayer.cordinate[0], testPlayer.cordinate[1]);

		//clear the screen
		system("CLS");
	}

	return 0;
}