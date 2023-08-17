#include <sys/types.h>

#include <stdio.h>

#include <stdlib.h>

#include <errno.h>

#include <unistd.h>

#include <sys/wait.h>

int main(int argc, char *argv[])
{
    pid_t pid, childpid;

    int status, N;

    printf("Numero de hijos:\n");
    scanf("%d",&N);

    for(int i = 1; i<N;i++)
    {
        pid= fork();

        if(pid==-1)
        {
            printf("Error al rear el hijo\n");
            exit(EXIT_FAILURE);
        }

        else if(pid==0)
        {
            printf("Hijon creado correctamente\n");
            printf("Hijo %d pid: %d, pid del padre %d \n", i,getpid(), getppid() );
        }

        else
        {
            printf("Padre %d, pid del padre %d \n",getpid(), getppid());

            childpid = wait(&status);

            if(childpid>0)
            {
                if(WIFEXITED(status)) printf("child %d exited. Status: %d\n", childpid, WEXITSTATUS(status));
                else if(WIFSIGNALED(status)) printf("child %d exited. Status: %d\n", childpid, WTERMSIG(status));
                else if(WIFSTOPPED(status)) printf("child %d exited. Status: %d\n", childpid, WSTOPSIG(status));            
                else 
                {
                    printf("Error ne la invocacion del wait o la llamada ha sido interrumpida por una señal");
                    exit(EXIT_FAILURE);

                }
            }
        }
    }
    exit(EXIT_SUCCESS);
}