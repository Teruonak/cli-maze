#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// function sign declaration
void fillMaze(FILE *f, int (*maze)[50], int *rowLength, int *colLength,
		int *goal, int *errorStatus);
void printMaze(int rowLength, int colLength, int maze[50][50],
		int playerDirection, int *playerX, int *playerY);
void printMazeUnit(int unit, int playerDirection);
char getPlayerDirection(int playerDirection);
int hasGoal(int goal[3]);
void doCommand(int (*maze)[50], char command[], int *goal, int *playerDirection,
		int playerX, int playerY, int *amountItem1, int *amountItem2,
		char *information);
void collect(int (*maze)[50], char *information, int playerDirection, int playerX, int playerY,
		int *amountItem1, int *amountItem2);
void useItem(int (*maze)[50], char *information, int playerDirection, int itemX, int itemY,
		int *amountItem, int numberItem);
void move(int (*maze)[50], int *goal, int movements, char *information,
		int playerDirection, int playerX, int playerY);
void movePlayer(int (*maze)[50], int times, int playerDirection, int *stepX,
		int *stepY);
void diagmove(int (*maze)[50], char cmd[], char *information,
		int playerDirection, int playerX, int playerY);

int main() {
	// configurations
	char fileName[100] = "mapa.txt";

	// variables
	FILE *file;
	int maze[50][50];
	int colLength, rowLength;
	int playerDirection = 0, playerX, playerY;
	int amountItem1 = 0;
	int amountItem2 = 0;
	char command[20];
	int goal[3] = { 1, 1, 1 };
	int errorStatus[5] = { };
	char information[50] = "";

	puts("Started");

	file = fopen(fileName, "r");
	if (!file) {
		printf("ERROR: can't open the file: %s", fileName);
	}
	fillMaze(file, maze, &rowLength, &colLength, goal, errorStatus);

	if (errorStatus[0]) {
		puts("ERROR: Could not open file");
		return 0;
	}
	if (errorStatus[1]) {
		printf("ERROR: The file %s do not follow the pattern.", fileName);
		return 0;
	}
	if (errorStatus[2]) {
		printf(
				"ERROR: The length of row: %d or column: %d is lower than 1 or greater than 50",
				rowLength, colLength);
		return 0;
	}
	if (errorStatus[3]) {
		puts("ERROR: Has more than one goal.");
		return 0;
	}
	if (errorStatus[4]) {
		puts("ERROR: ");
		return 0;
	}

	// DEBUG test fillMaze
//	for (int i = 0; i < rowLength; ++i) {
//		for (int j = 0; j < colLength; ++j) {
//			printf("%d", maze[i][j]);
//		}
//		puts("");
//	}

	while (hasGoal(goal)) {
//		system("cls");  // only Microsoft Windows
//		system("clear");  // only to linux

		printMaze(rowLength, colLength, maze, playerDirection, &playerX,
				&playerY);

		puts("");
		puts("");
		printf("item 1: %d\n", amountItem1);
		printf("item 2: %d\n", amountItem2);
		puts("");
		puts("");
		puts(information);
		puts("");
		printf("Command: ");
		fgets(command, 20, stdin);
		doCommand(maze, command, goal, &playerDirection, playerX, playerY,
				&amountItem1, &amountItem2, information);
	}

	if (hasGoal(goal) == 0) {
		printf("You win!");
	} else {
		printf("Game over!");
	}

	puts("");
	puts("");
	puts("Thanks for playing!");

	return 0;
}

void fillMaze(FILE *f, int (*maze)[50], int *rowLength, int *colLength,
		int *goal, int *errorStatus) {
	int c; // each char
	// init variables
	*rowLength = 0;
	*colLength = 0;
	int row = -1;
	int col = -1;
	int *pRowAndCol = rowLength;
//	int goalNumber[3] = { };
	// getting the data from file. Get each char
	while ((c = fgetc(f)) != EOF) {
		// to skip the CR
		if (c == 13) {
			continue;
		}
		// get the first line. i.e. row and column numbers
		if (row == -1) {
			// when finish the entire number
			if (c == 32) {
				pRowAndCol = colLength;
				continue;
			}
			if (c == 10) {
				row++;
				continue;
			}
			// get composite number
			if (*pRowAndCol == 0) {
				*pRowAndCol = c - '0';
			} else {
				*pRowAndCol *= 10;
				*pRowAndCol += (c - '0');
			}
			continue;
		}

		// get the Maze
		// skip the space
		if (c == 32) {
			continue;
		}
		// when break line
		if (c == '\n') {
			row++;
			if (col != *colLength) {
				//TODO throw an error
			}
			col = -1; // reset the column
			continue;
		}
		col++;
//		printf("maze[%d][%d] = %c\n", row, col, c); // DEBUG
		maze[row][col] = c - '0';

		// get the number of each goal
		if (maze[row][col] == 3) {
			goal[0] = 1;
		} else if (maze[row][col] == 4) {
			goal[1] = 1;
		} else if (maze[row][col] == 5) {
			goal[2] = 1;
		}
	}

	fclose(f);
}

