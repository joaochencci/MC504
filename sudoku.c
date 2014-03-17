/*MC504 - Sudoku - Modo Solucao*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef struct{
  char matrix[9][9];
  char clues[9][9][12];
  int solved[9][9];
  int i, j;
} Parameter;

void* findClues(void *param);

int main(){

  Parameter p;
  int i, j, k=0; //Contadores. i-linha, j-coluna, k-thread count
  int correct, noOfClues; //Numero de elementos corretos
  char c;
  
  pthread_t thr[81];
  
  printf("Entre com a Matriz:\n");
  //LEITURA DA MATRIZ
  for(i=0; i<9; i++){
    for(j=0; j<9; j++){
      scanf(" %c", &p.matrix[i][j]);
    }
  }
  
  //ZERA MATRIZ FLAG SOLVED
  for(i=0; i<9; i++){
    for(j=0; j<9; j++){
      p.solved[i][j]=0;
    }
  }
  
  while(correct<81){ //eh preciso que os 81 elementos estejam corretos para o sudoku estar
  
    //DICAS
    p.i=0;
    p.j=0;
    findClues((void*)&p);
    for(i=0; i<9; i++){
      for(j=0; j<9; j++){
	p.i=i;
	p.j=j;
	pthread_create(&thr[k++], NULL, findClues, (void*) &p);
      }
    }
    for(k=0; k<81; k++){
      pthread_join(thr[k], NULL);
    }
    
    //DEIXA ELEMENTOS OPCOES UNICAS NA DICA CORRETOS
    for(i=0; i<9; i++){
      for(j=0; j<9; j++){
	if(p.solved[i][j]==1) continue;
	else{
	  noOfClues = 0;
	  for(k=0; p.clues[i][j][k]!='\0'; k++){
	    if(p.clues[i][j][k]!='N'){
	      c = p.clues[i][j][k];
	      noOfClues += 1;
	    }
	  }
	  if(noOfClues==1){
	    p.solved[i][j]=1;
	  }
	}
      }
    }
  
    //CHECA SE SUDOKU ESTA CORRETO
    correct = 0;
    for(i=0; i<9; i++){
      for(j=0; j<9; j++){
	correct += p.solved[i][j];
      }
    }
    
  } //fim do While
  
  //MATRIZ IMPRESSA
  printf("Solucao:\n");
  for(i=0; i<9; i++){
    for(j=0; j<9; j++){
      for(k=0; p.clues[i][j][k]!='\0'; k++){
	if(p.clues[i][j][k]!='N'){
	  printf("%c", p.clues[i][j][k]);
	}
      }
      printf(" ");
    }
    printf("\n");
  }
  
  return 0;

};

void* findClues(void *param){
  
  Parameter p = *(Parameter*)param;
  
  int a, b, k=0;
  int buffer[9];
  
  if(p.matrix[p.i][p.j]!='X'){
    (*(Parameter*)param).clues[p.i][p.j][0] = p.matrix[p.i][p.j];
    (*(Parameter*)param).clues[p.i][p.j][1] = '\0';
    (*(Parameter*)param).solved[p.i][p.j] = 1;
  }
  else if((*(Parameter*)param).solved[p.i][p.j] == 1){
    return NULL;
  }
  else{
    
    //Preenche todas dicas possiveis
    (*(Parameter*)param).clues[p.i][p.j][0] = 'N';
    (*(Parameter*)param).clues[p.i][p.j][1] = '1';
    (*(Parameter*)param).clues[p.i][p.j][2] = '2';
    (*(Parameter*)param).clues[p.i][p.j][3] = '3';
    (*(Parameter*)param).clues[p.i][p.j][4] = '4';
    (*(Parameter*)param).clues[p.i][p.j][5] = '5';
    (*(Parameter*)param).clues[p.i][p.j][6] = '6';
    (*(Parameter*)param).clues[p.i][p.j][7] = '7';
    (*(Parameter*)param).clues[p.i][p.j][8] = '8';
    (*(Parameter*)param).clues[p.i][p.j][9] = '9';
    (*(Parameter*)param).clues[p.i][p.j][10] = 'N';
    (*(Parameter*)param).clues[p.i][p.j][11] = '\0';
    
    //Verifica Horizontal
    for(a=0; a<9; a++){
      for(b=1; b<10; b++){
	if(p.matrix[p.i][a]==(*(Parameter*)param).clues[p.i][p.j][b]){
	  (*(Parameter*)param).clues[p.i][p.j][b] = 'N';
	}
      }
    }
    
    //Verifica Vertical
    for(a=0; a<9; a++){
      for(b=1; b<10; b++){
	if(p.matrix[a][p.j]==(*(Parameter*)param).clues[p.i][p.j][b]){
	  (*(Parameter*)param).clues[p.i][p.j][b] = 'N';
	}
      }
    }
    
    //Passa Submatriz Relativa a posicao para Buffer
    int x; //numero da submatriz (de 0 a 8)
    
    if(p.i>=0&&p.i<=2){
      if(p.j>=0&&p.j<=2){
	x = 0;
      }
      if(p.j>=3&&p.j<=5){
	x = 1;
      }
      if(p.j>=6&&p.j<=8){
	x = 2;
      }
    }
    if(p.i>=3&&p.i<=5){
      if(p.j>=0&&p.j<=2){
	x = 3;
      }
      if(p.j>=3&&p.j<=5){
	x = 4;
      }
      if(p.j>=6&&p.j<=8){
	x = 5;
      }
    }
    if(p.i>=6&&p.i<=8){
      if(p.j>=0&&p.j<=2){
	x = 6;
      }
      if(p.j>=3&&p.j<=5){
	x = 7;
      }
      if(p.j>=6&&p.j<=8){
	x = 8;
      }
    }
    
    for(a=x-(x%3); a<x-(x%3)+3; a++){
      for(b=(x%3)*3; b<(x%3)*3+3; b++){
	buffer[k++] = p.matrix[a][b];
      }
    }
    
    //Verifica Submatriz
    for(k=0; k<9; k++){
      for(b=1; b<10; b++){
	if(buffer[k]==(*(Parameter*)param).clues[p.i][p.j][b]){
	  (*(Parameter*)param).clues[p.i][p.j][b] = 'N';
	}
      }
    }
    
  }
  
  return NULL;
}
