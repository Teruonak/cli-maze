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
void doCommand(int (*maze)[50], char command[], int *playerDirection,
		int playerX, int playerY, int *amountItem1, int *amountItem2);
void collect(int (*maze)[50], int playerDirection, int playerX, int playerY,
		int *amountItem1, int *amountItem2);
void useItem(int (*maze)[50], int playerDirection, int itemX, int itemY,
		int *amountItem, int numberItem);
void move(int (*maze)[50], int movements, int playerDirection, int playerX,
		int playerY);
void movePlayer(int (*maze)[50], int times, int playerDirection, int *stepX,
		int *stepY);

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

	puts("Started");

	file = fopen(fileName, "r");
	if (!file) {
		printf("Error to open the file: %s", fileName);
	}
	fillMaze(file, maze, &rowLength, &colLength, goal, errorStatus);

	if (errorStatus[0]) {
		puts("Could not open file");
		return 0;
	}
	if (errorStatus[1]) {
		printf("The file %s do not follow the pattern.", fileName);
		return 0;
	}
	if (errorStatus[2]) {
		printf(
				"The length of row: %d or column: %d is lower than 1 or greater than 50",
				rowLength, colLength);
		return 0;
	}
	if (errorStatus[3]) {
		puts("Has more than one goal.");
		return 0;
	}
	if (errorStatus[4]) {
		puts("");
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
		printf("Command: ");
		fgets(command, 20, stdin);
		doCommand(maze, command, &playerDirection, playerX, playerY,
				&amountItem1, &amountItem2);
	}

	if (hasGoal(goal) == 0) {
		printf("You win!");
	} else {
		printf("Game over!");
	}

	puts("Stopped");

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
		//TODO get the number of each goal
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

void collect(int (*maze)[50], int playerDirection, int playerX, int playerY,
		int *amountItem1, int *amountItem2) {
	int holderItemX = playerX, holderItemY = playerY;
	getNext(playerDirection, &holderItemX, &holderItemY);

	if (maze[holderItemY][holderItemX] == 8) {
		(*amountItem1)++;
		maze[holderItemY][holderItemX] = 0;
	} else if (maze[holderItemY][holderItemX] == 9) {
		(*amountItem2)++;
		maze[holderItemY][holderItemX] = 0;
	}
}

void doCommand(int (*maze)[50], char command[], int *playerDirection,
		int playerX, int playerY, int *amountItem1, int *amountItem2) {
	char *pCmd;
	pCmd = strtok(command, " \n");
	if (pCmd == NULL) {
		exit(0); //TODO throw error
	}
	// turns
	if (strcmp(pCmd, "turn") == 0) {
		pCmd = strtok(NULL, " \n"); // get the next "parameter"
		if (strcmp(pCmd, "left") == 0) {
			(*playerDirection) += 3;
		} else if (strcmp(pCmd, "right") == 0) {
			(*playerDirection)++;
		} else if (strcmp(pCmd, "180") == 0) {
			(*playerDirection) += 2;
		} else {
			exit(0); //TODO throw some error like "invalid command"
		}
	}
	// collect
	else if (strcmp(pCmd, "collect") == 0) {
		collect(maze, *playerDirection, playerX, playerY, amountItem1,
				amountItem2);
	}
	// use
	else if (strcmp(pCmd, "use") == 0) {
		pCmd = strtok(NULL, " \n"); // get the next "parameter"
		if (pCmd == NULL) {
			exit(0); //TODO throw error
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
			exit(0); //TODO throw some error like "invalid command"
		}
		useItem(maze, *playerDirection, playerX, playerY, amountItem,
				numberItem);
	}
	// move
	else if (strcmp(pCmd, "move") == 0) {
		pCmd = strtok(NULL, " \n");
		if (pCmd == NULL) {
			exit(0); //TODO throw error
		}
		if (!isdigit(*pCmd)) {
			exit(0); //TODO throw error
		}
		int movements = ((*pCmd) - '0');
		move(maze, movements, *playerDirection, playerX, playerY);
	}
}

void useItem(int (*maze)[50], int playerDirection, int playerX, int playerY,
		int *amountItem, int numberItem) {
	int holderItemX = playerX, holderItemY = playerY;
	getNext(playerDirection, &holderItemX, &holderItemY);
	// do not have the item in maze
	if (maze[holderItemY][holderItemX] != numberItem) {
		exit(0); //TODO throw error
	}
	// do not have enough amount to use Item
	if (*amountItem < 1) {
		exit(0); //TODO throw error
	}
	maze[holderItemY][holderItemX] = 0;
	(*amountItem)--;
}

void move(int (*maze)[50], int movements, int playerDirection, int playerX,
		int playerY) {
	int holderX = playerX, holderY = playerY;
	movePlayer(maze, movements - 1, playerDirection, &holderX, &holderY);
	switch (maze[holderY][holderX]) {
	case 1:
		puts("Wall"); //TODO error Wall
		exit(0);
		break;
	case 6:
		puts("B"); //TODO error B
		exit(0);
		break;
	case 7:
		puts("A"); //TODO A
		exit(0);
		break;
	case 8:
		puts("1"); //TODO 1
		exit(0);
		break;
	case 9:
		puts("2"); //TODO 2
		exit(0);
		break;
	}
	maze[playerY][playerX] = 0;
	maze[holderY][holderX] = 2;
}

void movePlayer(int (*maze)[50], int times, int playerDirection, int *stepX,
		int *stepY) {
//	int holderItemX = stepX, holderItemY = stepY;
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
