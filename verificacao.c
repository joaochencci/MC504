/*MC504 - Sudoku - Modo Dica
 * Nomes: Guilherme Zanelato - ra119494
 * 		  João Chencci - ra119637
 * 		  Andre Tamanaha - ra116134
 * */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> //IMPLEMENTAR THREADS!
int totalErrors = 0; //Inicialmente, nao ha erros

typedef struct {
	char matrix[9][9];
	int value;
} Parameter;

void* horizontalCheck(void *param); //Checa se ha erros nas linhas
void* verticalCheck(void *param); //Checa se ha erros nas colunas
void* submatrixCheck(void *param); //Checa se ha erros nas submatrizes

int main() {

	Parameter p;
	int i, j, k; //Contadores. i-linha, j-coluna, k-count

	pthread_t thr[27];

	printf("Entre com a Matriz:\n");
	//LEITURA DA MATRIZ
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++) {
			scanf(" %c", &p.matrix[i][j]);
		}
	}

	for (k = 0; k < 9; k++) {
		p.value = k;
		pthread_create(&thr[k], NULL, horizontalCheck, (void*) &p);
		pthread_create(&thr[k + 9], NULL, verticalCheck, (void*) &p);
		pthread_create(&thr[k + 18], NULL, submatrixCheck, (void*) &p);
	}

	for (k = 0; k < 27; k++) {
		pthread_join(thr[k], NULL);
	}

	//SE SUDOKU NAO TEM ERROS
	if (totalErrors == 0) {
		printf("O Sudoku esta correto.\n");
	}

	return 0;

}
;

void* horizontalCheck(void *param) {

	Parameter p = *(Parameter*) param;

	int a, b;
	int cnt = 0;

	for (a = 0; a < 9; a++) {
		cnt++; //Checa apenas numeros que ainda nao foram checados
		for (b = cnt; b < 9; b++) {
			if (p.matrix[p.value][a] == p.matrix[p.value][b]) {
				printf(
						"A linha %d contem mais de uma ocorrencia do numero %c.\n",
						p.value + 1, p.matrix[p.value][a]);
				totalErrors++;
				break;
			}
		}
	}

	//printf("Thr: %d\n", p.value); //DEBUG

	return NULL;

}
;

void* verticalCheck(void *param) {

	Parameter p = *(Parameter*) param;

	int a, b;
	int cnt = 0;

	for (a = 0; a < 9; a++) {
		cnt++; //Checa apenas numeros que ainda nao foram checados
		for (b = cnt; b < 9; b++) {
			if (p.matrix[a][p.value] == p.matrix[b][p.value]) {
				printf(
						"A coluna %d contem mais de uma ocorrencia do numero %c.\n",
						p.value + 1, p.matrix[a][p.value]);
				totalErrors++;
				break;
			}
		}
	}

	//printf("Thr: %d\n", p.value+9); //DEBUG

	return NULL;

}
;

void* submatrixCheck(void *param) {

	Parameter p = *(Parameter*) param;

	int a, b;
	int cnt = 0;

	int i, j, k = 0;
	int buffer[9];

	//Passa submatriz para um buffer (vetor)
	for (i = p.value - (p.value % 3); i < p.value - (p.value % 3) + 3; i++) {
		for (j = (p.value % 3) * 3; j < (p.value % 3) * 3 + 3; j++) {
			buffer[k++] = p.matrix[i][j];
		}
	}

	for (a = 0; a < 9; a++) {
		cnt++; //Checa apenas numeros que ainda nao foram checados
		for (b = cnt; b < 9; b++) {
			if (buffer[a] == buffer[b]) {
				printf(
						"A submatriz %d contem mais de uma ocorrencia do numero %c.\n",
						p.value + 1, buffer[a]);
				totalErrors++;
				break;
			}
		}
	}

	//printf("Thr: %d\n", p.value); //DEBUG

	return NULL;
}
