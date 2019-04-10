#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>

int next_id=1;
sem_t lock;
int num_call;

void* phonecall(void* vargp) {
    static int NUM_OPERATORS = 3;
    static int NUM_LINES = 5;
    static int connected = 0;    // Callers that are connected
    static sem_t connected_lock;
    static sem_t operators;
    sem_init(&connected_lock,0,1);
    sem_init(&operators,0,3);

  pthread_t tid=pthread_self();
  printf("This is a phone call from thread[%d]\n",next_id);
    if(connected==NUM_LINES){
      printf("The lines are busy, wait\n");

    }
    else{
      //++connected;
      sem_wait(&connected_lock);
      ++connected;
      printf("THREAD[%d] is speaking to operator\n",next_id);
      --num_call;
      sleep(3);
      --connected;
      sem_post(&connected_lock);
      //--connected;
    }
  printf("Call is over\n");

    /*
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
  
  pthread_t thread_arr[1];
  /*for(int n=0;n<5;++n){*/
  pthread_t tid;
  pthread_create(&tid,NULL,phonecall,&next_id);
  thread_arr[0]=tid;
  ++next_id;
  //}
  //printf("This is a phone call\n");
  //for(int a=0;a<5;a++){
    pthread_join(thread_arr[0],NULL);
  //}

  return NULL;
}




int main(int argc, char **argv) {
sem_init(&lock,0,1);

if (argc != 2) {
    printf("There no phone call\n");
    exit(0);
}

num_call=atoi(argv[0]);//conver number of call into integer

pthread_t tid1,tid2,tid3; // operator
pthread_create(&tid1,NULL,thread,NULL);
pthread_create(&tid2,NULL,thread,NULL);
pthread_create(&tid3,NULL,thread,NULL);
pthread_join(tid1, NULL);
pthread_join(tid2, NULL);
pthread_join(tid3, NULL);

return 0;
}



