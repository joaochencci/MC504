#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define HORIZONTAL_CHECK 1
#define VERTICAL_CHECK 2
#define SUBMATIX_CHECK 3
#define NONNUMBER_FOUND 4

int flag = 0; /* 1 - Error, 0 - Success */
char matrix[9][9];
char buffer[9][9];

int printNotValid(char *array, int type, int errorLocation);
int check(char **array,int item);
void* verticalCheck();
void* horizontalCheck();
void* blockCheck();
void* cleanBuffer();
void* totalCheck();

int main(int argc, char *argv[]) {
	FILE *data;
	if (argc != 2) {
		printf("erro");
		exit(1);
	} else
		data = fopen(argv[1], "r");


	/* Reading the Matrix from file */
	int c;
	int i = 0, j = 0;

	while ((c = getc(data)) != EOF) {
		if (c == ' ')
			continue;
		else if (c == '\n') {
			i = 0;
			j++;
		} else
			matrix[j][i++] = c;
	}

	pthread_t thr[9];
	int id[9], k;

	  for (k = 0; k < 9; k++) {
	    id[k] = k;
	    pthread_create(&thr[k], NULL, totalCheck, &id[k]);
	  }

	for (k = 0; k < 9; k++) {
		pthread_join(&thr[k], NULL);
	}

	/* Printing the matrix */
	printf("\n -- sudoku -- \n");
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++)
			printf("%c ", matrix[i][j]);
		printf("\n");
	}

	/* If the sudoku contains other than numbers, exit, printing error */
	printf("\n");
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++) {
			if ((matrix[i][j] < '0') || (matrix[i][j] > '9')) {
				printf(" Error (%d,%d): Sudoku can contain only numbers \n",
						i + 1, j + 1);
			}
		}
	}

	if (flag == 0)
		printf("\n The Sudoku is correct :)");

	printf("\n");
	return 0;
}

int check(char **array, int item) {
	int i, count;
	for (i = 0; i < 9; i++) {
		count = i;
		while (count < 9) {
			if (array[item][i] == array[item][++count])
				return 1;
		}
	}
	return 0;
}

void* totalCheck(void* item) {

	int aux =*(int*) item;
	verticalCheck(aux);
	horizontalCheck(aux);
	blockCheck(aux);
}

void* cleanBuffer(int item) {

	int i;
	for (i = 0; i < 9; i++) {
		buffer[item][i] = 'x';
	}
}

void* verticalCheck(int item) {
	int i, j;
	/* Vertical check */
	for (j = 0; j < 9; j++) {
		buffer[item][j] = matrix[ item][j];

		if (check(buffer,item) != 0) {
			printNotValid(buffer, VERTICAL_CHECK, j+1);
			flag = 1;
		}
	}
}

void* horizontalCheck(int item) {
	int i, j;
	/* Horizontal check */
	for (i = 0; i < 9; i++) {
		buffer[item][j] = matrix[i][item];

		if (check(buffer,item) != 0) {
			printNotValid(buffer, HORIZONTAL_CHECK, i+1);
			flag = 1;
		}
	}

}

void* blockCheck(int item) {
	/* Submatrix check */
	int count = 0;
	int icount = 0;
	int jcount = 0;
	int matcount = 0;
	int i, j;

	for (i = 0; i <= 6; i += 3) {
		for (j = 0; j <= 6; j += 3) {
			for (icount = 0, count = 0; icount < 3; icount++) {
				for (jcount = 0; jcount < 3; jcount++) {
					buffer[item][count++] = matrix[i + icount][j + jcount];
				}

			}

			++matcount;
			if (check(buffer,item) != 0) {
				printNotValid(buffer, SUBMATIX_CHECK, matcount);
				flag = 1;
			}
		}
	}
}

int printNotValid(char *array, int type, int errorLocation) {
	int i;
	flag = 1;
	if (type == HORIZONTAL_CHECK) {
		printf("\n Found error at row %d: \n\t", ++errorLocation);
		for (i = 0; i < 9; i++)
			printf("%c ", array[i]);
	} else if (type == VERTICAL_CHECK) {
		printf("\n Found error at column %d: \n", ++errorLocation);
		for (i = 0; i < 9; i++)
			printf("\n\t %c ", array[i]);
	} else if (type == SUBMATIX_CHECK) {
		printf("\n Found error at Submatrix %d: \n", errorLocation);
		for (i = 0; i < 9; i++) {
			printf("%c ", array[i]);
			if ((i == 2) || (i == 5))
				printf("\n");
		}

	}
}
