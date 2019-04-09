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
    sem_t operators;
	sem_init(&operators, 0, 3);
//pthread_create
	sem_wait(&operators);
// Proceed with ticket ordering process
	sem_post(&operators);
}


void *thread(void *vargp) {
  sem_init()
  pthread_t[5];
  for(int n=0;n<5;++n){
  pthread_t[n]pthread_create(&next_id++,NULL,phonecall,NULL);
  }
  printf("This is a phone call\n");
  for(int a=0;a<5;a++){
  	pthread_join(pthread_t[n],NULL);
  }

  return NULL;
}





int main (void){
pthread_t td1,td2,td3; // operator
pthread_create(&td1,NULL,thread,NULL);
pthread_create(&td2,NULL,thread,NULL);
pthread_create(&td3,NULL,thread,NULL);


return 0;
}



