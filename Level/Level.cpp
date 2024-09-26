#include "Level.h";

void Level::addBridge(std::string& map, Level::bridge relaventBridge) {
	//pressing the switch again will change the bridge
	static bool bridgeOn = false;
	for (int i = 0; relaventBridge.cordsOfTilesToReplace[i] != -1; i++) {
		map[relaventBridge.cordsOfTilesToReplace[i]] = bridgeOn ? ('#') : ('X');
	}
	relaventBridge.bridgeOn = !relaventBridge.bridgeOn;
}

Level::Level(std::string map) {
	this->map = map;
}