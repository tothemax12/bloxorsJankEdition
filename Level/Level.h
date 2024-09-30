#pragma once
#include <string>
#include "Map.h"

class Level
{
public:
	Level();
	Level(int spawnCord1, int spawnCord2, int playerInitialState, std::string nameOfMapFile);
	int playerSpawnCords[2];
	int initialState;

	//map for each level
	Map mapObj;
	std::string nameOfMapFile;

	//information relevant to a bridge
	struct bridge {
		//an array with -1 to mark the end
		int* cordsOfTilesToReplace;

		//tells us what tile this bride relates to on the map
		int associatedTileOnMapCord = 0;

		bool bridgeOn = false;
	};

	//array of bridges for the level, the end of this array is marked
	//by a bridge with associatedTileOnMapCord = -1;
	bridge** levelBridges;

	void toggleBridge(std::string& map, bridge relaventBridge);
};