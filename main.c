/*
 * Projeto 01 - MC504 - 1s2014
 *
 * André Seiji Tamanaha			116134
 * Guilherme Costa Zanelato		119494
 * João Victor Chencci Marques	119637
 *
 * */

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
  printf("João!");
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
