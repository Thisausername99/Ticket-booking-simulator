#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <stdbool.h>

#include <pthread.h>
#include <semaphore.h>


int next_id;
sem_t lock;
int num_ticket =240;

void* phonecall(void* vargp); //phonecall routine prototype

int main (int argc, char** argv){
  int size = atoi(argv[1]);
  pthread_t ids[size];
  //pthread_t tid;
 
  for(int n=0;n<size;++n){
    pthread_t tid;
    //newIds[index] = next_id;
    pthread_create(&tid, NULL, phonecall, NULL);
    ids[n]=tid;
    //next_id++;
  }
  //index = 0;
  for(int n=0;n<size;++n){
    pthread_join(ids[n], NULL);
    //printf("thread %i exit \n", n );
  }


  printf("TICKETS REMAIN: %i TICKETS\n",num_ticket);
  exit(0);
  return 0;
}



void* phonecall(void* vargp) {
  int call_id;
  static sem_t id_lock;
  sem_init(&id_lock,0,1);
  sem_wait(&id_lock);
  next_id++;
  sem_post(&id_lock);
  call_id=next_id;
 

  static int NUM_OPERATORS = 3;
  static int NUM_LINES = 5;
  static int connected = 0; // Callers that are connected
  static sem_t connected_lock;
  static sem_t operators;
  sem_init(&operators, 0, 3);
  sem_init(&connected_lock, 0, 1);
  bool found=false;
  printf("Thread[%d] is calling, busy signal\n", call_id);
  
  sem_wait(&connected_lock);
  while(1){
  //sem_wait(&connected_lock);
  if(connected != NUM_LINES){
    found=true;
    connected++; //increment connected callers
    break;
    sem_post(&connected_lock); //exit critical section
    //break;
    
  }
  else{
    //sem_wait(&connected_lock); //critical section of connected begins
    printf("Thread[%d] is declined, lines are busy\n", call_id);
    break;   
      }
  }
  sem_post(&connected_lock); 

    sem_wait(&operators);
    printf("Thread[%d] is speaking to operator\n", call_id);//*((unsigned int *)(vargp)));
    num_ticket--;
    sleep(3);
    printf("Thread[%d] has bought a ticket!\n", call_id); //*((unsigned int *)(vargp)));
    sem_post(&operators);
    
    sem_wait(&connected_lock); //critical section of connected begins
    connected--; //increment connected callers
    sem_post(&connected_lock); //exit critical section

    /*sem_wait(&connected_lock); //critical section of connected begins
    connected--; //increment connected callers
    sem_post(&connected_lock); //exit critical section*/
    
    printf("Thread[%d] has hung up!\n", call_id);

    sem_destroy(&connected_lock);
    sem_destroy(&operators);
    sem_destroy(&id_lock);
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
return NULL;
}
