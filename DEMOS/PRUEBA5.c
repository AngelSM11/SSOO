#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <errno.h>
#include <string.h>

int count=0;
sem_t mutex;

void *th_fuction(void *arg)
{
    int aux;
    
    

    sem_wait(&mutex);
    printf("%d", *(int *)arg+1);
    aux=count;
    aux=aux+1;
    count=aux;

    sem_post(&mutex);

    pthread_exit(NULL);
    
}


int main(int argc, char *argv[])
{
    long ret, *ret2, rvalue;
    int join_value, join_value2, p, valor=atoi(argv[1]);
    pthread_t  th1;
    
    p=sem_init(&mutex, 0, 1);
    if (p !=0)
   {
       printf("sem_init error...\n");
       printf("errno value= %d definido como %s\n", errno, strerror(errno));
       exit(EXIT_FAILURE); 
   }


    for(int i=0;i<atoi(argv[1]);i++){

    pthread_create(&th1, NULL, th_fuction, (void*) &valor);

    join_value= pthread_join(th1, NULL);
    
    

    if(join_value!=0){
        perror("Fallo en pthread_join()...\n");		
	    exit(EXIT_FAILURE);
    }
    }
    

    printf("%d\n",count);
    
    return 0;
}