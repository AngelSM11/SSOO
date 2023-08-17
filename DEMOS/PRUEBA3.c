#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>


int factorial(int n){
    int fact=1;

    if(n<0){
        exit(EXIT_FAILURE);
    }
    if(n>0){
        for(int j=1;j<n;j++){
            fact=fact*(j+1);
        }
    }

    return fact;
}

void signal_handless(){
    printf("------------- Señal ------------\n");
    exit(0);
}

int main(int argc, char *argv[]){
pid_t child_pid, wpid;
int status;

for(int i=1;i<=2;i++){
switch(child_pid = fork()){
case -1:       /* fork() failed */
    perror("fork");
    exit(EXIT_FAILURE);


case 0:        /* This is the child */
    /* Child does some work and then terminates */
    if(i==1){
        //Factorial
        if(signal(SIGUSR1, signal_handless )==0){
            printf("Señal recibida en el hijo %d\n", getpid());
            exit(EXIT_FAILURE);
        }
        else{
        printf("Soy el hijo %d, mi padre %d y el factorial de %s es %d\n", getpid(), getppid(), argv[1],factorial(atoi(argv[1])));
        exit(EXIT_SUCCESS);
        }
    }

    if(i==2){
        //Calculadora
        printf("Soy el hijo %d, mi padre %d y voy a abrir la calculadora\n", getpid(), getppid());
        if(execlp(argv[2],argv[2],NULL)==0){
            perror("execl");
            exit(EXIT_FAILURE);
        }
        exit(EXIT_SUCCESS);
    }
    

default:               /* This is the parent */
    printf("Soy el Padre %d\n", getpid());
    
}
}
    wpid = waitpid(child_pid, &status, WUNTRACED);
    //wpid=wait(&status);
    do{
        
        if (wpid == -1) {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }


        if (WIFEXITED(status)) {
            printf("Padre %d,ha finalizado el hijo %d con el estado %d\n",getpid(), wpid, WEXITSTATUS(status));


        } else if (WIFSIGNALED(status)) {
            printf("Padre %d,ha finalizado el hijo %d con el estado %d\n",getpid(), wpid, WTERMSIG(status));


        } else if (WIFSTOPPED(status)) {
            printf("Padre %d,ha finalizado el hijo %d con el estado %d",getpid(), wpid, WSTOPSIG(status));



        } else {    /* Non-standard case -- may never happen */
            printf("Padre %d,ha finalizado el hijo %d con el estado %x)\n",getpid(), wpid, status);
        }
    }while ((wpid=wait(&status))>=0);

}