#include <stdio.h>
#include <string>
#include <conio.h>
#include <stdlib.h>

//definitions of block state
#define VERTICAL 0
#define HORIZONTAL 1
#define HORIZONTAL2 2


//map is 30x30
std::string map = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXHXXXXXXX";
//std::string map = "#########XXXXXX##XXXXXX##XXXXXX##XXXXXX##XXXXXX##XXXXXX##XXXXXX##XXXXXX##XXXXXX##XXXXXX##XXXXXX##XHXXXX##XXX####";

int mapRowSize = 6;


void printMap(std::string map, int playerCords[]) {
	map[playerCords[0]] = '0';
	map[playerCords[1]] = '0';

	for (int i = 0; i < map.length(); i++) {
		//new row
		if (!(i % 6)) {
			printf("\n");
		}

		//print the player out
		// if (i == playerCords[0] || i == playerCords[1]) {
		// //printf("i: %d", i);
		// printf("%c", '0');
		// }

		printf("%c", map[i]);
	}
}

//print just the map so player is not on the hole
void printMapForAWin(std::string map) {
	for (int i = 0; i < map.length(); i++) {
		//new row
		if (!(i % 6)) {
			printf("\n");
		}

		//print the player out
		// if (i == playerCords[0] || i == playerCords[1]) {
		// //printf("i: %d", i);
		// printf("%c", '0');
		// }

		printf("%c", map[i]);
	}
}

class Player {
public:
	int cordinate[2] = { 2, 3 };
	//0 is vertical, 1 is horizontal, 2 is horizontal otherway lol
	int state = 2;
	int playerChar = 0;

	//constructor
	Player() {

	}

	// void normalizePlayersCordsBasedOnState(int* cordinates) {
	// //makes it easier to work with the cords if you move the block around
	// int* cord1 = NULL;
	// int* cord2 = NULL;
	// int* cords[2] = {cord1, cord2};
	// if (state == HORIZONTAL) {
	// if (cordinate[0] > cordinate[1]) {
	// cord1 = (cordinate);
	// cord2 = (cordinate+1);
	// } else {
	// cord1 = (cordinate+1);
	// cord2 = (cordinate);
	// }
	// } else if (state == HORIZONTAL2) {
	// if (cordinate[0] < cordinate[1]) {
	// cord1 = (cordinate);
	// cord2 = (cordinate+1);
	// } else {
	// cord1 = (cordinate+1);
	// cord2 = (cordinate);
	// }
	// } else if (state == VERTICAL) {
	// cordinate[1] = cordinate[0];
	// cord1 = (cordinate);
	// cord2 = (cordinate + 1);
	// }
	// //end of keeping track of cords (normalizing them?)--------------------------------------
	// cordinates = cord1;
	// cordinates[1] = cord2;
	//}

	//dir is a char representing the move the player made
	void updatePlayerCords(char dir) {
		//
		//makes it easier to work with the cords if you move the block around
		int* cord1 = NULL;
		int* cord2 = NULL;
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
		//end of keeping track of cords (normalizing them?)--------------------------------------

		//array of normalized cords

		// int normalizedCordinates[2];
		// normalizePlayersCordsBasedOnState(normalizedCordinates);
		// int* cord1 = *normalizedCordinates;
		// int* cord2 = *normalizedCordinates;

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
	}
};

int checkLevelWin(int cord, int state) {
	//check if the player vertically fell into the hole
	return ((state == VERTICAL) && (map[cord] == 'H'));
}

int main() {
	//game loop
	//int test[2] = {0, 1};
	Player testPlayer = Player();

	while (1) {
		//display
		printMap(map, testPlayer.cordinate);

		//get user input
		char input = _getch();
		testPlayer.updatePlayerCords(input);

		if (checkLevelWin(testPlayer.cordinate[0], testPlayer.state)) {
			system("CLS");
			map[testPlayer.cordinate[0]] = 'H';
			printMapForAWin(map);
			printf("You Won!");
			break;
		}

		//clear the screen
		system("CLS");
	}

	return 0;
}