void printMaze(int rowLength, int colLength, int maze[50][50],
		int playerDirection, int *playerX, int *playerY) {
	int i, j;
	for (i = 0; i < rowLength; i++) {
		for (j = 0; j < colLength; j++) {
			if (maze[i][j] == 2) {
				*playerX = j;
				*playerY = i;
			}
			printMazeUnit(maze[i][j], playerDirection);
		}
		printf("\n");
	}
}

void printMazeUnit(int unit, int playerDirection) {
	switch (unit) {
	case 0:
		printf(" ");
		break;
	case 1:
		printf("X");
		break;
	case 2:
		printf("%c", getPlayerDirection(playerDirection));
		break;
	case 3:
	case 4:
	case 5:
		printf("O");
		break;
	case 6:
		printf("B");
		break;
	case 7:
		printf("A");
		break;
	case 8:
		printf("1");
		break;
	case 9:
		printf("2");
		break;
	}
}

char getPlayerDirection(int playerDirection) {
	char direction = 'v';

	int rest = playerDirection % 4;
	switch (rest) {
	case 0:
		direction = 'v';
		break;
	case 1:
		direction = '<';
		break;
	case 2:
		direction = '^';
		break;
	case 3:
		direction = '>';
		break;
	}

	return direction;
}

int hasGoal(int goal[3]) {
	int hasGoal = 0;
	for (int i = 0; i < 3; ++i) {
		if (goal[i]) {
			hasGoal = 1;
		}
	}
	return hasGoal;
}

void getNext(int playerDirection, int *x, int *y) {
	int rest = playerDirection % 4;
	switch (rest) {
	case 0:
		*y += 1;
		break;
	case 1:
		*x -= 1;
		break;
	case 2:
		*y -= 1;
		break;
	case 3:
		*x += 1;
		break;
	}
}

int checkMazeUnit(int maze[50][50], int x, int y, char *information) {
	switch (maze[y][x]) {
	case 1: // Wall
		strcpy(information, "ERROR: You can't through walls");
		return maze[y][x];
	case 6: // B
		strcpy(information, "Game Over: Die with bomb");
		return maze[y][x];
	case 7: // A
		strcpy(information, "Game Over: Die with trap");
		return maze[y][x];
	case 8: // 1
		strcpy(information, "ERROR: You can't through the item 1");
		return maze[y][x];
	case 9: // 2
		strcpy(information, "ERROR: You can't through the item 2");
		return maze[y][x];
	}

	return 0;
}

void collect(int (*maze)[50], char *information, int playerDirection, int playerX, int playerY,
		int *amountItem1, int *amountItem2) {
	int holderItemX = playerX, holderItemY = playerY;
	getNext(playerDirection, &holderItemX, &holderItemY);

	if (maze[holderItemY][holderItemX] == 8) {
		(*amountItem1)++;
		strcpy(information, "Item 1 collected");
		maze[holderItemY][holderItemX] = 0;
	} else if (maze[holderItemY][holderItemX] == 9) {
		(*amountItem2)++;
		strcpy(information, "Item 2 collected");
		maze[holderItemY][holderItemX] = 0;
	}
}

void doCommand(int (*maze)[50], char command[], int *goal, int *playerDirection,
		int playerX, int playerY, int *amountItem1, int *amountItem2,
		char *information) {
	char *pCmd;
	strcpy(information, "");
	pCmd = strtok(command, " \n");
	if (pCmd == NULL) {
		strcpy(information, "ERROR: Invalid command! Please enter a command or enter 'help' for more information");
	}
	// turns
	if (strcmp(pCmd, "turn") == 0) {
		pCmd = strtok(NULL, " \n"); // get the next "parameter"
		if (pCmd == NULL) {
			strcpy(information, "INFO: Try 'turn [left,right,180]' e.g. 'turn left'");
			return;
		}
		if (strcmp(pCmd, "left") == 0) {
			(*playerDirection) += 3;
		} else if (strcmp(pCmd, "right") == 0) {
			(*playerDirection)++;
		} else if (strcmp(pCmd, "180") == 0) {
			(*playerDirection) += 2;
		} else {
			strcpy(information, "Invalid command!");
		}
	}
	// collect
	else if (strcmp(pCmd, "collect") == 0) {
		collect(maze, information, *playerDirection, playerX, playerY, amountItem1,
				amountItem2);
	}
	// use
	else if (strcmp(pCmd, "use") == 0) {
		pCmd = strtok(NULL, " \n"); // get the next "parameter"
		if (pCmd == NULL) {
			strcpy(information, "INFO: Try 'use [1,2]' e.g. 'use 2'");
			return;
		}
		int *amountItem = NULL;
		int numberItem = 0;
		if (((*pCmd) - '0') == 1) {
			amountItem = amountItem1;
			numberItem = 8;
		} else if (((*pCmd) - '0') == 2) {
			amountItem = amountItem2;
			numberItem = 9;
		} else {
			strcpy(information, "ERROR: Invalid command! Try 'use [1,2]' e.g. 'use 2'");
			return;
		}
		useItem(maze, information, *playerDirection, playerX, playerY, amountItem,
				numberItem);
	}
	// move
	else if (strcmp(pCmd, "move") == 0) {
		pCmd = strtok(NULL, " \n");
		if (pCmd == NULL) {
			strcpy(information, "INFO: Try 'move [0-9]' e.g. 'move 3'");
			return;
		}
		if (!isdigit(*pCmd)) {
			strcpy(information, "ERROR: Invalid command! Put a digit [0-9]");
			return;
		}
		int movements = ((*pCmd) - '0');
		move(maze, goal, movements, information, *playerDirection, playerX,
				playerY);
	}
	// diagonal move
	else if (strcmp(pCmd, "diagmove") == 0) {
		pCmd = strtok(NULL, " \n");
		if (pCmd == NULL) {
			strcpy(information, "INFO: Try 'diagmove [fr,fl,br,bl]' e.g. 'diagmove fl'");
			return;
		}
		diagmove(maze, pCmd, information, * playerDirection, playerX, playerY);
	} else {
		strcpy(information, "Invalid command!");
	}
}

