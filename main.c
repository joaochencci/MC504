/*
 * main.c
 *
 *  Created on: 15/03/2014
 *      Author: Guilherme
 */


/*
 * Passagem de parÃ¢metros para a thread. Cada thread terÃ¡ um identificador Ãºnico!
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N_THR 10


void* f_thread(void *v) {
  int thr_id;
  sleep(1);
  thr_id = (int) v;
  printf("Thread %d.\n", thr_id);
  printf("Jo�o!");
  return NULL;
}



int main() {


  pthread_t thr[N_THR];
  int i;

  for (i = 0; i < N_THR; i++)
    pthread_create(&thr[i], NULL, f_thread, (void*) i);

  for (i = 0; i < N_THR; i++)
    pthread_join(thr[i], NULL);

  return 0;
}
