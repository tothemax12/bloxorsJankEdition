#pragma once
#include <string>
//#include <stdlib.h>
class Level
{
public:
	Level(std::string map);
	~Level();
	std::string map;

	//information relevant to a bridge
	struct bridge {
		//an array with -1 to mark the end
		int cordsOfTilesToReplace[4];
		static bool bridgeOn;
	};

	void addBridge(std::string& map, bridge relaventBridge);
};