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
  int index = 0;

  if(argc <=1){
    printf("ERROR: no call input\n");
    return -1;
  }

  int size = atoi(argv[1]);
  sem_init(&lock, 0, 1);
  pthread_t ids[size];
  pthread_t tid;


  //pthread_t newIds[size]; //to cheese the ids
  for(int n=0;n<size;++n){

    pthread_create(&tid, NULL, phonecall, NULL);
    ids[n]=tid;
  }

  while(index < size){
    pthread_join(ids[index], NULL);
    index++;
  }

  printf("TICKETS REMAIN: %i TICKETS\n",num_ticket);
  exit(0);
  return 0;

}



void* phonecall(void* vargp) {
  int call_id;
  sem_t id_lock;
  sem_init(&id_lock,0,1);
  sem_wait(&id_lock);
  next_id++;
  sem_post(&id_lock);
  call_id=next_id;
  int print = 0;
  
  static int NUM_OPERATORS = 3;
  static int connected = 0; // Callers that are connected
  static sem_t connected_lock;
  static sem_t operators;
  sem_init(&operators, 0, 3);
  sem_init(&connected_lock, 0, 1);
  bool done=false;
  printf("Thread[%d] is calling...!\n", call_id); //*((unsigned int *)(vargp)));


  while(1){
    sem_wait(&connected_lock);
    if(connected >= NUM_OPERATORS){
      sem_post(&connected_lock);
      if(print == 0){
        printf("Thread[%d] has a busy signal...\n", call_id); //*((unsigned int *)(vargp)));
        print = 1;
      }
    }
    else{
      num_ticket--;
      connected++; //increment connected callers
      sem_post(&connected_lock); //exit critical section
      printf("Thread[%d] has been connected to an operator!\n", call_id); //*((unsigned int *)(vargp)));
      sleep(3);
      break;
      }
  }
    sem_wait(&operators);
    printf("Thread[%d] has bought a ticket!\n", call_id); //*((unsigned int *)(vargp)));
    sem_wait(&connected_lock); //critical section of connected begins
    connected--; //increment connected callers
    sem_post(&connected_lock); //exit critical section
    
    sem_post(&operators);
  

    /*sem_wait(&connected_lock); //critical section of connected begins
    connected--; //increment connected callers
    sem_post(&connected_lock); //exit critical section*/
    
    printf("Thread[%d] has hung up!\n", call_id);//*((unsigned int *)(vargp)));

    sem_destroy(&operators);
    sem_destroy(&connected_lock);

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
