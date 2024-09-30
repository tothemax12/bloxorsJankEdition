#pragma once
#include <string>
#include <stdio.h>
//class for string that holds map and related functionality, readInMap e.t.c
class Map
{
public:
	std::string mapStr;
	void printMap(std::string map, int playerCords[]);
	void printMapForAWin(std::string map);
	std::string readInMap(std::string mapName);
	Map(std::string mapName);
	Map();
};