/*MC504 - Sudoku - Modo Dica
 * Nomes: Guilherme Zanelato - ra119494
 * 		  João Chencci - ra119637
 * 		  Andre Tamanaha - ra116134
 * */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef struct {
	char matrix[9][9];
	char clues[9][9][12];
	int i, j;
} Parameter;

void* findClues(void *param);

int main() {

	Parameter p;
	int i, j, k = 0; //Contadores. i-linha, j-coluna, k-thread count

	pthread_t thr[81];

	printf("Entre com a Matriz:\n");
	//LEITURA DA MATRIZ
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++) {
			scanf(" %c", &p.matrix[i][j]);
		}
	}

	//DICAS
	p.i = 0;
	p.j = 0;
	findClues((void*) &p);
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++) {
			p.i = i;
			p.j = j;
			pthread_create(&thr[k++], NULL, findClues, (void*) &p);
		}
	}

	for (k = 0; k < 81; k++) {
		pthread_join(thr[k], NULL);
	}

	/*for(i=0; i<9; i++){
	 for(j=0; j<9; j++){
	 p.i=i;
	 p.j=j;
	 findClues((void*)&p);
	 }
	 }*/
	//SINGLETHREAD
	//MATRIZ IMPRESSA
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++) {
			for (k = 0; p.clues[i][j][k] != '\0'; k++) {
				if (p.clues[i][j][k] != 'N') {
					printf("%c", p.clues[i][j][k]);
				}
			}
			printf("     ");
		}
		printf("\n");
	}

	return 0;

}
;

void* findClues(void *param) {

	Parameter p = *(Parameter*) param;

	int a, b, k = 0;
	int buffer[9];

	printf("OI! EU ESTOU NA THREAD DE POSICAO: %d%d\n", p.i, p.j);

	if (p.matrix[p.i][p.j] != 'X') {
		(*(Parameter*) param).clues[p.i][p.j][0] = p.matrix[p.i][p.j];
		(*(Parameter*) param).clues[p.i][p.j][1] = '\0';
	} else {

		//Preenche todas dicas possiveis
		(*(Parameter*) param).clues[p.i][p.j][0] = '(';
		(*(Parameter*) param).clues[p.i][p.j][1] = '1';
		(*(Parameter*) param).clues[p.i][p.j][2] = '2';
		(*(Parameter*) param).clues[p.i][p.j][3] = '3';
		(*(Parameter*) param).clues[p.i][p.j][4] = '4';
		(*(Parameter*) param).clues[p.i][p.j][5] = '5';
		(*(Parameter*) param).clues[p.i][p.j][6] = '6';
		(*(Parameter*) param).clues[p.i][p.j][7] = '7';
		(*(Parameter*) param).clues[p.i][p.j][8] = '8';
		(*(Parameter*) param).clues[p.i][p.j][9] = '9';
		(*(Parameter*) param).clues[p.i][p.j][10] = ')';
		(*(Parameter*) param).clues[p.i][p.j][11] = '\0';

		//Verifica Horizontal
		for (a = 0; a < 9; a++) {
			for (b = 1; b < 10; b++) {
				if (p.matrix[p.i][a]
						== (*(Parameter*) param).clues[p.i][p.j][b]) {
					(*(Parameter*) param).clues[p.i][p.j][b] = 'N';
				}
			}
		}

		//Verifica Vertical
		for (a = 0; a < 9; a++) {
			for (b = 1; b < 10; b++) {
				if (p.matrix[a][p.j]
						== (*(Parameter*) param).clues[p.i][p.j][b]) {
					(*(Parameter*) param).clues[p.i][p.j][b] = 'N';
				}
			}
		}

		//Passa Submatriz Relativa a posicao para Buffer
		int x; //numero da submatriz (de 0 a 8)

		if (p.i >= 0 && p.i <= 2) {
			if (p.j >= 0 && p.j <= 2) {
				x = 0;
			}
			if (p.j >= 3 && p.j <= 5) {
				x = 1;
			}
			if (p.j >= 6 && p.j <= 8) {
				x = 2;
			}
		}
		if (p.i >= 3 && p.i <= 5) {
			if (p.j >= 0 && p.j <= 2) {
				x = 3;
			}
			if (p.j >= 3 && p.j <= 5) {
				x = 4;
			}
			if (p.j >= 6 && p.j <= 8) {
				x = 5;
			}
		}
		if (p.i >= 6 && p.i <= 8) {
			if (p.j >= 0 && p.j <= 2) {
				x = 6;
			}
			if (p.j >= 3 && p.j <= 5) {
				x = 7;
			}
			if (p.j >= 6 && p.j <= 8) {
				x = 8;
			}
		}

		for (a = x - (x % 3); a < x - (x % 3) + 3; a++) {
			for (b = (x % 3) * 3; b < (x % 3) * 3 + 3; b++) {
				buffer[k++] = p.matrix[a][b];
			}
		}

		//Verifica Submatriz
		for (k = 0; k < 9; k++) {
			for (b = 1; b < 10; b++) {
				if (buffer[k] == (*(Parameter*) param).clues[p.i][p.j][b]) {
					(*(Parameter*) param).clues[p.i][p.j][b] = 'N';
				}
			}
		}

	}
	sleep(1);
	return NULL;
}
