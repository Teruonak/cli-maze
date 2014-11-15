#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// function sign declaration
void doCommand(int *b, char c[], int m[50][50], int xj, int yj, int *item1,
		int *item2);
int fillMaze(FILE *f, int (*maze)[50], int *rowLength,
		int *colLength, int *goal, int *errorStatus);

void printMaze(int rowLength, int colLength, int maze[50][50],
		int playerDirection, int *playerX, int *playerY);
void printMazeUnit(int unit, int playerDirection);

int main() {
	// configurations
	char fileName[100] = "mapa.txt";

	// variables
	FILE *file;
	int maze[50][50];
	int colLength, rowLength;
	int playerDirection = 0, playerX, playerY;
	int numberItem1 = 0;
	int nubmerItem2 = 0;
	char command[20];
	int *goal[3];
	int errorStatus[5] = { 0, 0, 0, 0, 0 };

	puts("Started");

	file = fopen(fileName, "r");
	if (!file) {
		printf("Error to open the file: %s", fileName);
		exit(0);
	}
	fillMaze(file, maze, &rowLength, &colLength, &goal[0],
			errorStatus);

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

	// test fillMaze
	for (int i = 0; i < rowLength; ++i) {
		for (int j = 0; j < colLength; ++j) {
			printf("%d", maze[i][j]);
		}
		puts("");
	}

//	while (goal[0] == 3 || goal[1] == 4 || goal[2] == 5) {
	system("cls");

//		printMaze(rowLength, colLength, maze, playerDirection, &playerX,
//				&playerY);

	puts("");
	puts("");
//		printf("item 1: %d", numberItem1);
//		printf("item 2: %d", numberItem1);
	puts("");
	puts("");
	printf("Comando: ");
//	(command);
//		doCommand(&q, command, maze, x_2, y_2, &item_1, &item_2);
//	}

	if (goal[0] != 3 && goal[1] != 4 && goal[2] != 5) {
		printf("voce venceu!!");
	} else {
		printf("Game over!");
	}

	puts("Stopped");

	return 0;
}

int fillMaze(FILE *f, int (*maze)[50], int *rowLength,
		int *colLength, int *goal, int *errorStatus) {
	int c; // each char
	// init variables
	*rowLength = 0;
	*colLength = 0;
	int row = -1;
	int col = -1;
	int *pRowAndCol = rowLength;
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
			printf("%d\n", *pRowAndCol);
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
			col = -1;
			continue;
		}
		col++;
//		printf("maze[%d][%d] = %c\n", row, col, c); // DEBUG
		maze[row][col] = c - '0';
	}

	fclose(f);

	return errorStatus;
}

void printMaze(int rowLength, int colLength, int maze[50][50],
		int playerDirection, int *playerX, int *playerY) {
//	int i, j;
//	for (i = 0; i < rowLength; i++) {
//		for (j = 0; j < colLength; j++) {
//			if (maze[i][j] == 2) {
//				*playerX = j;
//				*playerY = i;
//			}
//			printMazeUnit(maze[i][j], playerDirection);
//		}
//		printf("\n");
//	}
}

char getPlayerDirection(int playerDirection, char command[]) {
	char direction = 'v';

	if (command) {
		if (strcmp(command, "right") == 0) {
			playerDirection++;
		} else if (strcmp(command, "left") == 0) {
			playerDirection += 3;
		} else if (strcmp(command, "back") == 0) {
			playerDirection += 2;
		}
	}

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

void printMazeUnit(int unit, int playerDirection) {
	switch (unit) {
	case 0:
		printf(" ");
		break;
	case 1:
		printf("x");
		break;
	case 2:
		printf("%c", getPlayerDirection(playerDirection, 0));
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

void doCommand(int *b, char c[], int m[][50], int xj, int yj, int *item1,
		int *item2) {
	char left[] = "turn left", right[] = "turn right", c_180[] = "turn 180",
			collect[] = "collect", use_1[] = "use 1", use_2[] = "use 2";
	if (strcmp(c, left) == 0) {
		*b = *b + 1;
	} else if (strcmp(c, right) == 0) {
		*b = *b - 1;
	} else if (strcmp(c, c_180) == 0) {
		*b = *b + 2;
	} else if (strcmp(c, collect) == 0 && *b % 4 == 0 && m[yj + 1][xj] == 8) {
		(*item1)++;
		m[yj + 1][xj] = 0;
	} else if (strcmp(c, collect) == 0 && *b % 4 == 1 && m[yj][xj + 1] == 8) {
		(*item1)++;
		m[yj][xj + 1] = 0;
	} else if (strcmp(c, collect) == 0 && *b % 4 == 2 && m[yj - 1][xj] == 8) {
		(*item1)++;
		m[yj - 1][xj] = 0;
	} else if (strcmp(c, collect) == 0 && *b % 4 == 3 && m[yj][xj - 1] == 8) {
		(*item1)++;
		m[yj][xj - 1] = 0;
	} else if (strcmp(c, collect) == 0 && *b % 4 == 0 && m[yj + 1][xj] == 9) {
		(*item2)++;
		m[yj + 1][xj] = 0;
	} else if (strcmp(c, collect) == 0 && *b % 4 == 1 && m[yj][xj + 1] == 9) {
		(*item2)++;
		m[yj][xj + 1] = 0;
	} else if (strcmp(c, collect) == 0 && *b % 4 == 2 && m[yj - 1][xj] == 9) {
		(*item2)++;
		m[yj - 1][xj] = 0;
	} else if (strcmp(c, collect) == 0 && *b % 4 == 3 && m[yj][xj - 1] == 9) {
		(*item2)++;
		m[yj][xj - 1] = 0;
	} else if (strcmp(c, use_1) == 0 && *b % 4 == 0 && item1 > 0
			&& m[yj + 1][xj] == 6) {
		m[yj + 1][xj] = 0;
		item1--;
	} else if (strcmp(c, use_1) == 0 && *b % 4 == 1 && item1 > 0
			&& m[yj][xj + 1] == 6) {
		m[yj][xj + 1] = 0;
		item1--;
	} else if (strcmp(c, use_1) == 0 && *b % 4 == 2 && item1 > 0
			&& m[yj - 1][xj] == 6) {
		m[yj - 1][xj] = 0;
		item1--;
	} else if (strcmp(c, use_1) == 0 && *b % 4 == 0 && item1 > 0
			&& m[yj][xj - 1] == 6) {
		m[yj][xj - 1] = 0;
		item1--;
	} else if (strcmp(c, use_2) == 0 && *b % 4 == 0 && item1 > 0
			&& m[yj + 1][xj] == 7) {
		m[yj + 1][xj] = 0;
		item2--;
	} else if (strcmp(c, use_2) == 0 && *b % 4 == 1 && item1 > 0
			&& m[yj][xj + 1] == 7) {
		m[yj][xj + 1] = 0;
		item2--;
	} else if (strcmp(c, use_2) == 0 && *b % 4 == 2 && item1 > 0
			&& m[yj - 1][xj] == 7) {
		m[yj - 1][xj] = 0;
		item2--;
	} else if (strcmp(c, use_2) == 0 && *b % 4 == 3 && item1 > 0
			&& m[yj][xj - 1] == 7) {
		m[yj][xj - 1] = 0;
		item2--;
	} else {
		printf("\nERRO: comando invalido!");
	}
}
