#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdbool.h>

int next_id=1;
sem_t lock;
volatile int num_call;

void* phonecall(void* vargp) {
    static int NUM_OPERATORS = 3;
    static int NUM_LINES = 5;
    static int connected = 0;    // Callers that are connected
    static sem_t connected_lock;
    static sem_t operators;
    sem_init(&connected_lock,0,1);
    sem_init(&operators,0,NUM_OPERATORS);
  

  //while(num_call>=0){
 	sem_wait(&connected_lock);
 	printf("THREAD[%d] is calling line,busy signal\n",next_id);
 	 if(connected==NUM_LINES){
     printf("The lines are busy, wait\n");
     sem_post(&connected_lock);
    }
 else{
    ++connected;
    sem_wait(&operators);
    //++connected;
    printf("THREAD[%d] is speaking to operator\n",next_id);
    sleep(3);
    printf("THREAD[%d] has bought the ticket!\n",next_id);
    printf("THREAD[%d] has hung up!\n",next_id);
    --connected;
    //pthread_exit(NULL);
    sem_post(&operators);
      //--connected;
    }
  //}
  //}
  //sem_post(&operators);
 


/*Check if the connection can be made:
	a.You'll need to test connected in a critical section
	b.If the line is busy, exit the critical section, print a message, and try again
	c.If the line is not busy, update connected, exit the critical section, and print a message, and continue to the next step.
Wait for an operator to be available (use a counting semaphore)
Print a message that the order is being taken by an operator
a ticket order by sleeping for a few seconds (sleep(3))
Print a message that the order is complete (and update the semaphore)
Update connected (using a binary semaphore)
Print a message that the call is over*/
return NULL;
}




int main(int argc, char **argv) {
sem_init(&lock,0,1);
if (argc != 2) {
    printf("There no phone call\n");
    exit(0);
}
pthread_t thread_arr[atoi(argv[0])];
num_call=atoi(argv[0]);//conver number of call into integer

pthread_t tid,tid2;// operator
//for(int n=0;n<num_call;++n){
++next_id;
pthread_create(&tid,NULL,phonecall,NULL);
pthread_join(tid,NULL);
//thread_arr[n]=tid;
pthread_create(&tid2,NULL,phonecall,NULL);
//pthread_create(&tid3,NULL,thread,NULL;
//}

/*for (int i = 0; i < num_call; ++i){


pthread_join(thread_arr[i], NULL);*/

pthread_join(tid2, NULL);

return 0;
}
