#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int factorial(int a){
    int fact=1;
    int aux=1;
    for(int j=2;j<=a;j++){
        
        fact=fact*j;
       
    }
    return fact;

}

int main(int argv, char *argc[]){
pid_t child_pid, wpid;
int status;

for(int i=0;i<2;i++){

switch(child_pid = fork()){
case -1:    /* fork() failed */
    perror("fork");
    exit(EXIT_FAILURE);



case 0:    /* This is the child */
    if(i==0){
        printf("Soy el hijo %d, mi padre es %d, y voy a abrir la calculadora\n",getpid(),getppid());
        if(execlp(argc[1], argc[1],(char*)NULL)){
            perror("fork");
            exit(EXIT_FAILURE);
        }
    }

    if(i==1){
        printf("Soy el hijo %d, mi padre es %d, y voy a hacer el factorial %d\n",getpid(),getppid(),factorial(atoi(argc[2])));
    }
    exit(EXIT_SUCCESS);
default:
    printf("Soy el padre %d, generando hijo\n",getpid());
}
}

    //wpid = waitpid(child_pid, &status, WUNTRACED); 
    wpid=wait(&status);     /* This is the parent */
    do {
       
        if (wpid == -1) {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }


        if (WIFEXITED(status)) {
            printf("child %d exited, status=%d\n",wpid, WEXITSTATUS(status));


        } else if (WIFSIGNALED(status)) {
            printf("child killed (signal %d)\n", WTERMSIG(status));


        } else if (WIFSTOPPED(status)) {
            printf("child stopped (signal %d)\n", WSTOPSIG(status));

        } else {    /* Non-standard case -- may never happen */
            printf("Unexpected status (0x%x)\n", status);
        }
    } while ((wpid=wait(&status))!=0);
}
