#include "C:\Users\ander\source\repos\bloxorsJankEdition\bloxorsJankEdition\Player\Player.h"
#include <stdlib.h>

//definitions of block state
#define VERTICAL 0
#define HORIZONTAL 1
#define HORIZONTAL2 2

//constructor
Player::Player(int mapRowSize) {
	//level 1 spawn cords
	cordinate[0] = {2};
	cordinate[1] = {3};

	//level 2 spawn cords
	//cordinate[0] = {122};
	//cordinate[1] = {123};

	//0 is vertical, 1 is horizontal, 2 is horizontal otherway lol
	state = 2;
	playerChar = 0;
	this->mapRowSize = mapRowSize;
};

int** Player::normalizePlayerCords() {
	int* cord1 = NULL;
	int* cord2 = NULL;
	int* cords[2] = {NULL, NULL};
		if (state == HORIZONTAL) {
			if (cordinate[0] > cordinate[1]) {
				cord1 = (cordinate);
				cord2 = (cordinate + 1);
			}
			else {
				cord1 = (cordinate + 1);
				cord2 = (cordinate);
			}
		}
		else if (state == HORIZONTAL2) {
			if (cordinate[0] < cordinate[1]) {
				cord1 = (cordinate);
				cord2 = (cordinate + 1);
			}
			else {
				cord1 = (cordinate + 1);
				cord2 = (cordinate);
			}
		}
		else if (state == VERTICAL) {
			cordinate[1] = cordinate[0];
			cord1 = (cordinate);
			cord2 = (cordinate + 1);
		}
		cords[0] = cord1;
		cords[1] = cord2;
		return cords;
}

//dir is a char representing the move the player made
void Player::updatePlayerCords(char dir) {
		//so we can do the math and put the block in the right place
		int PlayerMapRowSize = Player::mapRowSize;

		//makes it easier to work with the cords if you move the block around
		int** normalizedCordList = normalizePlayerCords();
		int* cord1 = normalizedCordList[0];
		int* cord2 = normalizedCordList[1];

		//code updating the players position
		switch (state) {
			//vertical x
		case VERTICAL:
			if (dir == 'w') {
				*cord1 -= mapRowSize;
				*cord2 -= 2 * mapRowSize;
				state = HORIZONTAL;
			}
			if (dir == 'a') {
				*cord1 -= 2;
				*cord2 -= 1;
				//update block state and make it horizontal
				state = HORIZONTAL2;
			}
			if (dir == 's') {
				*cord1 += mapRowSize;
				*cord2 += 2 * mapRowSize;
				//update block state and make it horizontal
				state = HORIZONTAL;
			}
			if (dir == 'd') {
				*cord1 += 1;
				*cord2 += 2;
				//update block state and make it horizontal
				state = HORIZONTAL2;
			}

			break;
			//horizontal x 2
			//           x 1
		case HORIZONTAL:
			//old implementation
			if (dir == 'w') {
				*cord1 -= 2 * mapRowSize;
				*cord2 = *cord1;
				state = VERTICAL;
			}
			if (dir == 'a') {
				*cord1 -= 1;
				*cord2 -= 1;
			}
			if (dir == 's') {
				*cord1 += mapRowSize;
				*cord2 = *cord1;
				state = VERTICAL;
			}
			if (dir == 'd') {
				*cord1 += 1;
				*cord2 += 1;
			}
			break;
			//other horizontal xx
			//   1,2
		case HORIZONTAL2:
			if (dir == 'w') {
				*cord1 -= mapRowSize;
				*cord2 -= mapRowSize;
			}
			if (dir == 'a') {
				*cord1 -= 1;
				*cord2 -= 2;

				//update block state and make it vertical
				state = VERTICAL;
			}
			if (dir == 's') {
				*cord1 += mapRowSize;
				*cord2 += mapRowSize;
			}
			if (dir == 'd') {
				*cord1 += 2;
				*cord2 += 1;
				//update block state and make it vertical
				state = VERTICAL;
			}

			break;
		default:
			break;
		}
	};