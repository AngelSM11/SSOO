#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

void signal_handless(){
    printf("------------- Señal ------------\n");
    exit(0);
}

int main(int argc, char* argv[]){
pid_t child_pid, wpid;
int status, N;
printf(" Numero de hijos: ");
scanf("%d",&N);
printf("Soy el padre %d \n", getpid());

    for(int J=0;J<N;J++){
        switch(child_pid = fork()){
            case -1:      /* fork() failed */
                perror("fork");
                exit(EXIT_FAILURE);



            case 0:       /* This is the child */
                /* Child does some work and then terminates */
                printf(" Hijo <%d>. Pid del padre: <%d>\n", getpid(), getppid() );
                if(J==N-1){
                    if(signal(SIGUSR1, signal_handless )==0){
                        sleep(2);
                    }
                }
            break;


            default:
            printf("Esperando a que mi hijo %d termine \n", J+1);
            wait(&status);
            printf("El proceso %d ha finalizado, codigo de salida: %d \n", wpid,WEXITSTATUS(status));
            exit(EXIT_SUCCESS);

        } 
        }
 }
    
