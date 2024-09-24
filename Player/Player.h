#pragma once 
class Player {
public:
	int cordinate[2];
	//0 is vertical, 1 is horizontal, 2 is horizontal otherway lol
	int state;
	int playerChar;
	int mapRowSize;

	//constructor
	Player(int mapRowSize);

	//make the cords nice to work with
	int** normalizePlayerCords();

	//dir is a char representing the move the player made
	void updatePlayerCords(char dir);
};