void useItem(int (*maze)[50], char *information, int playerDirection, int playerX, int playerY,
		int *amountItem, int numberItem) {
	int holderItemX = playerX, holderItemY = playerY;
	getNext(playerDirection, &holderItemX, &holderItemY);

	int mazeUnit = maze[holderItemY][holderItemX];
	// do not have the item in maze
	if ((mazeUnit != 6 && numberItem == 8 ) || (mazeUnit != 7 && numberItem == 9 ) || (mazeUnit != 6 && mazeUnit != 7)) {
		exit(0); //TODO throw error
		strcpy(information, "ERROR: Invalid command! Use 1 for B and 2 for A");
		return;
	}
	// do not have enough amount to use Item
	if (*amountItem < 1) {
		strcpy(information, "ERROR: You don't have an enough item amount");
		return;
	}
	strcpy(information, "Obstacle destroyed");
	maze[holderItemY][holderItemX] = 0;
	(*amountItem)--;
}

void move(int (*maze)[50], int *goal, int movements, char *information,
		int playerDirection, int playerX, int playerY) {
	int holderX = playerX, holderY = playerY;
	strcpy(information, "");
	movePlayer(maze, movements - 1, playerDirection, &holderX, &holderY);

	int status;
	status = checkMazeUnit(maze, holderX, holderY, information);

	if (status == 1 || status == 8 || status == 9) {
		return;
	}

	if (maze[holderY][holderX] == 3) {
		goal[0] = 0;
	} else if (maze[holderY][holderX] == 4) {
		goal[1] = 0;
	} else if (maze[holderY][holderX] == 5) {
		goal[2] = 0;
	}

	maze[playerY][playerX] = 0;
	maze[holderY][holderX] = 2;
}

void movePlayer(int (*maze)[50], int times, int playerDirection, int *stepX,
		int *stepY) {
	getNext(playerDirection, stepX, stepY);

	if (times == 0) {
		return;
	}

	if (maze[*stepY][*stepX] != 0 && maze[*stepY][*stepX] != 3
			&& maze[*stepY][*stepX] != 4 && maze[*stepY][*stepX] != 5) {
		return;
	}
	return movePlayer(maze, times - 1, playerDirection, stepX, stepY);
}

void diagmove(int (*maze)[50], char cmd[], char *information,
		int playerDirection, int playerX, int playerY) {
	int FRONT = 0;
	int RIGHT = 1;
	int LEFT = 3;
	int BACK = 2;
	int moveX = playerX, moveY = playerY;
	if (strcmp(cmd, "fl") == 0) {
		getNext(playerDirection + FRONT, &moveX, &moveY);
		getNext(playerDirection + LEFT, &moveX, &moveY);
	} else if (strcmp(cmd, "fr") == 0) {
		getNext(playerDirection + FRONT, &moveX, &moveY);
		getNext(playerDirection + RIGHT, &moveX, &moveY);
	} else if (strcmp(cmd, "bl") == 0) {
		getNext(playerDirection + BACK, &moveX, &moveY);
		getNext(playerDirection + LEFT, &moveX, &moveY);
	} else if (strcmp(cmd, "br") == 0) {
		getNext(playerDirection + BACK, &moveX, &moveY);
		getNext(playerDirection + RIGHT, &moveX, &moveY);
	}
	int status;
	status = checkMazeUnit(maze, moveX, moveY, information);

	if (status == 1 || status == 8 || status == 9) {
		return;
	}

	maze[playerY][playerX] = 0;
	maze[moveY][moveX] = 2;
}
