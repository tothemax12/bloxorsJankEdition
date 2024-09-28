#include "C:\Users\ander\source\repos\bloxorsJankEdition\bloxorsJankEdition\Level\Level.h"

void Level::toggleBridge(std::string& map, Level::bridge relaventBridge) {
	//pressing the switch again will change the bridge
	for (int i = 0; relaventBridge.cordsOfTilesToReplace[i] != -1; i++) {
		map[relaventBridge.cordsOfTilesToReplace[i]] = relaventBridge.bridgeOn ? ('#') : ('X');
	}
	relaventBridge.bridgeOn = !relaventBridge.bridgeOn;
}

Level::Level(std::string map, int spawnCord1, int spawnCord2, int initialState) {
	this->map = map;
	this->playerSpawnCords[0] = spawnCord1;
	this->playerSpawnCords[1] = spawnCord2;
	this->initialState = initialState;
}

Level::Level() {
	this->map = "";
	this->playerSpawnCords[0] = 0;
	this->playerSpawnCords[1] = 0;
	this->initialState = 0;
}