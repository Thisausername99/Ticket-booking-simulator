#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#define NUM_OPERATORS 3


static int next_id; //global variable for call ids
static sem_t id_lock; //semaphore for next_id
static sem_t connected_lock; //semaphore for connected
static sem_t operators; //semaphore for operators

void * phonecall(void * vargp); //phonecall routine prototype

int main(int argc, char ** argv) {
  sem_init(&operators, 0, NUM_OPERATORS); //initialize operator counting semaphore
  sem_init(&connected_lock, 0, 1); //initialize connected binary semaphore
  sem_init(&id_lock, 0, 1); //initialize next_id binary semaphore

  if (argc <= 1) { //check if there is input
    printf("ERROR: no call input\n");
    return -1; 
  }
  
  int size = atoi(argv[1]); //convert the string form of the number of iterations argument to an int
  pthread_t ids[size]; //array of pthread_t to store thread ids

  for (int n = 0; n < size; ++n) { //loop to create threads
    pthread_create(&ids[n], NULL, phonecall, NULL); //creates threads and stores their ids in the ids array
  }

  for (int n = 0; n < size; ++n) { //loop to join threads
    pthread_join(ids[n], NULL); //joins thread using the id in the array
  }

  sem_destroy(&connected_lock); //destroys connected semaphore
  sem_destroy(&operators); //destroys operators semaphore
  sem_destroy(&id_lock); //destroys next_id semaphore
  return 0;
}

void * phonecall(void * vargp) {
  int call_id; //instantiate call_id
  sem_wait(&id_lock); //locks next_id semaphore, start of critical section
    next_id++; //increment next_id
  sem_post(&id_lock); //unlocks next_id semaphore, end of critical section
  call_id = next_id; //sets call_id to the current next_id
  int print = 0; //boolean to ensure the busy signal line is printed once

  static int NUM_LINES = 5; //max number of lines that can be in the "queue"
  //static int NUM_OPERATORS = 3; //max number of operators that can sell tickets
  static int connected = 0; //callers that are connected

  while (1) { //loop to keep the callers in until they can buy a ticket
    sem_wait(&connected_lock);
    if (connected == NUM_LINES) {
      sem_post(&connected_lock); //unlocks connected semaphore, end of crititcal section
      if (print == 0) { //if busy signal line not printed yet
        printf("Thread[%d] has a busy signal...\n", call_id);
        //sleep(1);
        print = 1; //sets print to be true since line has been printed
      }
    } else {
        connected++; //increment connected callers
      sem_post(&connected_lock); //unlocks connected semaphore, end of crititcal section
      printf("Thread[%d] has been connected to a line!\n", call_id);
      break;
    }
  }

  sem_wait(&operators); //locks operators semaphore, start of critical section
    printf("Thread[%d] is speaking to operator\n", call_id);
    sleep(3);
    printf("Thread[%d] has bought a ticket!\n", call_id);
    sem_wait(&connected_lock); //locks connected semaphore, start of critical section
      connected--; //decrement connected callers
    sem_post(&connected_lock); //unlockslocks operators semaphore, end of critical section
  sem_post(&operators); //unlocks operators semaphore, end of critical section


  printf("Thread[%d] has hung up!\n", call_id);
  return NULL;
}
