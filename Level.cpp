#include "C:\Users\ander\source\repos\bloxorsJankEdition\bloxorsJankEdition\Level\Level.h"

void Level::toggleBridge(std::string& map, Level::bridge relaventBridge) {
	//pressing the switch again will change the bridge
	for (int i = 0; relaventBridge.cordsOfTilesToReplace[i] != -1; i++) {
		map[relaventBridge.cordsOfTilesToReplace[i]] = relaventBridge.bridgeOn ? ('#') : ('X');
	}
	relaventBridge.bridgeOn = !relaventBridge.bridgeOn;
}

Level::Level(int spawnCord1, int spawnCord2, int playerInitialState, std::string nameOfMapFile) {
	//init map object here
	this->playerSpawnCords[0] = spawnCord1;
	this->playerSpawnCords[1] = spawnCord2;
	this->initialState = playerInitialState;
}

Level::Level() {
	//init map object here
	this->playerSpawnCords[0] = 0;
	this->playerSpawnCords[1] = 0;
	this->initialState = 0;
}

//init levels
//Level level1 = Level(readInMap("level1"), 122, 123, 2);
//Level level2 = Level(readInMap("level2"), 122, 123, 2);
//Level levels[2];

//void initializeLevels() { 
//	int* level1EndBridgeCords = new int[3]{0, 0, -1};
//	Level::bridge* level1EndBridge = new Level::bridge{
//	level1EndBridgeCords,//array for where to put the bridge
//	-1,//associated tile on the map
//	};
//
//	Level::bridge** level1Bridges = new Level::bridge * [3];
//	level1Bridges[0] = level1EndBridge;
//
//	level1.levelBridges = level1Bridges;
//
//	//Bridges related to level2
//	int* level2Bridge1Cords = new int[3]{245, 246, -1 };
//	Level::bridge* level2Bridge1 = new Level::bridge {
//		level2Bridge1Cords,//array for where to put the bridge
//		183,//associated tile on the map
//	};
//
//	int* level2Bridge2Cords = new int[2]{ 251, -1 };
//	Level::bridge* level2Bridge2 = new Level::bridge {
//		level2Bridge2Cords,//array for where to put the bridge
//		129,//associated tile on the map
//	};
//
//	int* level2EndBridgeCords= new int[3]{0, 0, -1};
//	Level::bridge* level2EndBridge = new Level::bridge{
//	level2EndBridgeCords,//array for where to put the bridge
//	-1,//associated tile on the map
//	};
//
//	Level::bridge** level2Bridges = new Level::bridge*[3];
//	level2Bridges[0] = level2Bridge1;
//	level2Bridges[1] = level2Bridge2;
//	level2Bridges[2] = level2EndBridge;
//
//	level2.levelBridges = level2Bridges;
//}