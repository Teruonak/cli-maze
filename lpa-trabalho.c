#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// function sign declaration
void printMaze(int a, int b);
void doCommand(int *b, char c[], int m[50][50], int xj, int yj, int *item1,
		int *item2);
int *fillMaze(FILE *f, char fileName[100], int (*maze)[50], int *rowLength,
		int *colLength, int *goal, int errorStatus);

int main() {
	// configurations
	char fileName[100] = "mapa.txt";

	// variables
	FILE *file;
	int maze[50][50];
	int colLength, rowLength;
	int playerDirection = 0, playerX, playerY;
	int numberItem1 = 0, nubmerItem2 = 0;
	char command[20];
	int *goal[3];
	int errorStatus[5] = { 0, 0, 0, 0, 0 };

	fillMaze(file, fileName, maze, &rowLength, &colLength, goal, errorStatus);

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
				"The length of row: %d or column: %d is lower than 1 or greater than 50", rowLength, colLength);
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

	playerDirection = 0;

	while (goal[0] == 3 || goal[1] == 4 || goal[2] == 5) {
		system("cls");

		printMaze(rowLength, colLength, maze, playerDirection, &playerX,
				&playerY);

		puts("");
		puts("");
		printf("item 1: %d", item_2);
		printf("item 2: %d", item_2);
		puts("");
		puts("");
		printf("Comando: ");
		gets(command);
		doCommand(&q, command, maze, x_2, y_2, &item_1, &item_2);
	}

	if (goal[0] != 3 && goal[1] != 4 && goal[2] != 5) {
		printf("voce venceu!!");
	} else {
		printf("Game over!");
	}

	return 0;
}

int *fillMaze(FILE *f, char fileName[100], int (*maze)[50], int *rowLength,
		int *colLength, int *goal, int *errorStatus) {
	f = fopen(fileName, "r");
	if (!f) {
		errorStatus[0] = 1;
		return errorStatus;
	}
	// getting the data from file
	fscanf(f, "%d", rowLength);
	fscanf(f, "%d", colLength);
	if (*rowLength < 1 || *rowLength > 50 || *colLength < 1 || *colLength > 50) {
		errorStatus[2] = 1;
	}
	int i, j;
	// init flag for goals. If in the end of for loop the flag > 1, has more than 1 same goal;
	goal[0] = 0;
	goal[1] = 0;
	goal[2] = 0;
	for (i = 0; i < *rowLength; i++) {
		for (j = 0; j < *colLength; j++) {
			fscanf(f, "%d", &maze[i][j]);
			// get the goal position and increment the flag
			switch (maze[i][j]) {
			case 3:
				goal[0][0] = &maze[i][j];
				goal[0][1]++;
				break;
			case 4:
				goal[1][0] = &maze[i][j];
				goal[1][1]++;
				break;
			case 5:
				goal[2][0] = &maze[i][j];
				goal[2][1]++;
				break;
			}
			if (maze[i][j] < 0 || maze[i][j] > 9) {
				errorStatus[4] = 1;
			}
		}
	}
	// print the error with goal flag
	for (int i = 0; i < 3; ++i) {
		if (goal[i][1] > 1) {
			errorStatus[3] = 1;
		}
	}

	return errorStatus;
}

void printMaze(int rowLength, int colLength, int maze[], int playerDirection,
		int *playerX, int * playerY) {
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
