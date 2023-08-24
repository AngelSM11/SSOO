#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>



long double factorial(int a){
    long double aux=1;
    long double aux2;
    if(a<1){
        printf("introduce valor 1 o mayor a 1\n");
    }
    if(a>1){

    for(int i=0;i<a; i++){
        aux2=aux;
        aux=aux+aux2;
    }
    }
    return aux;
}

int main(int agrc, char *argv[]){
pid_t child_pid, wpid;
int status;

for(int i=0;i<2; i++){
switch(child_pid = fork()){
    case -1:
          /* fork() failed */
        perror("fork");
        exit(EXIT_FAILURE);
    


    case 0: 
           /* This is the child */
        /* Child does some work and then terminates */
        if(i==0){
            int fact=factorial(atoi(argv[1]));
            printf("Soy el hijo %d mi padre es %d el factorial de %d es %d\n", getpid(), getppid(),atoi(argv[1]),fact);
    
            }

        if(i==1){
            printf("Soy el hijo %d mi padre es %d y voy a abrir la calculadora\n", getpid(), getppid());
            if((execlp(argv[2],argv[2], (char*) NULL))!=0){
                perror("fork");
                exit(EXIT_FAILURE);
            }
        }
        exit(EXIT_SUCCESS);
    
    default:
        printf("Padre: Genreando hijo\n");

    
    }
}      
    wpid = wait(&status);              /* This is the parent */
    do {
        
        if (wpid == -1) {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }


        if (WIFEXITED(status)) {
            printf("Padre %d, ha finalizado el hijo %d con el status=%d\n",getpid(), wpid, WEXITSTATUS(status));


        } else if (WIFSIGNALED(status)) {
            printf("child killed (signal %d)\n", WTERMSIG(status));


        } else if (WIFSTOPPED(status)) {
            printf("child stopped (signal %d)\n", WSTOPSIG(status));

        } else {    /* Non-standard case -- may never happen */
            printf("Unexpected status (0x%x)\n", status);
        }
    } while ((wpid=wait(&status))>0);

}