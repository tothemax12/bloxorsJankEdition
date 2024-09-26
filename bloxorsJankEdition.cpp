#include <stdio.h>
#include <string>
#include <conio.h>
#include <stdlib.h>
#include "C:\Users\ander\source\repos\bloxorsJankEdition\bloxorsJankEdition\Player\Player.h"
#include "C:\Users\ander\source\repos\bloxorsJankEdition\bloxorsJankEdition\Level\Level.h"

//libraries for reading in a map
#include <fstream>
#include <iostream>

//map is 30x30
std::string map = "";
int mapRowSize = 60;

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
void addBridge(std::string &map, int* cordsOfTilesToReplace) {
	//pressing the switch again will change the bridge
	static bool bridgeOn = false;
	for (int i = 0; *(cordsOfTilesToReplace + i) != -1; i++) {
		map[cordsOfTilesToReplace[i]] = bridgeOn ? ('#') : ('X');
	}
	bridgeOn = !bridgeOn;
}

void handleMapTiles(int cord1, int cord2) {
	int cordsForBridge[3] = {245, 246, -1};
	int cordsForBridge2[3] = {251, -1};


	//handle if a button tile is pressed
	if (map[cord1] == 'B' || map[cord2] == 'B') {
		addBridge(map, cordsForBridge);
	}

	if (map[cord1] == 'S') {
		addBridge(map, cordsForBridge2);
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

int main() {
	//game loop

	//init levels
	Level level1 = Level(readInMap("level1"));
	Level level2 = Level(readInMap("level2"));
	Level levels[2] = { level1, level2 };
	int currentLevel = 0;

	Player testPlayer = Player(mapRowSize);
	
	int gameStatus = -1;
	while (1) {
		//display
		printMap(levels[currentLevel].map, testPlayer.cordinate);

		//get user input
		char input = _getch();
		testPlayer.updatePlayerCords(input);

		//see if the user won, lost or is still going
		gameStatus = checkGameStatus(testPlayer.cordinate[0], testPlayer.cordinate[1], testPlayer.state);
		if (gameStatus) {
			if (gameStatus == 2) {
				currentLevel++;
			}
			break;
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
