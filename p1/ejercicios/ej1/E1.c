
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>


int main(int argc, char *argv[]){
    
    pid_t pid,chilpid;
    int status;

    if(argc!=2)
    {
        printf("Error en linea de comandos\n");
        exit(EXIT_FAILURE);
    }

        printf("-------------------Soy el ABUELO con pid %d \n",getpid());
        switch (chilpid=fork())
        {

        case -1:
        printf("Error al crear hijo\n");
        exit(EXIT_FAILURE);

        case 0:
        printf("Soy el hijo con pid %d y mi padre es %d\n",getpid(),getppid());
        for(int i=0; i<atoi(argv[1]); ++i)
            {
            switch (chilpid=fork())
            {

            case -1:
            printf("Error al crear hijo\n");
            exit(EXIT_FAILURE);

            case 0:
            printf("Soy el hijo con pid %d y mi padre es %d\n",getpid(),getppid());
            
            exit(EXIT_SUCCESS);

            default:
            printf("-------------------Soy el PADRE con pid %d y mi HIJO es %d\n",getpid(),chilpid);
            pid = wait(&status);
            do{
                if (chilpid == -1) {
                    perror("waitpid");
                    exit(EXIT_FAILURE);
                }
                if (WIFEXITED(status)) {
                    printf("child exited %d, status=%d\n",chilpid, WEXITSTATUS(status));


                } else if (WIFSIGNALED(status)) {
                    printf("child killed (signal %d)\n", WTERMSIG(status));


                } else if (WIFSTOPPED(status)) {
                    printf("child stopped (signal %d)\n", WSTOPSIG(status));

                } else {    /* Non-standard case -- may never happen */
                    printf("Unexpected status (0x%x)\n", status);
                }
            }while((wait(&status))>0);
            }
        }
        printf("-------------------Soy el ABUELO con pid %d y mi HIJO es %d\n",getppid(),getpid());
        exit(EXIT_SUCCESS);
            
        
    }
    
        pid = wait(&status);
        do{
        if (pid == -1) {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }
        if (WIFEXITED(status)) {
            printf("child exited %d, status=%d\n",chilpid, WEXITSTATUS(status));
            printf("cHIVATO\n");

        } else if (WIFSIGNALED(status)) {
            printf("child killed (signal %d)\n", WTERMSIG(status));


        } else if (WIFSTOPPED(status)) {
            printf("child stopped (signal %d)\n", WSTOPSIG(status));

        } else {    /* Non-standard case -- may never happen */
            printf("Unexpected status (0x%x)\n", status);
        }
        }while((wait(&status))>0);
    return 0;
};