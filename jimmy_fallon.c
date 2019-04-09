#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>


pthread_t next_id;
sem_t lock;


void* phonecall(void* vargp) {
  pthread_t tid=pthread_self();
  printf("This is a phone call from thread[%u]\n",(unsigned int)tid);
    /*static int NUM_OPERATORS = 3;
    static int NUM_LINES = 5;
    static int connected = 0;    // Callers that are connected
    static sem_t connected_lock;
    static sem_t operators;
    sem_t operators;
	sem_init(&operators, 0, 3);
//pthread_create
	sem_wait(&operators);
// Proceed with ticket ordering process
	sem_post(&operators);


//Print that an attempt to connect has been made.

*/



//Check if the connection can be made:
//You'll need to test connected in a critical section
//If the line is busy, exit the critical section, print a message, and try again
//If the line is not busy, update connected, exit the critical section, and print a message, and continue to the next step.
//Wait for an operator to be available (use a counting semaphore)
//Print a message that the order is being taken by an operator
// a ticket order by sleeping for a few seconds (sleep(3))
//Print a message that the order is complete (and update the semaphore)
//Update connected (using a binary semaphore)
//Print a message that the call is over

}


void *thread(void *vargp) {
  

  printf("making\n");
  pthread_t thread_arr[1];
  /*for(int n=0;n<5;++n){*/
  ++next_id;
  pthread_create(&next_id,NULL,phonecall,NULL);
  thread_arr[0]=next_id;
  //}
  //printf("This is a phone call\n");
  //for(int a=0;a<5;a++){
    pthread_join(thread_arr[0],NULL);
  //}

  return NULL;
}




int main (void){
pthread_t td1,td2,td3; // operator
pthread_create(&td1,NULL,thread,NULL);
pthread_create(&td2,NULL,thread,NULL);
pthread_create(&td3,NULL,thread,NULL);
pthread_join(tid1, NULL);
pthread_join(tid2, NULL);
pthread_join(tid3, NULL);

return 0;
}



