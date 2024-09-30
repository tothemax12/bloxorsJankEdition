#include "Map.h"

//libraries for reading in a map
#include <fstream>
#include <iostream>

//Implementation of Map class
void Map::printMap(std::string map, int playerCords[]) {
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
void Map::printMapForAWin(std::string map) {
	for (int i = 0; i < map.length(); i++) {
		//new row
		if (!(i % 6)) {
			printf("\n");
		}

		printf("%c", map[i]);
	}
}

//map reading in functionality
std::string Map::readInMap(std::string mapName) {
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

Map::Map(std::string mapName) {
	this->mapStr = readInMap(mapName);
};

Map::Map() {
	this->mapStr = readInMap("level1");
};