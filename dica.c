/*MC504 - Sudoku - Modo Dica*/

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
			printf("  ");
		}
		printf("\n");
	}

	return 0;

}
;

void* findClues(void *param) {

	Parameter p = *(Parameter*) param;

	int a, b;

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

	}

	return NULL;
}
