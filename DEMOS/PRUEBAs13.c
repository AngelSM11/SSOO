#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
pid_t child_pid, wpid;
int status;
int A=0;

for(int i=0; i<4;i++){
switch(child_pid = fork()){

case -1:   /* fork() failed */
    perror("fork");
    exit(EXIT_FAILURE);


case 0:     /* This is the child */
    /* Child does some work and then terminates */
     printf("Soy el hijo %d, mi padre %d\n", getpid(), getppid());
     A=A+1;
     printf("%d\n",A);
     //exit(EXIT_SUCCESS);
     break;


default:
    printf("padre %d\n", getpid());
    printf("Esperando a que mi hijo %d termine \n", i+1);
    do {
        wpid = waitpid(child_pid, &status, WUNTRACED);
        if (wpid == -1) {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }


        if (WIFEXITED(status)) {
            printf("child exited, status=%d\n", WEXITSTATUS(status));


        } else if (WIFSIGNALED(status)) {
            printf("child killed (signal %d)\n", WTERMSIG(status));


        } else if (WIFSTOPPED(status)) {
            printf("child stopped (signal %d)\n", WSTOPSIG(status));

        } else {    /* Non-standard case -- may never happen */
            printf("Unexpected status (0x%x)\n", status);
        }
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    exit(EXIT_SUCCESS);
    
    }
    
}
printf("Suma final %d\n",A);
}