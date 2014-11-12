#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void im(int a, int b);
void aplica(int *b, char c[], int m[][50], int xj, int yj, int *item1,
		int *item2);

void im(int a, int b) {
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

void aplica(int *b, char c[], int m[][50], int xj, int yj, int *item1,
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
		printf("\n\ncomando: ");
		gets(c);
		aplica(b, c, m, xj, yj, item1, item2);
	}
}
int main() {
	FILE *f;
	int x, y, i, j;

	f = fopen("mapa.txt", "r");
	fscanf(f, "%d", &y);
	fscanf(f, "%d", &x);

	int mapa[y][x];
	int q, x_2, y_2;
	int item_1 = 0, item_2 = 0;
	char c[20];
	int *p3, *p4, *p5;

	for (i = 0; i < y; i++) {
		for (j = 0; j < x; j++) {
			fscanf(f, "%d", &mapa[i][j]);
			if (mapa[i][j] == 3) {
				p3 = &mapa[i][j];
			}
			if (mapa[i][j] == 4) {
				p4 = &mapa[i][j];
			}
			if (mapa[i][j] == 5) {
				p5 = &mapa[i][j];
			}
		}
	}

	int count = 0;

	for (i = 0; i < y; i++) {
		for (j = 0; j < x; j++) {
			if (mapa[i][j] == 2) {
				count++;
			}
		}
	}

	if (count > 1) {
		printf("Há mais de um jogador em campo!");
		return 0;
	}
	if (count == 0) {
		printf("Não há jogador em campo!");
		return 0;
	}

	q = 80;

	while (*p3 == 3 || *p4 == 4 || *p5 == 5) {
		system("cls");
		for (i = 0; i < y; i++) {
			for (j = 0; j < x; j++) {
				if (mapa[i][j] == 2) {
					x_2 = j;
					y_2 = i;
				}
				im(mapa[i][j], q);
			}
			printf("\n");
		}
		printf("\n\nitem 1: %d", item_2);
		printf("\nitem 2: %d", item_2);
		printf("\n\ncomando: ");
		gets(c);
		aplica(&q, c, mapa, x_2, y_2, &item_1, &item_2);
	}

	if (*p3 != 3 && *p4 != 4 && *p5 != 5) {
		printf("voce venceu!!");
	} else {
		printf("Game over!");
	}

	return 0;
}
