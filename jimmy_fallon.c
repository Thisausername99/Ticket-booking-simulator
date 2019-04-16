#include <stdio.h>

#include <stdlib.h>

#include <unistd.h>

#include <stdbool.h>

#include <pthread.h>

#include <semaphore.h>


int next_id;
sem_t id_lock;
sem_t connected_lock;
sem_t operators;
int num_ticket = 240;

void * phonecall(void * vargp); //phonecall routine prototype

int main(int argc, char ** argv) {

  sem_init( & operators, 0, 3);
  sem_init( & connected_lock, 0, 1);
  sem_init( & id_lock, 0, 1);

  int index = 0;
  if (argc <= 1) {
    printf("ERROR: no call input\n");
    return -1;
  }

  int size = atoi(argv[1]);
  pthread_t ids[size];

  for (int n = 0; n < size; ++n) {
    pthread_t tid;
    pthread_create( & tid, NULL, phonecall, NULL);
    ids[n] = tid;
  }

  for (int n = 0; n < size; ++n) {
    pthread_join(ids[n], NULL);

  }

  sem_destroy( & connected_lock);
  sem_destroy( & operators);
  sem_destroy( & id_lock);
  printf("TICKETS REMAIN: %i TICKETS\n", num_ticket);
  return 0;

}

void * phonecall(void * vargp) {
  /*static sem_t id_lock;
  sem_init(&id_lock,0,1);*/

  int call_id;
  sem_wait( & id_lock);
  next_id++;
  sem_post( & id_lock);
  call_id = next_id;
  int print = 0;

  static int NUM_LINES = 5;
  static int NUM_OPERATORS = 3;
  static int connected = 0; // Callers that are connected
  /*static sem_t connected_lock;
  static sem_t operators;
  sem_init(&operators, 0, 3);
  sem_init(&connected_lock, 0, 1);*/

  while (1) {
    sem_wait( & connected_lock);
    if (connected == NUM_LINES) {
      sem_post( & connected_lock);
      if (print == 0) {
        printf("Thread[%d] has a busy signal...\n", call_id); //*((unsigned int *)(vargp)));
        print = 1;
      }
    } else {
      connected++; //increment connected callers
      //printf("Thread[%d] has been connected to a line!\n", call_id);
      sem_post( & connected_lock); //exit critical section
      printf("Thread[%d] has been connected to a line!\n", call_id);
      //sem_wait(&operators);
      sleep(1); // IF COMMENT THIS THEN PROGRAM WILL HANG
      break;
    }
  }

  sem_wait( & operators);
  printf("Thread[%d] is speaking to operator\n",call_id);
  num_ticket--;
  sleep(3);
  printf("Thread[%d] has bought a ticket!\n",call_id);

  sem_wait( & connected_lock); //critical section of connected begins
  connected--; //increment connected callers
  sem_post( & connected_lock); //exit critical section

  sem_post( & operators);

  printf("Thread[%d] has hung up!\n", call_id);

  return NULL;
}