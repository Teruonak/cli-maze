#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// function sign declaration
void printMaze(int a, int b);
void doCommand(int *b, char c[], int m[50][50], int xj, int yj, int *item1,
		int *item2);
int fillMaze(FILE *f, char fileName[100], int (*maze)[50], int *rowLength, int *colLength, int *goal);

int main() {
	// configurations
	char fileName[100] = "mapa.txt";

	// variables
	FILE *file;
	int colLength, rowLength;
	int maze[50][50];
	int q, x_2, y_2;
	int item_1 = 0, item_2 = 0;
	char command[20];
	int goal[3][2];
	int errorStatus[5] = {0,0,0,0,0};

	errorStatus = fillMaze(file, fileName, maze, &rowLength, &colLength, goal);

	if (errorStatus[0][1]) {
				puts("Could not open file");
				return 0;
	}
	if (errorStatus[1][1]) {
				puts("The file " + fileName + " do not follow the pattern.");
				return 0;
	}
	if (errorStatus[2][1]) {
		puts("The length of row: " + rowLength + " or column: " + colLength + " is lower than 1 or greater than 50");
		return 0;
	}
	if (errorStatus[3][1]) {
		puts("Has more than one goal.");
		return 0;
	}
	if (errorStatus[4][1]) {
		puts("");
		return 0;
	}

	q = 80;

	while (goal[0] == 3 || goal[1] == 4 || goal[2] == 5) {
		system("cls");

		printMaze(rowLength, colLength, maze);

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

int *fillMaze(FILE *f, char fileName[100], int (*maze)[50], int *rowLength, int *colLength, int *goal) {
	int errorStatus[5] = {0,0,0,0,0};
	f = fopen(fileName, "r");
	if (!f) {
		errorStatus[0] = 1;
		return errorStatus;
	}
	// getting the data from file
	fscanf(f, "%d", rowLength);
	fscanf(f, "%d", colLength);
	if (rowLength < 1 || rowLength > 50 || colLength < 1 || colLength > 50) {
		errorStatus[2] = 1;
	}
	int i,j;
	// init flag for goals. If in the end of for loop the flag > 1, has more than 1 same goal;
	goal[0][1] = 0;
	goal[1][1] = 0;
	goal[2][1] = 0;
	for (i = 0; i < *rowLength; i++) {
		for (j = 0; j < *colLength; j++) {
			fscanf(f, "%d", &maze[i][j]);
			// get the goal position and increment the flag
			switch (maze[i][j]) {
			case 3:
				goal[0][0] = maze[i][j];
				goal[0][1]++;
				break;
			case 4:
				goal[1] = maze[i][j];
				goal[1][1]++;
				break;
			case 5:
				goal[2] = maze[i][j];
				goal[2][1]++;
				break;
			}
			if (maze[i][j] > 9 || maze[i][j] < 0) {
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

int positionPlayer(int position, int command){

}

void printMaze(int rowLength, int colLength, int maze[]) {
	int i, j;
	for (i = 0; i < rowLength; i++) {
		for (j = 0; j < colLength; j++) {
			if (maze[i][j] == 2) {
				setXYPlayer();
				x_2 = j;
				y_2 = i;
			}
			printMaze(maze[i][j], q);
		}
		printf("\n");
	}

	if (a == 0) {
		printf(" ");
	}
	if (a == 1) {
		printf("x");
	}
	if (a == 2 && b % 4 == 0) {
		printf("v");
	}
	if (a == 2 && b % 4 == 1) {
		printf(">");
	}
	if (a == 2 && b % 4 == 2) {
		printf("^");
	}
	if (a == 2 && b % 4 == 3) {
		printf("<");
	}
	if (a == 3) {
		printf("O");
	}
	if (a == 4) {
		printf("O");
	}
	if (a == 5) {
		printf("O");
	}
	if (a == 6) {
		printf("B");
	}
	if (a == 7) {
		printf("A");
	}
	if (a == 8) {
		printf("1");
	}
	if (a == 9) {
		printf("2");
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
