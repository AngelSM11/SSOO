#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;




void *Escritor(void *arg)
{
    int *a;
    a = malloc(sizeof(int));
    pthread_mutex_lock(&mutex);
    a=(int*)arg;
    printf("Escruibiendo %d\n", *a);
    pthread_mutex_unlock(&mutex);

    pthread_exit(a);
}

void *Lector(void *arg)
{
    int *b;
    b = malloc(sizeof(int));
    pthread_mutex_lock(&mutex);
    printf("Leyendo %d\n", *(int*) b);
    pthread_mutex_unlock(&mutex);
}

int main(void)
{
    int N=0;
    pthread_t  th1, th2;
    
    printf("Valor a escribir");
    scanf("%d", &N);

    
    pthread_create(&th1, NULL, Escritor,(void*) &N);
    pthread_join(th1, (void**) &N);
    pthread_create(&th2, NULL, Lector, (void*) &N);


    
    //pthread_join(th2, NULL);
    return 0;
}