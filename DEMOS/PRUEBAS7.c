#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <semaphore.h>

int variable=-1;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void * lector(void *arg)
{

    pthread_mutex_lock(&mutex);

    printf("Lector %ld, leo el numero %d\n", pthread_self(), variable);
    pthread_mutex_unlock(&mutex);
    pthread_exit(0);
}

void * escritor(void *arg)
{
    
    pthread_mutex_lock(&mutex);
    variable=variable+1;
    printf("Escritor %ld, escribio el numero %d\n", pthread_self(), variable);
    
    pthread_mutex_unlock(&mutex);
    pthread_exit(0);
}


int main(int argc, char *argv[]){
    
    pthread_mutex_init(&mutex, NULL);
    for(int i=0; i<atoi(argv[1]);i++){
    pthread_t  th1, th2;

    pthread_create(&th2, NULL, escritor, NULL);
    pthread_create(&th1, NULL, lector, NULL);
    


    if(pthread_join(th1, NULL)){
        printf("ERROR LECTOR");
    };
    if(pthread_join(th2, NULL)){
        printf("ERROR ESCRITOR");
    };
    }
    return 0;
}