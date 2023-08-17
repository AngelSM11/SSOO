
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>


int main(int argc, char *argv[]){
    
    
    if(argc!=2)
    {
        printf("Error en linea de comandos\n");
        exit(EXIT_FAILURE);
    }

    int n=atoi(argv[1]);
    
    for(int i=0; i<n; ++i)
    {
        switch (fork())
        {

        case -1:
        printf("Error al crear hijo\n");
        exit(EXIT_FAILURE);

        case 0:
        printf("Soy el hijo con pid %d y mi padre es %d\n",getpid(),getppid());
        exit(EXIT_SUCCESS);

        case 1:
        printf("Soy el padre con pid %d, esperando a qu emi hijo con pid %d termine\n", getppid(), getpid());

        }
    }
    return 0;
};