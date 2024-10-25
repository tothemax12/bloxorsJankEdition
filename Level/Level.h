#pragma once
#include <string>
#include "Map.h"

class Level
{
public:
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
	/*void initializeLevels();*/

	Level();
	Level(int spawnCord1, int spawnCord2, int playerInitialState, std::string nameOfMapFile, bridge** levelBridges);
};

//level definitions
extern Level level1;
extern Level level2;
extern Level level3;
extern Level levels[3];
extern void initializeLevels();