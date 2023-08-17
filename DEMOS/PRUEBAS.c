#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>


int main(int argc, char *argv[]){
pid_t child_pid, wpid;
int status;

if(argc!=2)
{
    printf("Error en el numero de argumentos introducidos\n");
    exit(EXIT_FAILURE);
}

printf("Soy el proceso padre con PID %d\n", getpid());
for(int i=0; i<atoi(argv[1]); i++ ){
switch(child_pid=fork()){

        case -1:
            /* fork() failed */
            perror("fork");
            exit(EXIT_FAILURE);



        case 0:
            /* HIJO */
            /* Child does some work and then terminates */
            printf("Soy el proceso hijo con PID %d y mi padre %d\n", getpid(), getppid());
            sleep(2);
            printf("Hijo %d terminado\n", getpid());
            exit(EXIT_SUCCESS);


        
        default:  
           // printf("Padre BIEN con pid: %d\n", getpid());  
            printf("Hijo %d generado\n",child_pid );               /* This is the parent */
            sleep(1);
    }
}       
        wpid=wait(&status);
        sleep(2);
        do {
                
                if (wpid == -1) {
                    perror("waitpid");
                    exit(EXIT_FAILURE);
                }


                if (WIFEXITED(status)) {
                    printf("Hijo %d finalizado con padre %d status=%d\n",wpid,getpid(), WEXITSTATUS(status));


                } else if (WIFSIGNALED(status)) {
                    printf("child killed (signal %d)\n", WTERMSIG(status));


                } else if (WIFSTOPPED(status)) {
                    printf("child stopped (signal %d)\n", WSTOPSIG(status));  
            }
        }while((wpid=wait(&status)) >=0);
            if (errno == ECHILD) {
                printf("%d",ECHILD);
                printf("Todos los hijos han terminado\n");
            }
            else {    /* Non-standard case -- may never happen */
                    printf("Unexpected status (0x%x)\n", status);
                }

    return EXIT_SUCCESS;

}
    

