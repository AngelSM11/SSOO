#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>



int par=0, impar=0;
static pthread_mutex_t foo_mutex = PTHREAD_MUTEX_INITIALIZER;


void *incer(void *arg)
{
    
    int *suma=malloc(sizeof(int));
    int *N=(int*)arg;
    int random;
    if((*N%2)==0){
        for(int j=0;j<100;j++){
            random =rand()%10;
            par=par+random;
            *suma=*suma+random;
        }
    }
    else if((*N%2)!=0){
        for(int j=0;j<100;j++){
            random =rand()%10;
            impar=impar+random;
            *suma=*suma+random;
            
        }
        
    }
   
    pthread_exit(suma);
}


int main(int agrc, char* argv[])
{
    int N=atoi(argv[1]);
    pthread_t  th1[N];
    int *suma;
    int sumatotal=0;

    


 
   for(int i=0;i<N;i++){

    pthread_create(&th1[1], NULL, incer, (void*) &N);
    pthread_join(th1[1], (void**) &suma);
    
    sumatotal=sumatotal+*suma;
    

   }
   
   printf("%d\n",sumatotal);
   printf("%d\n",(impar+par));
   if(sumatotal==(impar+par)){
    printf("CORRECTO\n");
   }
    return 0;
}