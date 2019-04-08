#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore>

int next_id;
sem_t lock;


void* phonecall(void* vargp) {
    static int NUM_OPERATORS = 3;
    static int NUM_LINES = 5;
    static int connected = 0;    // Callers that are connected
    static sem_t connected_lock;
    static sem_t operators;
}


void *thread(void *vargp) {
  pthread_t[5];
            
  // Does this code create a "race condition"?
  // Race Test:
  //  (1) If there is no race, then each thread would get a different
  //      value of i (received from the main thread).
  //  (2) If there is no race, the set of values printed to stdout
  //      would consist of one output for each value from 0 to 99.
  int i = *((int *)vargp);
  pthread_detach(pthread_self());
  printf("%d\n", i);
  return NULL;
}





int main (void){


}



