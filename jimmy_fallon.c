#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>


pthread_t next_id = 0;
sem_t lock;

void* phonecall(void* vargp); //phonecall routine prototype

int main (int argc, char** argv){
  int index = 0;
  int size = atoi(argv[1]);
  sem_init(&lock, 0, 1);
  pthread_t ids[size];
  pthread_t newIds[size]; //to cheese the ids
  while(index < size){
    newIds[index] = next_id;
    pthread_create(&ids[index], NULL, phonecall, &newIds[index]);
    index++;
    next_id++;
  }
  index = 0;
  while(index < size){
    pthread_join(ids[index], NULL);
    index++;
  }

  exit(0);
  return 0;
}

void* phonecall(void* vargp) {
  printf("Thread[%u] is calling, busy signal\n", *((unsigned int *)(vargp)));
  static int NUM_OPERATORS = 3;
  static int NUM_LINES = 5;
  static int connected = 0; // Callers that are connected
  static sem_t connected_lock;
  static sem_t operators;
  sem_init(&operators, 0, 3);
  sem_init(&connected_lock, 0, 1);

  sem_wait(&lock); //critical section of the call begins
  if(connected == NUM_LINES){
    printf("All lines currently busy.\n");
    //somehow get it to try again
    //sem_post(&lock);
  }
  else{
    sem_wait(&connected_lock); //critical section of connected begins
    connected++; //increment connected callers
    sem_post(&connected_lock); //exit critical section

    printf("Thread[%u] has available line, call ringing\n", *((unsigned int *)(vargp)));

    sem_wait(&operators);
    printf("Thread[%u] is speaking to the operator\n", *((unsigned int *)(vargp)));
    sleep(3);
    printf("Thread[%u] has bought a ticket!\n", *((unsigned int *)(vargp)));
    sem_post(&operators);
    printf("Thread[%u] has hung up!\n", *((unsigned int *)(vargp)));

    sem_wait(&connected_lock); //critical section of connected begins
    connected--; //increment connected callers
    sem_post(&connected_lock); //exit critical section
  }

  sem_post(&lock); //exit critical section


//Check if the connection can be made:
//  You'll need to test connected in a critical section
//  If the line is busy, exit the critical section, print a message, and try again
//  If the line is not busy, update connected, exit the critical section, and print a message, and continue to the next step.
//Wait for an operator to be available (use a counting semaphore)
//Print a message that the order is being taken by an operator
// a ticket order by sleeping for a few seconds (sleep(3))
//Print a message that the order is complete (and update the semaphore)
//Update connected (using a binary semaphore)
//Print a message that the call is over

}
